//
// Created by alexma on 24/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <string>
#include <cmath>
#include <tuple>
#include "model.h"

void writeCSV(string, cv::Mat);

using namespace std;
using namespace cv;

Mat ConvTri(Mat, double, int s = 1);

tuple<Mat, Mat> gradientMag(Mat, int, bool full = 0);

Mat gradientHist(Mat, Mat, int, int, bool);

Mat rgbToLuvu(Mat);

void gradientMagNorm(Mat, double, float);

tuple<Mat, Mat> edgesChns(Mat I, _opt opts) {


    double a, b;
    int rowsiz = I.rows;
    int colsiz = I.cols;
    auto siz = I.size();
    int nChannels = opts.nChns;
    uint32 shrink = opts.shrink;
    int shrinkrowsiz = rowsiz / shrink;
    int shrinkcolsiz = colsiz / shrink;
    Mat chnsReg(shrinkrowsiz, shrinkcolsiz, CV_32FC(nChannels));
    Mat chnsSim(shrinkrowsiz, shrinkcolsiz, CV_32FC(nChannels));
    int nTypes = 1;
    int k = 0;
    Mat chns(shrinkrowsiz, shrinkcolsiz, CV_32FC(nChannels));
    Mat float_I;
    Mat I_shrink;
    float_I = rgbToLuvu(I);
    float_I.convertTo(I, CV_32FC3);
    double scale = (double) 1 / shrink;
    resize(I, I_shrink, Size(), scale, scale);
    Mat *mergemat = new Mat[5];
    mergemat[k] = I_shrink;
    k++;
    float_I.release();


    for (int i = 1; i < 3; i++) {
        int s = (int) pow(2, i - 1);
        Mat I1;
        if (s == shrink)
            I1 = I_shrink;
        else
            resize(I, I1, Size(), 1 / s, 1 / s);

        Mat float_I1;
        I1 = ConvTri(I1, opts.grdSmooth);

        tuple<Mat, Mat> magout;
        magout = gradientMag(I1, 0);
        Mat M, O;
        tie(M, O) = magout;
        gradientMagNorm(M, opts.normRad, 0.01f);
        int binsiz = max(1, (int) shrink / s);
        Mat H;
        H = gradientHist(M, O, binsiz, opts.nOrients, 1);
        Mat M_re, H_re;
        double rescale = (double) s / shrink;
        resize(M, M_re, Size(), rescale, rescale);
        resize(H, H_re, Size(), fmax(1, rescale), fmax(1, rescale));
        mergemat[k] = M_re;
        k++;
        mergemat[k] = H_re;
        k++;
        M_re.release();
        H_re.release();
        M.release();
        O.release();
    }


    int *from_to = new int[opts.nChns * 2];
    for (int i = 0; i < opts.nChns; i += 1) {
        from_to[2 * i] = i;
        from_to[2 * i + 1] = i;
    }
    mixChannels(mergemat, 5, &chns, 1, from_to, opts.nChns);
    assert(chns.channels() == opts.nChns);
    double chnSm = opts.chnSmooth / shrink;
    double simSm = opts.simSmooth / shrink;
    if (chnSm > 1) chnSm = round(chnSm);
    if (simSm > 1) simSm = round(simSm);
    chnsReg = ConvTri(chns, chnSm);
    chnsSim = ConvTri(chns, simSm);
    tuple<Mat, Mat> output = make_tuple(chnsReg, chnsSim);
    chnsReg.release();
    chnsSim.release();
    return output;
};