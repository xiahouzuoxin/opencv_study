/*
 * FileName : Laplace.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 16 Nov 2014 10:52:09 AM CST
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
        cout << "Usage: ./Laplace [image file]" <<endl;
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
    // CV_EXPORTS_W void Laplacian( InputArray src, OutputArray dst, int ddepth,
    //                          int ksize=1, double scale=1, double delta=0,
    //                          int borderType=BORDER_DEFAULT );
    Laplacian(src, dst, src.depth(), 3, 1, 0, BORDER_DEFAULT);
    namedWindow("Laplacian", CV_WINDOW_AUTOSIZE);
    imshow("Laplacian",dst);

    waitKey();

    return 0;
}

