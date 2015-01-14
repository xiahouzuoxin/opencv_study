/*
 * FileName : /home/xiahouzuoxin/opencv_study/20_facedector/blur_dialog.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 23 Dec 2014 04:19:29 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "blur_dialog.h"
#include "imgproc/imgproc.hpp"
#include <highgui.h>

static void blur_bilateral(const cv::Mat& img, cv::Mat& dst, int ksize)
{
    cv::Mat tmp;
    cv::Mat out;

    pyrDown(img, tmp, cv::Size(cvRound(img.cols/2), cvRound(img.rows/2)));
    bilateralFilter(tmp, out, ksize, ksize*2, ksize/2);
    pyrUp(out, dst, cv::Size(out.cols*2, out.rows*2));
    //bilateralFilter(img, dst, ksize, ksize*2, ksize/2);
}

static void makeDepth32f(cv::Mat& source, cv::Mat& output)
{
    if (source.depth() != CV_32F) {
        source.convertTo(output, CV_32F);
    } else {
        output = source;
    }
}

/*
 * @brief  O(1) time implementation of guided filter 
 * @inputs 
 *   I: guidance image (should be a gray-scale/single channel image)
 *   p: filtering input image (should be a gray-scale/single channel image)
 *   r: local window radius
 *   eps: regularization parameter
 * @outputs 
 * @retval  
 */
static void guidedFilter(cv::Mat& output, cv::Mat& source, cv::Mat& guided_image, int radius, double epsilon)
{
   using namespace cv;

   CV_Assert(radius >= 2 && epsilon > 0);
   CV_Assert(source.data != NULL && source.channels() == 1);  
   CV_Assert(guided_image.channels() == 1);  
   CV_Assert(source.rows == guided_image.rows && source.cols == guided_image.cols);

   cv::Size win_size(2*radius+1, 2*radius+1);  

   //cv::Mat guided;
   //if (guided_image.data == source.data) {
   //    //make a copy  
   //    guided_image.copyTo(guided);  
   //} else {
   //    guided = guided_image;  
   //}

   //将输入扩展为32位浮点型，以便以后做乘法  
   cv::Mat source_32f, guided_32f;  
   makeDepth32f(source, source_32f); 
   makeDepth32f(guided_image, guided_32f);  

   //计算I*p和I*I  
   cv::Mat mat_Ip, mat_I2;  
   multiply(guided_32f, source_32f, mat_Ip);  
   multiply(guided_32f, guided_32f, mat_I2);  

   //计算各种均值  
   cv::Mat mean_p, mean_I, mean_Ip, mean_I2;  

   boxFilter(source_32f, mean_p, CV_32F, win_size);  
   boxFilter(guided_32f, mean_I, CV_32F, win_size);  
   boxFilter(mat_Ip, mean_Ip, CV_32F, win_size);  
   boxFilter(mat_I2, mean_I2, CV_32F, win_size);   

   //计算Ip的协方差和I的方差  
   cv::Mat cov_Ip = mean_Ip - mean_I.mul(mean_p);  
   cv::Mat var_I = mean_I2 - mean_I.mul(mean_I);  
   var_I += epsilon;  

   //求a和b  
   cv::Mat a, b;  
   divide(cov_Ip, var_I, a);  
   b = mean_p - a.mul(mean_I);  
 
   //对包含像素i的所有a、b做平均  
   cv::Mat mean_a, mean_b;  
   boxFilter(a, mean_a, CV_32F, win_size); 
   boxFilter(b, mean_b, CV_32F, win_size); 

   //计算输出 (depth == CV_32F)
   output = mean_a.mul(guided_32f) + mean_b;
}

