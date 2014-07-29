/*
 * FileName : MatObj.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 15 May 2014 09:12:45 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
    /*
     * Create Mat
     */
    Mat M(2,2,CV_8UC3, Scalar(0,0,255));
    cout << "M=" << endl << " " << M << endl << endl;

    /*
     * Matlab style
     */
    Mat E = Mat::eye(4,4,CV_64F);
    cout << "E=" << endl << " " << E << endl << endl;
    E = Mat::ones(4,4,CV_64F);
    cout << "E=" << endl << " " << E << endl << endl;
    E = Mat::zeros(4,4,CV_64F);
    cout << "E=" << endl << " " << E << endl << endl;


    /*
     * Convert IplImage to Mat
     */
    IplImage *img = cvLoadImage("../test_imgs/Lena.jpg");
    Mat L(img);
    namedWindow("Lena.jpg", CV_WINDOW_AUTOSIZE); 
    imshow("Lena.jpg", L);
    waitKey(0);

    /*
     * Init Mat with separated data
     */
    Mat C = (Mat_<int>(3,3) << 0,1,2,3,4,5,6,7,8);
    cout << "C=" << endl << " " << C << endl << endl;


    return 0;
}


