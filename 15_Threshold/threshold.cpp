/*
 * FileName : filter_and_threshold.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sat 20 Sep 2014 07:04:29 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat src,gray,dst;

const char *wn = "Demo";
int th_val = 0;
int th_type = 3;
int const max_val = 255;
int const max_type = 4;
int const max_BINARY_val = 255;

static void Thresh(int, void *)
{
	/*
	 * 0: Binary
	 * 1: Binary Inverted
	 * 2: Threshold Truncated
	 * 3: Threshold to Zero
	 * 4: Threshold to Zero Inverted
	 */
	
	threshold(gray, dst, th_val, max_BINARY_val, th_type);

	imshow(wn, dst);
}

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage: ./threshold [file name]"<<endl;
        return -1;
    }

	// read image as GRAYSCALE
	src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout<<"Error: read data"<<endl;
        return -1;
    }

	// window to display
	namedWindow(wn);
	createTrackbar("Value", wn, &th_val, max_val, Thresh);  /* bar */
	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted", 
            wn, &th_type, max_type, Thresh);

    cvtColor(src, gray, CV_RGB2GRAY);

	// Init by Calling Thresh
	Thresh(0, 0);

	// wait if ESC be pressed
	while(1)
	{
		char c = waitKey(20);

		if(c == 27)         /* ESC */
		{
			break;
		}
	}
}

