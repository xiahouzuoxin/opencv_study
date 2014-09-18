/*
 * FileName : image_smoothing.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Wed 17 Sep 2014 08:30:25 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h"
#include "imgproc/imgproc.hpp"
#include "highgui/highgui.hpp"

using namespace std;
using namespace cv;

const int MAX_KERNEL_LENGTH = 10;

const char *wn_name = "Smoothing";

static void salt(Mat &I, int n);
static void disp_caption(const char *wn_name, Mat src, const char *caption);
static void disp_image(const char *wn_name, Mat I);

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
int main(int argc, char *argv[])
{
    if (argc<2) {
        cout<<"Usage: ./image_smoothing [file name]"<<endl;
        return -1;
    }

    Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    salt(I, 6000);
    imshow(wn_name, I);
    waitKey(0);

    Mat dst;  // Result

    /* Homogeneous blur */
    disp_caption(wn_name, I, "Homogeneous blur");
    for (int i=1; i<MAX_KERNEL_LENGTH; i+=2) {
        blur(I, dst, Size(i, i), Point(-1,-1));
        disp_image(wn_name, dst);
    }

    /* Guassian blur */
    disp_caption(wn_name, I, "Gaussian blur");
    for (int i=1; i<MAX_KERNEL_LENGTH; i+=2) {
        GaussianBlur(I, dst, Size(i, i), 0, 0);
        disp_image(wn_name, dst);
    }

    /* Median blur */
    disp_caption(wn_name, I, "Median blur");
    for (int i=1; i<MAX_KERNEL_LENGTH; i+=2) {
        medianBlur(I, dst, i);
        disp_image(wn_name, dst);
    }

    /* Bilatrial blur */
    disp_caption(wn_name, I, "Bilatrial blur");
    for (int i=1; i<MAX_KERNEL_LENGTH; i+=2) {
        bilateralFilter(I, dst, i, i*2, i/2);
        disp_image(wn_name, dst);
    }
    waitKey(0);

    return 0;
}


/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
static void disp_caption(const char *wn_name, Mat src, const char *caption)
{
    Mat dst = Mat::zeros(src.size(), src.type());

    putText(dst, caption, Point(src.cols/4, src.rows/2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255));

    imshow(wn_name, dst);
    waitKey(0);
}



/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
static void disp_image(const char *wn_name, Mat I)
{
    imshow(wn_name, I);
    waitKey(1000);
}


/*
 * @brief   添加椒盐噪声
 * @inputs  
 * @outputs 
 * @retval  
 */
static void salt(Mat &I, int n=3000)
{
    for (int k=0; k<n; k++) {
        int i = rand() % I.cols;
        int j = rand() % I.rows;

        if (I.channels()) {
            I.at<uchar>(j,i) = 255;
        } else {
            I.at<Vec3b>(j,i)[0] = 255;
            I.at<Vec3b>(j,i)[1] = 255;
            I.at<Vec3b>(j,i)[2] = 255;
        }
    }
}
