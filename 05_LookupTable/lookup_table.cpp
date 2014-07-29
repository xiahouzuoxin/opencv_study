/*
 * FileName : lookup_table.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 01 Jun 2014 04:35:37 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
 
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

#define QUAN_VAL1          (10)
#define QUAN_VAL2          (100)

void CreateLookupTable(Mat& table, uchar quan_val)
{
    table.create(1,256,CV_8UC1);
	
    uchar *p = table.data;
	for(int i = 0; i < 256; ++i)
	{
		p[i] = quan_val*(i/quan_val);
	}
}

int main(int argc, char *argv[])
{
    Mat img;
    Mat out1;
    Mat out2;

    if (argc < 2) {
        cout << "Please input image file name." << endl;
        return -1;
    }

    img = imread(argv[1], 1);


    Mat table;
    CreateLookupTable(table, QUAN_VAL1);
    LUT(img, table, out1);
    CreateLookupTable(table, QUAN_VAL2);
    LUT(img, table, out2);  // Call OpenCV function

    namedWindow("Lena", CV_WINDOW_NORMAL);
    imshow("Lena", img);
    namedWindow("QUAN_VAL=10", CV_WINDOW_NORMAL);
    imshow("QUAN_VAL=10", out1);
    namedWindow("QUAN_VAL=100", CV_WINDOW_NORMAL);
    imshow("QUAN_VAL=100", out2);

    waitKey(0);

    return 0;
}

