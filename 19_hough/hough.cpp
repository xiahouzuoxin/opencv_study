/*
 * FileName : hough.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Wed 26 Nov 2014 09:52:45 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h" 
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage: ./hough [image file name]"<<endl;
        return -1;
    }

    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout<<"Read image error"<<endl;
        return -1;
    }
    namedWindow("Source", CV_WINDOW_AUTOSIZE);
    imshow("Source", src);

    Mat img;
    cvtColor(src, img, CV_RGB2GRAY); 
    GaussianBlur(img, img, Size(3,3), 0, 0);
    Canny(img, img, 100, 200, 3);
    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    imshow("Canny", img);

    vector<Vec2f> lines;
    HoughLines(img, lines, 1, CV_PI/360, 200);
    for (size_t i=0; i<lines.size(); i++) {
        float rho = lines[i][0]; 
        float theta = lines[i][1];
        Point pt1,pt2;
        double a=cos(theta);
        double b=sin(theta);
        double x0 = rho*a;
        double y0 = rho*b;
        pt1.x = cvRound(x0+1000*(-b));
        pt1.y = cvRound(y0+1000*a);
        pt2.x = cvRound(x0-1000*(-b));
        pt2.y = cvRound(y0-1000*a);
        line(src, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    } 
    namedWindow("Hough", CV_WINDOW_AUTOSIZE);
    imshow("Hough", src);

    waitKey();

    return 0;
}

