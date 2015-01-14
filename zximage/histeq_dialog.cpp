/*
 * FileName : histeq_dialog.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Mon 29 Dec 2014 04:01:36 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "histeq_dialog.h" 
#include "imgproc/imgproc.hpp"
#include <highgui.h>

static float range[] = {0,255};
static const float *histRange = {range};
static int histSize = 255;
//static bool uniform = true;
//static bool accumulate = false;
const char *win_hist = "histogram";

using namespace cv;

HisteqDialog::HisteqDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }
    /* Display hist graph of origin image */
    hist_graph();

    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    okButton->setEnabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
    execButton = new QPushButton(tr("&Histeq"));
    connect(execButton, SIGNAL(clicked()), this, SLOT(histeq()));

    QVBoxLayout *bntLayout = new QVBoxLayout();
    bntLayout->addWidget(execButton);
    bntLayout->addWidget(okButton);
    bntLayout->addWidget(closeButton);
    bntLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(bntLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Hist Equalization"));
    setFixedHeight(sizeHint().height());
}

void HisteqDialog::hist_graph_gray(Mat& img, Mat& hist)
{
    CV_Assert(img.channels()==1);

    calcHist(&img, 1,0, Mat(), hist, 1, &histSize, &histRange, true, false);

    int hist_w = 400;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);

    Mat histImage(hist_w,hist_h,CV_8UC3, Scalar(0,0,0));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    // Draw
    for (int i=1; i<histSize; i++) {
        line(histImage, Point(bin_w*(i-1),hist_h-cvRound(hist.at<float>(i-1))),
                Point(bin_w*(i), hist_h-cvRound(hist.at<float>(i))), Scalar(255,255,255),2,8,0);
    }

    namedWindow(win_hist);
    imshow(win_hist, histImage);
    //waitKey();

    //cvtColor(histImage, histImage, CV_BGR2RGB);
    //QImage qimg = QImage((const unsigned char *)(histImage.data), histImage.cols, histImage.rows,
    //        histImage.cols*histImage.channels(), QImage::Format_RGB888);
    //label->setPixmap(QPixmap::fromImage(qimg));
}

void HisteqDialog::hist_graph_color(Mat& img, Mat *rgb_hists)
{
    CV_Assert(img.channels()==3);

    vector<Mat> rgb_planes;
    split(img, rgb_planes);

    calcHist(&rgb_planes[0], 1,0, Mat(), rgb_hists[0], 1, &histSize, &histRange, true, false);
    calcHist(&rgb_planes[1], 1,0, Mat(), rgb_hists[1], 1, &histSize, &histRange, true, false);
    calcHist(&rgb_planes[2], 1,0, Mat(), rgb_hists[2], 1, &histSize, &histRange, true, false);

    int hist_w = 400;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);

    Mat histImage(hist_w,hist_h,CV_8UC3, Scalar(0,0,0));
    normalize(rgb_hists[0], rgb_hists[0], 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(rgb_hists[1], rgb_hists[1], 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(rgb_hists[2], rgb_hists[2], 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // Draw
    for (int i=1; i<histSize; i++) {
        line(histImage, Point(bin_w*(i-1),hist_h-cvRound(rgb_hists[0].at<float>(i-1))),
                Point(bin_w*(i), hist_h-cvRound(rgb_hists[0].at<float>(i))), Scalar(255,0,0),2,8,0);
        line(histImage, Point(bin_w*(i-1),hist_h-cvRound(rgb_hists[1].at<float>(i-1))),
                Point(bin_w*(i), hist_h-cvRound(rgb_hists[1].at<float>(i))), Scalar(0,255,0),2,8,0);
        line(histImage, Point(bin_w*(i-1),hist_h-cvRound(rgb_hists[2].at<float>(i-1))),
                Point(bin_w*(i), hist_h-cvRound(rgb_hists[2].at<float>(i))), Scalar(0,0,255),2,8,0);
    }

    namedWindow(win_hist);
    imshow(win_hist, histImage);
}

void HisteqDialog::hist_graph()
{
    /* Display hist graph of origin image */
    if (pimage->channels()==3) {
        Mat hist[3];
        hist_graph_color(*pimage, hist);
    } else if (pimage->channels()==1) {
        Mat hist;
        hist_graph_gray(*pimage, hist);
    }
}

void HisteqDialog::histeq_gray(Mat& img)
{
    CV_Assert(img.channels()==1);

    equalizeHist(img, img);
}

void HisteqDialog::histeq_color(Mat& img)
{
    CV_Assert(img.channels()==3);

    vector<Mat> rgb_planes;
    split(img, rgb_planes);

    equalizeHist(rgb_planes[0], rgb_planes[0]);
    equalizeHist(rgb_planes[1], rgb_planes[1]);
    equalizeHist(rgb_planes[2], rgb_planes[2]);
    
    merge(rgb_planes, img); 
}

void HisteqDialog::histeq()
{
    if (pimage->channels()==3) {
        histeq_color(*pimage);
    } else if (pimage->channels()==1) {
        histeq_gray(*pimage);
    }
    hist_graph();

    emit statusChanged();
}

void HisteqDialog::okClicked()
{
    destroyWindow(win_hist);
    this->close();
    emit dialogClosed();
}

void HisteqDialog::closeClicked()
{
    image.copyTo(*pimage);
    emit statusChanged();

    destroyWindow(win_hist);
    this->close();
    emit dialogClosed();
}

