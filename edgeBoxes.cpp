//
// Created by alexma on 26/10/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "model.h"



using namespace std;
using namespace cv;



_para initial_para();

tuple<Mat, Mat, Mat, Mat> edgesDetect(Mat, _model, int);

Mat parts_localization_main(Mat, Mat, _para);

Mat edgesNms(Mat, Mat, int, int, float, int);


void writeout(string, Mat, const char *);


void parts_localization(string picname, _model model, _para o) {
    Mat I = imread(picname);
    assert(I.rows != 0 && I.cols != 0);

    clock_t begin = clock();
    model.opts.nms = 0;
    Mat I_resize;
    float shrink = 1;
    resize(I, I_resize, Size(), 1/shrink, 1/shrink);
    tuple<Mat, Mat, Mat, Mat> detect = edgesDetect(I_resize, model, 4);
    //out << ((double) clock() - begin) / CLOCKS_PER_SEC << endl;
    Mat E, O, unuse1, unuse2;
    tie(E, O, unuse1, unuse2) = detect;
    //cout << ((double) clock() - begin) / CLOCKS_PER_SEC << endl;
    E = edgesNms(E, O, 2, 0, 1, model.opts.nThreads);
    Mat bbs;
    bbs = parts_localization_main(E, O, o) * shrink;
    //cout << ((double) clock() - begin) / CLOCKS_PER_SEC << endl;


    string picsuffix = ".jpg";
    unsigned long picfolderxpos = picname.find("/");
    string filename = picname.erase(0, picfolderxpos + 1);
    unsigned long picsuffixpos = filename.find(".");
    filename.erase(picsuffixpos, filename.length() - picsuffixpos);

    Mat I_draw;
    I.copyTo(I_draw);


    //for top10 box scores

    for (int i = 0; i < 5; i++) {

        //draw the bbox
        Point2f p1(bbs.at<float>(i, 0), bbs.at<float>(i, 1));
        Point2f p2(bbs.at<float>(i, 0) + bbs.at<float>(i, 2), bbs.at<float>(i, 1) + bbs.at<float>(i, 3));
        Point2f p3(bbs.at<float>(i, 0), bbs.at<float>(i, 1) + bbs.at<float>(i, 3));
        Point2f p4(bbs.at<float>(i, 0) + bbs.at<float>(i, 2), bbs.at<float>(i, 1));


        int tlx = (int) bbs.at<float>(i, 0);
        int tly = (int) bbs.at<float>(i, 1);
        int brx = (int) (bbs.at<float>(i, 0) + bbs.at<float>(i, 2));
        int bry = (int) (bbs.at<float>(i, 1) + bbs.at<float>(i, 3));

        Mat box;
        box = I.colRange(tlx, brx).rowRange(tly, bry);

        rectangle(I_draw, p1, p2, 1);

    }


    //store bbs in csv file if needed
    string folder = "output/";
    string suffix = "bbs.csv";
    string outpic = folder + filename + "_result" + picsuffix;
    string output = folder + filename + suffix;
    writeout(output, bbs, "csv");
    imwrite(outpic, I_draw);
    //display the box, the picture stays for one minute
    if (model.opts.showpic == 1) {
        imshow("boxs", I_draw);
        waitKey(model.opts.showtime * 1000);
    }


    I_draw.release();

}


