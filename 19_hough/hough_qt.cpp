/*
 * FileName : hough.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Wed 26 Nov 2014 09:52:45 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "cv.h" 
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

static QImage Mat2QImage(Mat& image)
{
    QImage img;

    if (image.channels()==3) {
        cvtColor(image, image, CV_BGR2RGB);
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_RGB888);
    } else if (image.channels()==1) {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_ARGB32);
    } else {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_RGB888);
    }

    return img;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *wn = new QWidget;
    wn->setWindowTitle("disp image");

    QString filename = QFileDialog::getOpenFileName(0, "Open File", "", "*.jpg *.png *.bmp", 0);
    if (filename.isNull()) {
        return -1;
    }

    Mat src = imread(filename.toAscii().data(), CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout<<"Read image error"<<endl;
        return -1;
    }
    //namedWindow("Source", CV_WINDOW_AUTOSIZE);
    //imshow("Source", src);

    Mat img;
    cvtColor(src, img, CV_RGB2GRAY); 
    GaussianBlur(img, img, Size(3,3), 0, 0);
    Canny(img, img, 100, 200, 3);
    //namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    //imshow("Canny", img);

    Mat dst;
    src.copyTo(dst);
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
        line(dst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    } 
    //namedWindow("Hough", CV_WINDOW_AUTOSIZE);
    //imshow("Hough", src);

    QImage qimg = Mat2QImage(src); 
    QLabel *label_src = new QLabel("",0);
    label_src->setPixmap(QPixmap::fromImage(qimg));

    qimg = Mat2QImage(img); 
    QLabel *label_canny = new QLabel("",0);
    label_canny->setPixmap(QPixmap::fromImage(qimg));

    qimg = Mat2QImage(dst); 
    QLabel *label_dst = new QLabel("",0);
    label_dst->setPixmap(QPixmap::fromImage(qimg));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label_src);
    layout->addWidget(label_canny);
    layout->addWidget(label_dst);
    wn->setLayout(layout);
    wn->show();

    waitKey();

    return app.exec();
}