BlurDialog::BlurDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }

    opt = OPT_HOMOGENEOUS;
    ksize = 1;

    /* QRadioButton */
    QGroupBox *radioGroup = new QGroupBox("Blur Operation", this);
    homogeneousBtn = new QRadioButton("Homogeneous");
    guassianBtn = new QRadioButton("Guassian");
    medianBtn = new QRadioButton("Median");
    bilateralBtn = new QRadioButton("Bilateral");
    guidedBtn = new QRadioButton("Guided");
    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->addWidget(homogeneousBtn);
    radioLayout->addWidget(guassianBtn);
    radioLayout->addWidget(medianBtn);
    radioLayout->addWidget(bilateralBtn);
    radioLayout->addWidget(guidedBtn);
    radioGroup->setLayout(radioLayout);
    radioGroup->setVisible(true);
    homogeneousBtn->setChecked(true);

    connect(guassianBtn, SIGNAL(clicked()), this, SLOT(setGuassianOpt()));
    connect(homogeneousBtn, SIGNAL(clicked()), this, SLOT(setHomogeneousOpt()));
    connect(medianBtn, SIGNAL(clicked()), this, SLOT(setMedianOpt()));
    connect(bilateralBtn, SIGNAL(clicked()), this, SLOT(setBilateralOpt()));
    connect(guidedBtn, SIGNAL(clicked()), this, SLOT(setGuidedOpt()));

    /* QSlider */
    ksizeLabel = new QLabel(tr("KernelSize(2n+1)"));
    ksizeSlider = new QSlider(Qt::Horizontal);
    ksizeSlider->setRange(0,cvRound(cv::min(img.cols,img.rows)/4));
    ksizeSlider->setValue(0);
    ksizeSBox = new QSpinBox();
    ksizeSBox->setRange(0,cvRound(cv::min(img.cols,img.rows)/4));
    ksizeSBox->setValue(0);

    connect(ksizeSlider, SIGNAL(valueChanged(int)), this, SLOT(ksizeChanged(int)));
    connect(ksizeSlider, SIGNAL(valueChanged(int)), ksizeSBox, SLOT(setValue(int)));
    connect(ksizeSBox, SIGNAL(valueChanged(int)), this, SLOT(ksizeChanged(int)));
    connect(ksizeSBox, SIGNAL(valueChanged(int)), ksizeSlider, SLOT(setValue(int)));

    QHBoxLayout *ksizeLayout = new QHBoxLayout();
    ksizeLayout->addWidget(ksizeLabel);
    ksizeLayout->addWidget(ksizeSlider);
    ksizeLayout->addWidget(ksizeSBox);

    /* Button actions */
    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    okButton->setEnabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));

    QHBoxLayout *bntLayout = new QHBoxLayout();
    bntLayout->addWidget(okButton);
    bntLayout->addWidget(closeButton);
    bntLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(radioGroup);
    mainLayout->addLayout(ksizeLayout);
    mainLayout->addLayout(bntLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Blur Operation"));
    setFixedHeight(sizeHint().height());
}

void BlurDialog::okClicked()
{
    this->close();
    emit dialogClosed();
}

void BlurDialog::closeClicked()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit dialogClosed();
}

void BlurDialog::blur_opt(void)
{
    switch (opt) {
    case OPT_HOMOGENEOUS:
        blur(image, *pimage, cv::Size(2*ksize+1,2*ksize+1), cv::Point(-1,-1));
        break;
    case OPT_GUASSIAN:
        GaussianBlur(image, *pimage, cv::Size(2*ksize+1,2*ksize+1), 0,0);
        break;
    case OPT_MEDIAN:
        medianBlur(image, *pimage, 2*ksize+1);
        break;
    case OPT_BILATERAL:
        blur_bilateral(image, *pimage, ksize);
        break;
    case OPT_GUIDED:
        guidedFilter(*pimage, gray_image, gray_image, ksize+2, 0.04);
        pimage->convertTo(*pimage, CV_8UC1, 1);
        break;
    default:
        break;
    }

    emit statusChanged();
}

void BlurDialog::setHomogeneousOpt()
{
    opt = OPT_HOMOGENEOUS;
    blur_opt();
}

void BlurDialog::setGuassianOpt()
{
    opt = OPT_GUASSIAN;
    blur_opt();
}

void BlurDialog::setMedianOpt()
{
    opt = OPT_MEDIAN;
    blur_opt();
}

void BlurDialog::setBilateralOpt()
{
    opt = OPT_BILATERAL;
    blur_opt();
}

void BlurDialog::setGuidedOpt()
{
    opt = OPT_GUIDED;
    blur_opt();
}

void BlurDialog::ksizeChanged(int value)
{
    ksize = value;
    blur_opt();
}

