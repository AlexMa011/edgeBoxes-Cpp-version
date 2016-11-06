//
// Created by alexma on 26/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <string>
#include <cmath>
#include <tuple>
#include "model.h"
#include <ctime>

using namespace std;
using namespace cv;


_para initial_para();

tuple<Mat, Mat, Mat, Mat> edgesDetect(Mat, _model, int);

Mat parts_localization_main(Mat, Mat, _para);

Mat edgesNms(Mat, Mat, int, int, float, int);

Mat edgeBoxesImg(Mat I, _model model, _para);

void output(string, Mat, Mat, _model);

void writeout(string, Mat, const char*);

void parts_localization(string picname, _model model) {
    Mat I = imread(picname);
    assert(I.rows!=0 && I.cols!=0);
    cvtColor(I, I, COLOR_BGR2RGB);
    _para para = initial_para();
    Mat bbs =  edgeBoxesImg(I, model, para);
    output(picname, bbs, I, model);
}

Mat edgeBoxesImg(Mat I, _model model, _para o) {
    clock_t begin = clock();
    model.opts.nms = 0;
    tuple<Mat, Mat, Mat, Mat> detect = edgesDetect(I, model, 4);
    Mat E, O, unuse1, unuse2;
    tie(E, O, unuse1, unuse2) = detect;
//    display the edge detection result
//    Mat E_norm;
//    normalize(E,E_norm,0,1,NORM_MINMAX,-1);
//    imshow("dfsa", E_norm);
//    waitKey(60000);

    E = edgesNms(E, O, 2, 0, 1, model.opts.nThreads);
    Mat bbs;
    bbs = parts_localization_main(E, O, o);
    return bbs;
}

void output(string picname, Mat bbs, Mat I, _model model){
    for (int i = 0; i < 5; i++) {
        Point2f p1(bbs.at<float>(i, 0), bbs.at<float>(i, 1));
        Point2f p2(bbs.at<float>(i, 0) + bbs.at<float>(i, 2), bbs.at<float>(i, 1) + bbs.at<float>(i, 3));
        rectangle(I, p1, p2, 1);
    }
    //store bbs in csv file if needed
    string folder ="data/";
    string suffix = "bbs.csv";
    string filename = picname.erase(0,9);
    string picsuffix = "_result.jpg";
    string outpic = "pictures/"+filename+picsuffix;
    unsigned long deletepicsuffixpos = filename.find(".");
    filename.erase(deletepicsuffixpos,filename.length()-deletepicsuffixpos);
    string output = folder+filename+suffix;
    writeout(output,bbs,"csv");
    imwrite(outpic, I);
    //display the box, the picture stays for one minute
    if(model.opts.showpic == 1){
        imshow("bboxs", I);
        waitKey(model.opts.showtime*1000);
    }
}