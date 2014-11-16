/*
 * FileName : canny.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 16 Nov 2014 10:59:31 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
 
#include <iostream>
#include "cv.h" 
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Usage: ./canny [image file]" <<endl;
        return -1;
    }
    // Read image
    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout << "Error: read image" << endl;
        return -1;
    }
    cvtColor(src, src, CV_RGB2GRAY);
    namedWindow("Origin", CV_WINDOW_AUTOSIZE);
    imshow("Origin",src);

    Mat dst;
    GaussianBlur(src, dst, Size(3,3), 0, 0);
    // CV_EXPORTS_W void Canny( InputArray image, OutputArray edges,
    //                      double threshold1, double threshold2,
    //                      int apertureSize=3, bool L2gradient=false );
    Canny(dst, dst, 50, 200, 3);
    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    imshow("Canny",dst);

    waitKey();

    return 0;
}
