//
// Created by alexma on 26/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


Mat ConvTri(Mat I, double r, int s = 1) {
    int height = I.rows;
    int width = I.cols;
    int depth = I.channels();
    Mat J, J1;
    if (r > 0 & r <= 1) {
        float p = (float) (12 / r / (r + 2) - 2);
        Mat kernel;
        kernel.push_back<float>(1 / (2 + p));
        kernel.push_back<float>(p / (2 + p));
        kernel.push_back<float>(1 / (2 + p));
        Mat kernel_t(kernel.cols, kernel.rows, kernel.type());
        transpose(kernel, kernel_t);
        r = 1;
        Point anchor = Point(-1, -1);
        filter2D(I, J, CV_32F, kernel_t, anchor, 0, BORDER_REFLECT);
        filter2D(J, J1, CV_32F, kernel, anchor, 0, BORDER_REFLECT);
        kernel.release();
        kernel_t.release();
    } else {
        Mat kernel;
        float ke = 0;
        for (int i = 0; i < r; i++) {
            ke = i + 1;
            kernel.push_back<float>(ke);
        }
        ke = (float) r + 1;
        kernel.push_back<float>(ke);
        for (int i = (int) r + 1; i < 2 * r + 1; i++) {
            ke = (float) (2 * r + 1 - i);
            kernel.push_back<float>(ke);
        }
        kernel /= pow((r + 1), 2);
        Mat kernel_t(kernel.cols, kernel.rows, kernel.type());
        transpose(kernel, kernel_t);
        Point anchor = Point(-1, -1);
        filter2D(I, J, CV_32F, kernel_t, anchor, 0, BORDER_REFLECT);
        filter2D(J, J1, CV_32F, kernel, anchor, 0, BORDER_REFLECT);
        kernel.release();
        kernel_t.release();
    }


    J.release();


    //handle the difference between row major and col major layout
    return J1;
}

//void convTri1(float *, float *, int, int, int, float, int);

//void convTri(float *, float *, int, int, int, int, int);

//void getadd(Mat, float *);

//void fillmat(float *, Mat);


//Mat ConvTri(Mat I, double r, int s = 1) {
//    clock_t begin = clock();
//    int height = I.rows;
//    int width = I.cols;
//    int depth = I.channels();
//    float *J_data = new float[height * width * depth];
//    for (int i = 0; i < height * width * depth; i++) J_data[i] = 0;
//    float *I_data = new float[height * width * depth];
//    getadd(I, I_data);
//    if (r > 0 && r <= 1 && s <= 2) {
//        convTri1(I_data, J_data, height, width, depth, (float) (12 / r / (r + 2) - 2), s);
//    } else {
//        convTri(I_data, J_data, height, width, depth, (int) r, s);
//    }
//
//
//    //handle the difference between row major and col major layout
//    Mat J(height, width, I.type());
//    if (I.channels() < 5) {
//        fillmat(J_data, J);
//    } else {
//        vector<Mat> Ivec((unsigned) I.channels());
//        for (int i = 0; i < I.channels(); i++) {
//            Ivec[i].create(height, width, CV_32FC1);
//            Ivec[i].zeros(height, width, CV_32FC1);
//        };
//        for (int i1 = 0; i1 < I.channels(); i1++) {
//            for (int j1 = 0; j1 < I.cols; j1++) {
//                for (int k1 = 0; k1 < I.rows; k1++) {
//                    Ivec[i1].at<float>(k1, j1) = J_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//                }
//            }
//        }
//        merge(Ivec, J);
//    }
//    return J;
//}