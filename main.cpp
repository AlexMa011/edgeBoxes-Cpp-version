#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <string>
#include <cmath>
#include <tuple>
#include <fstream>
#include <ctime>
#include "model.h"


using namespace std;
using namespace cv;

_model loadmodel();


void parts_localization(string , _model );


int main() {
    //load model and set opts
    _model model = loadmodel();
    model.opts.sharpen = 0;
    model.opts.multiscale = 0;
    model.opts.nThreads = 4;
    model.opts.showpic = 0;
    model.opts.showtime = 60;
    cout<<"model loaded!"<<endl;
    //detect objects
    for(int i=1;i<5;i++){
        clock_t begin = clock();
        string picnum = to_string(i);
        string picname = "pictures/"+picnum+".jpg";
        parts_localization(picname, model);
        cout<<((double)clock()-begin)/CLOCKS_PER_SEC<<endl;
    }
    std::cout << "Done!" << std::endl;//for test
    return 0;
}

