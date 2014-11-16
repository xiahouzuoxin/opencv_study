/*
 * FileName : sobel.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 16 Nov 2014 09:53:16 AM CST
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
        cout << "Usage: ./sobel [image file]" <<endl;
        return -1;
    }
    // Read image
    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout << "Error: read image" << endl;
        return -1;
    }
    cvtColor(src, src, CV_RGB2GRAY);
    namedWindow("Origin", 0);
    imshow("Origin",src);

    // CV_EXPORTS_W void Sobel( InputArray src, OutputArray dst, int ddepth,
    //                      int dx, int dy, int ksize=3,
    //                      double scale=1, double delta=0,
    //                      int borderType=BORDER_DEFAULT );
    Mat dst_x;
    // Gradient X
    Sobel(src, dst_x, src.depth(), 1, 0, 3, 1, 0, BORDER_DEFAULT);
    namedWindow("Sobel image X gradient", 0);
    imshow("Sobel image X gradient", dst_x);
    Mat dst_y;
    // Gradient Y
    Sobel(src, dst_y, src.depth(), 0, 1, 3, 1, 0, BORDER_DEFAULT);
    namedWindow("Sobel image Y gradient", 0);
    imshow("Sobel image Y gradient", dst_y);

    Mat dst;
    // Method one: |G|=|Gx|+|Gy|
    convertScaleAbs(dst_x, dst_x);
    convertScaleAbs(dst_y, dst_y);
    addWeighted(dst_x, 0.5, dst_y, 0.5, 0, dst);
    namedWindow("Sobel image XY", 0);
    imshow("Sobel image XY", dst);
    // Method two:
    Sobel(src, dst, src.depth(), 1, 1, 3, 1, 0, BORDER_DEFAULT);

    waitKey();

    return 0;
}

