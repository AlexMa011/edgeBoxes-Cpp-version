//
// Created by alexma on 23/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "model.h"

using namespace std;
using namespace cv;

Mat ConvTri(Mat, double, int s = 1);

tuple<Mat, Mat> edgesChns(Mat, _opt);

tuple<Mat, Mat, Mat> edgesDetectmain(_model, Mat, Mat, Mat);

Mat edgesNms(Mat, Mat, int, int, float, int);

void getadd(Mat, float *);

void fillmat(float *, Mat);

void writeCSV(string, Mat);


tuple<Mat, Mat, Mat, Mat> edgesDetect(Mat I, _model model, int nargout) {
    clock_t begin = clock();
    // get parameters
    _opt opts = model.opts;
    const int shrink = (const int) opts.shrink;
    const int imWidth = (const int) opts.imWidth;
    const int gtWidth = (const int) opts.gtWidth;
    const int nChns = opts.nChns;
    const int nCells = opts.nCells;
    const uint32 nChnFtrs = (const uint32) opts.nChnFtrs;
    const int stride = (const int) opts.stride;
    const int nTreesEval = opts.nTreesEval;
    int sharpen = opts.sharpen;
    int nThreads = opts.nThreads;
    const int nBnds = int(model.eBnds.rows * model.eBnds.cols - 1) /
                      int(model.thrs.rows * model.thrs.cols);
    opts.nTreesEval = min(opts.nTreesEval, opts.nTrees);
    // need to add something here
    opts.stride = max(opts.stride, opts.shrink);
    model.opts = opts;

    //get image size
    int rowsiz = I.rows;
    int colsiz = I.cols;
    auto siz = I.size();
    const int nTreeNodes = model.fids.cols;
    const int nTrees = model.fids.rows;
    const int h1 = (int) ceil(double(rowsiz - imWidth) / stride);
    const int w1 = (int) ceil(double(colsiz - imWidth) / stride);
    const int h2 = h1 * stride + gtWidth;
    const int w2 = w1 * stride + gtWidth;
    const int chnDims[3] = {rowsiz / shrink, colsiz / shrink, nChns};
    const int indDims[3] = {h1, w1, nTreesEval};
    const int outDims[3] = {h2, w2, 1};
    const int segDims[5] = {gtWidth, gtWidth, h1, w1, nTreesEval};



    //define outputs
    Mat E(rowsiz, colsiz, CV_32FC1);
    //Mat O(rowsiz, colsiz, CV_32FC1);
    Mat segs(5, segDims, CV_8UC1);
    Mat inds(3, indDims, CV_32SC1);
    tuple<Mat, Mat, Mat, Mat> output;



    if (opts.multiscale) {
        // if multiscale run edges detect multi times
        int k = 3;
        double ss[3] = {0.5, 1, 2};
        inds.copyTo(segs);
        model.opts.multiscale = 0;
        model.opts.nms = 0;
        E.setTo(Scalar(0));
        // need to handle E as an output
        for (int i = 0; i < k; i++) {
            double s = ss[i];
            Mat I1;
            resize(I, I1, Size(), s, s);
            Mat E1;
            //add the imResample function
            if (nargout < 4) {
                //handle the output
                output = edgesDetect(I1, model, nargout);
                Mat unuse1, unuse2, inds_col;
                tie(E1, unuse1, inds_col, unuse2) = output;
                inds_col.copyTo(inds.col(i));
            } else {
                output = edgesDetect(I1, model, nargout);
                Mat unuse, inds_col, segs_col;
                tie(E1, unuse, inds_col, segs_col) = output;
                inds_col.copyTo(inds.col(i));
                segs_col.copyTo(segs.col(i));
            }
            Mat E1_sample;
            resize(E1, E1_sample, siz, 0, 0);
            E += E1_sample;
            E1_sample.release();
            model.opts = opts;
        }
    } else {

        // pad image, making divisible by 4
        int r = (int) opts.imWidth / 2;
        int p[4];
        for (int i = 0; i < 4; i++) p[i] = r;
        p[1] = p[1] + (4 - (rowsiz + 2 * r) % 4) % 4;
        p[3] = p[3] + (4 - (colsiz + 2 * r) % 4) % 4;
        Mat I_padding;
        copyMakeBorder(I, I_padding, p[0], p[1], p[2], p[3], BORDER_REFLECT);
        I_padding.copyTo(I);
        I_padding.release();



        //compute features and apply forest to image
        tuple<Mat, Mat> chns = edgesChns(I, opts);


        Mat chnsReg;
        Mat chnsSim;
        tie(chnsReg, chnsSim) = chns;
        double s = opts.sharpen;
        if (s) {
            Mat I_norm, I_conv;
            normalize(I, I_norm, 0, 1, NORM_MINMAX, CV_32F);
            I_conv = ConvTri(I_norm, 1);
            I_conv.copyTo(I);
            I_norm.release();
            I_conv.release();
        }




        tuple<Mat, Mat, Mat> mainoutput = edgesDetectmain(model, I, chnsReg, chnsSim);
        tie(E, inds, segs) = mainoutput;




        //normalize and finalize edge maps
        double t = pow(opts.stride, 2) / pow(opts.gtWidth, 2) / opts.nTreesEval;
        r = (int) opts.gtWidth / 2;
        if (s == 0) t = t * 2;
        else if (s == 1) t = t * 1.8;
        else t = t * 1.66;
        Mat new_E;
        E.rowRange(r, rowsiz + r).colRange(r, colsiz + r).copyTo(new_E);
        new_E *= t;
        E = ConvTri(new_E, 1);
        new_E.release();


    }




    //compute approximate orientation O from edges E
    Mat Oxx, Oxy, Oyy;
    Mat E_conv = ConvTri(E, 4);
    Sobel(E_conv, Oxx, -1, 2, 0);
    Sobel(E_conv, Oxy, -1, 1, 1);
    Sobel(E_conv, Oyy, -1, 0, 2);
    E_conv.release();

    float *o = new float[rowsiz * colsiz];
    float *oxx = (float *) Oxx.data;
    float *oxy = (float *) Oxy.data;
    float *oyy = (float *) Oyy.data;
    for (int i = 0; i < rowsiz * colsiz; i++) {
        int xysign = -((oxy[i] > 0) - (oxy[i] < 0));
        o[i] = (atan((oyy[i] * xysign / (oxx[i] + 1e-5))) > 0) ? (float) fmod(
                atan((oyy[i] * xysign / (oxx[i] + 1e-5))), M_PI) : (float) fmod(
                atan((oyy[i] * xysign / (oxx[i] + 1e-5))) + M_PI, M_PI);
    }
    Oxx.release();
    Oxy.release();
    Oyy.release();
    Mat O(rowsiz, colsiz, CV_32FC1, o);


    //perform nms
    if (opts.nms > 0)
        E = edgesNms(E, O, 1, 5, 1.01, opts.nThreads);

    output = make_tuple(E, O, inds, segs);
    return output;


}
