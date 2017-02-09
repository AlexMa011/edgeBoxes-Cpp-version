//
// Created by alexma on 31/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void getadd(Mat, float *);

void fillmat(float *, Mat);

void gradMag(float *, float *, float *, int, int, int, bool);

void gradHist(float *, float *, float *, int, int, int bin, int nOrients, int softBin, bool full = 0);

Mat ConvTri(Mat, double, int s = 1);

void gradMagNorm(float *, float *, int, int, float);

tuple<Mat, Mat> gradientMag(Mat I, int channel, bool full = 0) {
    float *I_data = new float[I.rows * I.cols * I.channels()];
    getadd(I, I_data);
    float *M_data = new float[I.rows * I.cols];
    float *O_data = new float[I.rows * I.cols];
    for (int i = 0; i < I.rows * I.cols; i++) M_data[i] = 0.f;
    for (int i = 0; i < I.rows * I.cols; i++) O_data[i] = 0.f;
    gradMag(I_data, M_data, O_data, I.rows, I.cols, I.channels(), full);
    Mat M(I.rows, I.cols, CV_32F);
    Mat O(I.rows, I.cols, CV_32F);
    fillmat(M_data, M);
    fillmat(O_data, O);
    tuple<Mat, Mat> output = make_tuple(M, O);
    delete[] I_data;
    delete[] M_data;
    delete[] O_data;
    return output;
};

Mat gradientHist(Mat M, Mat O, int bin, int nOrients, bool softbin) {
    float *M_data = new float[M.rows * M.cols * M.channels()];
    getadd(M, M_data);
    float *O_data = new float[O.rows * O.cols * O.channels()];
    getadd(O, O_data);
    int hb = M.rows / bin;
    int wb = M.cols / bin;
    float *H_data = new float[hb * wb * nOrients];
    for (int i = 0; i < hb * wb * nOrients; i++) H_data[i] = 0.f;
    gradHist(M_data, O_data, H_data, M.rows, M.cols, bin, nOrients, softbin);
    Mat H(hb, wb, CV_32FC(nOrients));
    fillmat(H_data, H);

    return H;
};

void gradientMagNorm(Mat M, double normRad, float normConst) {
    Mat S = ConvTri(M, normRad);
    int h = M.rows;
    int w = M.cols;
    float *M_data = new float[h * w];
    float *S_data = new float[h * w];
    getadd(M, M_data);
    getadd(S, S_data);
    gradMagNorm(M_data, S_data, h, w, normConst);
    fillmat(M_data, M);
}