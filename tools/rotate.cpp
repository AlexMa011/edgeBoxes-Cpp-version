//
// Created by alexma on 14/11/2016.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Point2f RotatePoint1(const Point2f &p, float rad) {
    const float x = cos(rad) * p.x - sin(rad) * p.y;
    const float y = sin(rad) * p.x + cos(rad) * p.y;
    const Point2f rot_p(x, y);
    return rot_p;
}

Point2f RotatePoint(const Point2f &cen_pt, const Point2f &p, float rad) {
    const Point2f trans_pt = p - cen_pt;
    const Point2f rot_pt = RotatePoint1(trans_pt, rad);
    const Point2f fin_pt = rot_pt + cen_pt;

    return fin_pt;
}