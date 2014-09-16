/*
 * FileName : fft2.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Wed 30 Jul 2014 09:42:12 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage:./fft2 [image name]"<<endl;
        return -1;
    }

    // Read as grayscale image
    Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << "Read image error"<<endl;
        return -1;
    }

    Mat padded;
    int m = getOptimalDFTSize(image.rows);  // Return size of 2^x that suite for FFT
    int n = getOptimalDFTSize(image.cols);
    // Padding 0, result is @padded
    copyMakeBorder(image, padded, 0, m-image.rows, 0, n-image.cols, BORDER_CONSTANT, Scalar::all(0));

    // Create planes to storage REAL part and IMAGE part, IMAGE part init are 0
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);

    dft(complexI, complexI);

    // compute the magnitude and switch to logarithmic scale
    split(complexI, planes);
    magnitude(planes[0], planes[0], planes[1]);
    Mat magI = planes[0];

    // => log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
    magI += Scalar::all(1);
    log(magI, magI);

    // crop the spectrum
    magI = magI(Rect(0, 0, magI.cols & (-2), magI.rows & (-2)));
    Mat _magI = magI.clone();
    normalize(_magI, _magI, 0, 1, CV_MINMAX);

    // rearrange the quadrants of Fourier image so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0,0,cx,cy));    // Top-Left
    Mat q1(magI, Rect(cx,0,cx,cy));   // Top-Right
    Mat q2(magI, Rect(0,cy,cx,cy));   // Bottom-Left
    Mat q3(magI, Rect(cx,cy,cx,cy));  // Bottom-Right

    // exchange Top-Left and Bottom-Right
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    
    // exchange Top-Right and Bottom-Left
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX);

    imshow("Input image", image);
    imshow("Spectrum magnitude before shift frequency", _magI);
    imshow("Spectrum magnitude after shift frequency", magI);
    waitKey();

    return 0;
}
