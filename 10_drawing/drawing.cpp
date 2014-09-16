/*
 * FileName : random_gen.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 29 Jul 2014 08:31:41 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;


const char wndname[] = "Drawing";
const int RAND_N = 100;

void help(void)
{
    cout<<"Usage:./drawing"<<endl;
}

static Scalar random_color(RNG& rng)
{
    int icolor = (unsigned)rng;

    return Scalar(icolor&0xFF, (icolor>>8)&0xFF, (icolor>>16)&0xFF);
}

int main(int argc, char *argv[])
{
    int line_type = CV_AA;
    int i = 0;
    int width = 1000;
    int height = 700;
    int x1 = -width/2;
    int x2 = width*3/2;
    int y1 = -height/2;
    int y2 = height*3/2;
    const int DELAY = 10;

    RNG rng(0xFFFFFFFF);
    Mat image = Mat::zeros(height, width, CV_8UC3);

    imshow(wndname, image);
    waitKey(DELAY);
    
    for (i=0; i<RAND_N; i++) {
        Point pt1;
        Point pt2;

        pt1.x = rng.uniform(x1, x2);
        pt1.y = rng.uniform(y1, y2);
        pt2.x = rng.uniform(x1, x2);
        pt2.y = rng.uniform(y1, y2);

        line(image, pt1, pt2, random_color(rng), rng.uniform(1,5), line_type);
    }
    imshow(wndname, image);
    waitKey(0);

    for (i=0; i<RAND_N; i++) {
    Point org;
    org.x = rng.uniform(x1, x2);
    org.y = rng.uniform(y1, y2);
    putText(image, "OpenCV",org, rng.uniform(0,8),rng.uniform(0,10)*0.5+0.1, 
            random_color(rng), rng.uniform(1, 10), line_type);
    }

    imshow(wndname, image);
    waitKey(0);
    return 0;
}
