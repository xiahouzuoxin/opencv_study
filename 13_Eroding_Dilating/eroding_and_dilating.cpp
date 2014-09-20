/*
 * FileName : eroding_and_dilating.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Fri 19 Sep 2014 07:42:12 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h" 
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

#define TYPE_MORPH_RECT      (0)
#define TYPE_MORPH_CROSS     (1)
#define TYPE_MORPH_ELLIPSE   (2)

#define MAX_ELE_TYPE         (2)
#define MAX_ELE_SIZE         (20)

Mat src, erode_dst, dilate_dst;

const char *erode_wn  = "eroding demo";
const char *dilate_wn = "dilating demo";

int erode_ele_type;
int dilate_ele_type;
int erode_ele_size;
int dilate_ele_size;

static void Erosion(int, void *);
static void Dilation(int, void *);

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage: ./eroding_and_dilating [file name]"<<endl;
        return -1;
    }

    src = imread(argv[1]);
    if (!src.data) {
        cout<<"Read image failure."<<endl;
        return -1;
    }

    // Windows
    namedWindow(erode_wn, WINDOW_AUTOSIZE);
    namedWindow(dilate_wn, WINDOW_AUTOSIZE);

    // Track Bar for Erosion
    createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", erode_wn, 
            &erode_ele_type, MAX_ELE_TYPE, Erosion);  // callback @Erosion
    createTrackbar("Element Size: 2n+1", erode_wn, 
            &erode_ele_size, MAX_ELE_SIZE, Erosion);

    // Track Bar for Dilation
    createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", dilate_wn, 
            &dilate_ele_type, MAX_ELE_TYPE, Dilation);  // callback @Erosion
    createTrackbar("Element Size: 2n+1", dilate_wn, 
            &dilate_ele_size, MAX_ELE_SIZE, Dilation);

    // Default start
    Erosion(0, 0);
    Dilation(0, 0);

    waitKey(0);

    return 0;
}

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
static void Erosion(int, void *)
{
    int erode_type;

    switch (erode_ele_type) {
    case TYPE_MORPH_RECT:
       erode_type = MORPH_RECT; 
       break;
    case TYPE_MORPH_CROSS:
       erode_type = MORPH_CROSS;
       break;
    case TYPE_MORPH_ELLIPSE:
       erode_type = MORPH_ELLIPSE;
       break;
    default:
       erode_type = MORPH_RECT;
       break;
    }

    Mat ele = getStructuringElement(erode_type, Size(2*erode_ele_size+1, 2*erode_ele_size+1), 
            Point(erode_ele_size, erode_ele_size));

    erode(src, erode_dst, ele);

    imshow(erode_wn, erode_dst);
}

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
static void Dilation(int, void *)
{
    int dilate_type;

    switch (dilate_ele_type) {
    case TYPE_MORPH_RECT:
       dilate_type = MORPH_RECT; 
       break;
    case TYPE_MORPH_CROSS:
       dilate_type = MORPH_CROSS;
       break;
    case TYPE_MORPH_ELLIPSE:
       dilate_type = MORPH_ELLIPSE;
       break;
    default:
       dilate_type = MORPH_RECT;
       break;
    }

    Mat ele = getStructuringElement(dilate_type, Size(2*dilate_ele_size+1, 2*dilate_ele_size+1), 
            Point(dilate_ele_size, dilate_ele_size));

    dilate(src, dilate_dst, ele);

    imshow(dilate_wn, dilate_dst);
}

