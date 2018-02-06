#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "model.h"


using namespace std;
using namespace cv;

_model loadmodel();

_para initial_para();
void edgebox(string, _model, _para);

tuple<int, int> siftflow(Mat image, int option, int pin);


int main() {

    cout << "Please waiting for the model to load!" << endl;

    //load model and set opts
    _model model = loadmodel();
    model.opts.sharpen = 2;
    model.opts.multiscale = 0;
    model.opts.nThreads = 4;
    model.opts.nTreesEval = 4;
    model.opts.showpic = 1;//set if show picture or not
    model.opts.showtime = 10;//in s
    model.opts.stride = 2;
    model.opts.showboxnum = 15;
    _para para = initial_para();
    cout << "model loaded!" << endl;



    string picname = "img/peppers.png";
    edgebox(picname, model, para);
    std::cout << "Done!" << std::endl;//for test
    return 0;
}

