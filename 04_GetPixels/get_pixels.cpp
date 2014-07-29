/*
 * FileName : get_pixels.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 01 Jun 2014 06:40:54 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Usage: ./get_pixels [imag name]" << endl;
        return -1;
    }

    Mat img;
    
    img = imread(argv[1], 1);
    

    /*
     * Reverse pixels
     */
    Mat out1 = img.clone();  // change dst will not affect img

    long n_rows = out1.rows;
    long n_cols = out1.cols * out1.channels();

//    if (dst.isContinuous()) {
//        n_rows = 1;
//        n_cols = n_rows * n_cols;
//    }


    /*
     * Row pointer
     */
    uchar *p;
    for (long i=0; i<n_rows; i++) {
        p = out1.ptr<uchar>(i);
        for (long j=0; j<n_cols; j++) {
            p[j] = 255 - p[j];
        }
    }

    /*
     * Element pointer
     */
    Mat out2;
    out2.create(img.size(), img.type());  // reserve size and type but alloc new space

    n_rows = out2.rows;
    n_cols = out2.cols * out2.channels();

    p = out2.data;
    double c = 0.5;
    double b = 30;
    for (long i=0; i<n_rows*n_cols; i++) {
       *(p+i) = (uchar)(255 * 0.5 * ((double)(img.data[i]) / 255) + b);
    }

    /*
     * Display
     */
    namedWindow("src_image", CV_WINDOW_NORMAL);
    imshow("src_image", img);
    namedWindow("reverse_image", CV_WINDOW_NORMAL);
    imshow("reverse_image", out1);
    namedWindow("mici_image", CV_WINDOW_NORMAL);
    imshow("mici_image", out2);

    waitKey(0);

    return 0;
}

