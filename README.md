

###Introduction

 This code is for part center localization and part orientation recognition using deep learning. 
 The input is an RGB image with parts, the system will output top 5 confident parts detection with their centered points and orientations.

###Dependencies

[Opencv2](http://opencv.org/downloads.html)
 is required. The installation documentation can be find [here](http://docs.opencv.org/2.4/doc/tutorials/introduction/table_of_content_introduction/table_of_content_introduction.html).
 (Note: opencv 3 is also plausible if the writeout function in gadgets.cpp is removed.)
And you need to install the matiolib. Download the [matio package](https://sourceforge.net/projects/matio/), and just switch to the matio folder, and execute the following commands:

If you are using Mac OS with homebrew, just use brew install to install opencv2 and libmatio.

Please install [torch](http://torch.ch/) with luajit as instructed in ~/torch.

###Getting Started
Switch to the main folder, and type the following command to run compile and run:
```code:
$ cmake .
$ make
$ ./parts_localization
```
Remember to delete CMakeCache.txt if needed.

If you want to use GPU, just uncomment the `add_definitions(-DWITH_GPU)` in CMakeList.txt.(Bugs May Happen!)

The pictures can be add to the pictures folder and modify the main.cpp a little.
The default setting is show the picture for 1 minute.
The output bbox infomation in stored in data folder as csv format.
If you want to see the pic immediately, set the showpic para to be 1.
The picture result with bbox and orientation is stored in pictures folder.

The csv file contains five column:
the first two is the left corner coordinates, 
the next two is width and height and 
the last one is scores.
And the boxes is stored in score order from high to low.




###Organization
```code:
parts localization
├── edgesDetect.cpp
├── edgesDetectMex.cpp
├── parts_localization.cpp
├── parts_localization_main.cpp
├── edgesChns.cpp
├── edgesNmsMex.cpp
├── gadgets.cpp
├── main.cpp
├── get_orientation.lua
└── tools
    ├── ConvTri.cpp
    ├── convConst.cpp
    ├── gradient.cpp
    ├── gradientMex.cpp
    ├── imPadMex.cpp
    └── rgbConvertMex.cpp
```
Tools folder contains function for image processing.
The gadgets.cpp file contains function about loading model, type conversion and initialize
parameters. Parameters can be changed in initial_para() function in gadgets.cpp.
