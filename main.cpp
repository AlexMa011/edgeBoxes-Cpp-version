#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "model.h"


using namespace std;
using namespace cv;

_model loadmodel();

_para initial_para();
void parts_localization(string, _model, _para);

tuple<int, int> siftflow(Mat image, int option, int pin);


int main() {

    cout << "Please waiting for the model to load!" << endl;

    //load model and set opts
    _model model = loadmodel();
    model.opts.sharpen = 0;
    model.opts.multiscale = 0;
    model.opts.nThreads = 4;
    model.opts.nTreesEval = 4;
    model.opts.showpic = 0;//set if show picture or not
    model.opts.showtime = 50;//in s
    model.opts.stride = 2;
    _para para = initial_para();
    cout << "model loaded!" << endl;



    string picname = "peppers.png";
    clock_t begin = clock();
    parts_localization(picname, model, para);
    cout << ((double) clock() - begin) / CLOCKS_PER_SEC << endl;
    std::cout << "Done!" << std::endl;//for test
    return 0;
}

