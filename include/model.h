//
// Created by alexma on 21/10/2016.
//

#ifndef EDGEBOX_MODEL_H
#define EDGEBOX_MODEL_H

using namespace std;
using namespace cv;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

class _opt{
public:
    uint32 imWidth, gtWidth;
    uint32 nPos, nNeg, nImgs, nTrees;
    double fracFtrs;
    uint32 minCount, minChild;
    uint32 maxDepth;
    char* discretize;
    uint32 nSamples, nClasses;
    char* split;
    uint32 nOrients;
    uint32 grdSmooth, chnSmooth, simSmooth;
    uint32 normRad;
    uint32 shrink;
    uint32 nCells;
    uint32 rgbd;
    uint32 stride;
    uint32 multiscale;
    uint32 sharpen;
    uint32 nTreesEval;
    uint32 nThreads;
    uint32 nms;
    uint32 seed;
    uint32 useParfor;
    char* modelDir;
    char* modelFnm;
    char* bsdsDir;
    uint32 nChns, nChnFtrs, nSimFtrs, nTotFtrs;
    bool showpic;
    uint32 showtime;
};

class _model{
public:
    _opt opts;
    Mat thrs;
    Mat fids;
    Mat child;
    Mat count;
    Mat depth;
    Mat segs;
    Mat nSegs;
    Mat eBins;
    Mat eBnds;
};

class _para{
public:
    string name;
    float alpha;
    float beta;
    float eta;
    float minScore;
    int maxBoxes;
    float edgeMinMag;
    float edgeMergeThr;
    float clusterMinMag;
    float maxAspectRatio;
    float minBoxArea;
    float maxBoxLength;
    float gamma;
    float kappa;


};

#endif //EDGEBOX_MODEL_H
