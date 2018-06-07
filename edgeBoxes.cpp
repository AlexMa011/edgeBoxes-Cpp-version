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

Mat edgebox_main(Mat, Mat, _para);

Mat edgesNms(Mat, Mat, int, int, float, int);


void writeout(string, Mat, const char *);


void edgebox(string picname, _model model, _para o) {
    Mat I = imread(picname);
    assert(I.rows != 0 && I.cols != 0);

    clock_t begin = clock();
    model.opts.nms = 1;
    Mat I_resize;
    float shrink = 4;
    resize(I, I_resize, Size(), 1/shrink, 1/shrink);
    tuple<Mat, Mat, Mat, Mat> detect = edgesDetect(I_resize, model, 4);
    Mat E, O, unuse1, unuse2;
    tie(E, O, unuse1, unuse2) = detect;
    E = edgesNms(E, O, 2, 0, 1, model.opts.nThreads);
    Mat bbs;
	cout << 1 << endl;
    bbs = edgebox_main(E, O, o) * shrink;
    cout << "time:" << ((double) clock() - begin) / CLOCKS_PER_SEC << "s" << endl;

    string picsuffix = ".jpg";
    unsigned long picfolderxpos = picname.find("/");
    string filename = picname.erase(0, picfolderxpos + 1);
    unsigned long picsuffixpos = filename.find(".");
    filename.erase(picsuffixpos, filename.length() - picsuffixpos);

    Mat I_draw;
    I.copyTo(I_draw);


    //for top10 box scores

    for (int i = 0; i < model.opts.showboxnum; i++) {

        //draw the bbox
        Point2f p1(bbs.at<float>(i, 0), bbs.at<float>(i, 1));
        Point2f p2(bbs.at<float>(i, 0) + bbs.at<float>(i, 2), bbs.at<float>(i, 1) + bbs.at<float>(i, 3));
        Point2f p3(bbs.at<float>(i, 0), bbs.at<float>(i, 1) + bbs.at<float>(i, 3));
        Point2f p4(bbs.at<float>(i, 0) + bbs.at<float>(i, 2), bbs.at<float>(i, 1));


        int tlx = (int) bbs.at<float>(i, 0);
        int tly = (int) bbs.at<float>(i, 1);
		//brx may be bigger than I.cols-1
		//bry may be bigger than I.rows-1
        int brx = std::min((int) (bbs.at<float>(i, 0) + bbs.at<float>(i, 2)),I.cols-1);
        int bry = std::min((int) (bbs.at<float>(i, 1) + bbs.at<float>(i, 3)),I.rows-1);

        Mat box;			
        box = I.colRange(tlx, brx).rowRange(tly, bry);	

        rectangle(I_draw, p1, p2,Scalar(0,255,0), 1);
        Point2f ptext(bbs.at<float>(i, 0), bbs.at<float>(i, 1)-3);
        putText(I_draw,to_string(bbs.at<float>(i,4)),ptext,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,255,0),1);

    }


    //store bbs in csv file if needed
    string folder = "output/";
    string outpic = folder + filename + "_result" + picsuffix;
    string outedges = folder + filename + "_edges" + picsuffix;
    imwrite(outpic, I_draw);
    double E_min,E_max;
    cv::minMaxLoc(E, &E_min, &E_max);
    Mat E_draw = (E-E_min)/(E_max-E_min)*255;
    E_draw.convertTo(E_draw, CV_8U);
    imwrite(outedges, E_draw);
    //display the box, the picture stays for one minute
    if (model.opts.showpic == 1) {
        imshow("boxs", I_draw);
        waitKey(model.opts.showtime * 1000);
    }


    I_draw.release();

}


