/*
 * FileName : read.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 13 May 2014 07:34:25 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img;

    img = imread(argv[1], 1);

    if (argc != 2 || !img.data) {
        cout<<"No image data.\n"<<endl;
        return -1;
    }

    namedWindow("Display Image", CV_WINDOW_AUTOSIZE);
    imshow("Display Image", img);

    waitKey(0);

    return 0;
}

