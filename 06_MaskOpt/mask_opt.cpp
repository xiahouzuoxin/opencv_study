/*
 * FileName : mask_opt.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Fri 25 Jul 2014 09:48:33 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>


using namespace std;
using namespace cv;

extern void Sharpen(const Mat& myImage, Mat& Result);

int main(int argc, char *argv[])
{
    Mat img;
    Mat result;

    if (argc < 2) {
        cout << "Please input image file name." << endl;
        return -1;
    }

    img = imread(argv[1], 1);


    Sharpen(img, result);

    namedWindow("image", CV_WINDOW_NORMAL);
    imshow("image", img);
    namedWindow("result", CV_WINDOW_NORMAL);
    imshow("result", result);

    waitKey(0);

    return 0;
}

