/*
 * FileName : /home/xiahouzuoxin/opencv_study/20_facedector/hough_dialog.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Mon 22 Dec 2014 11:34:42 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include <highgui.h>
#include "imgproc/imgproc.hpp"
#include "hough_dialog.h"

using namespace cv;

HoughDialog::HoughDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }

    int diag_len = pimage->cols+pimage->rows;

    /* Default value */
    rho = 1;
    theta = 1;
    thr = 200;
    ksize = 1;
    lthr = 100;
    hthr = 200;

    /* Label */
    rhoLabel = new QLabel(tr("rho"));
    thetaLabel = new QLabel(tr("theta"));
    thrLabel = new QLabel(tr("thr"));
    ksizeLabel = new QLabel(tr("ksize"));
    lthrLabel = new QLabel(tr("lthr"));
    hthrLabel = new QLabel(tr("hthr"));

    /* Slider */
    rhoSlider = new QSlider(Qt::Horizontal);
    rhoSlider->setRange(1, diag_len);
    rhoSlider->setValue(rho);
    thetaSlider = new QSlider(Qt::Horizontal);
    thetaSlider->setRange(1, 360);
    thetaSlider->setValue(theta);
    thrSlider = new QSlider(Qt::Horizontal);
    thrSlider->setRange(1, diag_len);
    thrSlider->setValue(thr);

    ksizeSlider = new QSlider(Qt::Horizontal);
    ksizeSlider->setRange(1, 15);
    ksizeSlider->setValue(ksize);
    lthrSlider = new QSlider(Qt::Horizontal);
    lthrSlider->setRange(0, diag_len);
    lthrSlider->setValue(lthr);
    hthrSlider = new QSlider(Qt::Horizontal);
    hthrSlider->setRange(0, diag_len);
    hthrSlider->setValue(hthr);

    /* SpinBox */
    rhoEdit = new QSpinBox();
    rhoEdit->setValue(rho);
    rhoEdit->setRange(1, diag_len);  // Resolution: 1 pixel
    thetaEdit = new QSpinBox();
    thetaEdit->setValue(theta);
    thetaEdit->setRange(1, 360);  // Resolution: 1 degree
    thrEdit = new QSpinBox();
    thrEdit->setValue(thr);
    thrEdit->setRange(1, diag_len);

    ksizeEdit = new QSpinBox();
    ksizeEdit->setRange(1, 15);
    ksizeEdit->setValue(ksize);
    lthrEdit = new QSpinBox();
    lthrEdit->setRange(0, diag_len);
    lthrEdit->setValue(lthr);
    hthrEdit = new QSpinBox();
    hthrEdit->setRange(0, diag_len);
    hthrEdit->setValue(hthr);

    /* Connections */
    connect(rhoSlider, SIGNAL(valueChanged(int)), this, SLOT(rhoChanged(int)));
    connect(rhoSlider, SIGNAL(valueChanged(int)), rhoEdit, SLOT(setValue(int)));
    connect(thetaSlider, SIGNAL(valueChanged(int)), this, SLOT(thetaChanged(int)));
    connect(thetaSlider, SIGNAL(valueChanged(int)), thetaEdit, SLOT(setValue(int)));
    connect(thrSlider, SIGNAL(valueChanged(int)), this, SLOT(thrChanged(int)));
    connect(thrSlider, SIGNAL(valueChanged(int)), thrEdit, SLOT(setValue(int)));

    connect(rhoEdit, SIGNAL(valueChanged(int)), this, SLOT(rhoChanged(int)));
    connect(rhoEdit, SIGNAL(valueChanged(int)), rhoSlider, SLOT(setValue(int)));
    connect(thetaEdit, SIGNAL(valueChanged(int)), this, SLOT(thetaChanged(int)));
    connect(thetaEdit, SIGNAL(valueChanged(int)), thetaSlider, SLOT(setValue(int)));
    connect(thrEdit, SIGNAL(valueChanged(int)), this, SLOT(thrChanged(int)));
    connect(thrEdit, SIGNAL(valueChanged(int)), thrSlider, SLOT(setValue(int)));

    connect(ksizeSlider, SIGNAL(valueChanged(int)), this, SLOT(ksizeChanged(int)));
    connect(ksizeSlider, SIGNAL(valueChanged(int)), ksizeEdit, SLOT(setValue(int)));
    connect(lthrSlider, SIGNAL(valueChanged(int)), this, SLOT(lthrChanged(int)));
    connect(lthrSlider, SIGNAL(valueChanged(int)), lthrEdit, SLOT(setValue(int)));
    connect(hthrSlider, SIGNAL(valueChanged(int)), this, SLOT(hthrChanged(int)));
    connect(hthrSlider, SIGNAL(valueChanged(int)), hthrEdit, SLOT(setValue(int)));

    connect(ksizeEdit, SIGNAL(valueChanged(int)), this, SLOT(ksizeChanged(int)));
    connect(ksizeEdit, SIGNAL(valueChanged(int)), ksizeSlider, SLOT(setValue(int)));
    connect(lthrEdit, SIGNAL(valueChanged(int)), this, SLOT(lthrChanged(int)));
    connect(lthrEdit, SIGNAL(valueChanged(int)), lthrSlider, SLOT(setValue(int)));
    connect(hthrEdit, SIGNAL(valueChanged(int)), this, SLOT(hthrChanged(int)));
    connect(hthrEdit, SIGNAL(valueChanged(int)), hthrSlider, SLOT(setValue(int)));

    /* Button actions */
    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    okButton->setEnabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
    moreButton = new QPushButton(tr("&More>>"));
    connect(moreButton, SIGNAL(clicked()), this, SLOT(moreClicked()));

    /* default visiable layout */
    QVBoxLayout *LeftLayout = new QVBoxLayout();
    LeftLayout->addWidget(rhoLabel);
    LeftLayout->addWidget(thetaLabel);
    LeftLayout->addWidget(thrLabel);
    QVBoxLayout *MidLayout = new QVBoxLayout();
    MidLayout->addWidget(rhoSlider);
    MidLayout->addWidget(thetaSlider);
    MidLayout->addWidget(thrSlider);
    QVBoxLayout *RightLayout = new QVBoxLayout();
    RightLayout->addWidget(rhoEdit);
    RightLayout->addWidget(thetaEdit);
    RightLayout->addWidget(thrEdit);

    QHBoxLayout *topLayout = new QHBoxLayout(); 
    topLayout->addLayout(LeftLayout);
    topLayout->addLayout(MidLayout);
    topLayout->addLayout(RightLayout);
    topLayout->addStretch();

    QVBoxLayout *bntLayout = new QVBoxLayout();
    bntLayout->addWidget(okButton);
    bntLayout->addWidget(closeButton);
    bntLayout->addWidget(moreButton);
    bntLayout->addStretch();

    //QHBoxLayout *defaultLayout = new QHBoxLayout();
    //defaultLayout->addLayout(topLayout);
    //defaultLayout->addLayout(bntLayout);

    /* extension layout */
    QVBoxLayout *eLeftLayout = new QVBoxLayout();
    eLeftLayout->addWidget(ksizeLabel);
    eLeftLayout->addWidget(lthrLabel);
    eLeftLayout->addWidget(hthrLabel);

    QVBoxLayout *eMidLayout = new QVBoxLayout();
    eMidLayout->addWidget(ksizeSlider);
    eMidLayout->addWidget(lthrSlider);
    eMidLayout->addWidget(hthrSlider);

    QVBoxLayout *eRightLayout = new QVBoxLayout();
    eRightLayout->addWidget(ksizeEdit);
    eRightLayout->addWidget(lthrEdit);
    eRightLayout->addWidget(hthrEdit);
   
    QHBoxLayout *ebtmLayout = new QHBoxLayout(); 
    ebtmLayout->addLayout(eLeftLayout);
    ebtmLayout->addLayout(eMidLayout);
    ebtmLayout->addLayout(eRightLayout);

    ex_win = new QGroupBox(tr("&Canny"));
    ex_win->setLayout(ebtmLayout);
    ex_win->setVisible(false);

    /* main layout */
    QVBoxLayout *mainLeftLayout = new QVBoxLayout();
    mainLeftLayout->addLayout(topLayout);
    mainLeftLayout->addWidget(ex_win);
    mainLeftLayout->addStretch();

    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(mainLeftLayout);
    mainLayout->addLayout(bntLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    setWindowTitle(tr("Hough Line Check"));
    //setFixedHeight(sizeHint().height());
}

void HoughDialog::okClicked()
{
    this->close();
    emit dialogClosed();
}

void HoughDialog::closeClicked()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit dialogClosed();
}

void HoughDialog::moreClicked()
{
    if (ex_win->isHidden()) {
        ex_win->show();
    } else {
        ex_win->hide();
    }
    setLayout(mainLayout);
}

void HoughDialog::rhoChanged(int value)
{
    this->rho = value * rho_step;    
    hough();
}

void HoughDialog::thetaChanged(int value)
{
    this->theta = value * theta_step;
    hough();
}

void HoughDialog::thrChanged(int value)
{
    this->thr = value * thr_step;
    hough();
}


void HoughDialog::ksizeChanged(int value)
{
    this->ksize = 1 + value * ksize_step;
    hough();
}

void HoughDialog::lthrChanged(int value)
{
    this->lthr = value * lthr_step;
    hough();
}

void HoughDialog::hthrChanged(int value)
{
    this->hthr = value * hthr_step;
    hough();
}

void HoughDialog::hough()
{
    Mat tmp;
    GaussianBlur(gray_image, tmp, Size(ksize,ksize), 0, 0);
    Canny(tmp, tmp, lthr,hthr,3); 

    vector<Vec2f> lines;
    HoughLines(tmp, lines, rho, theta, thr);

    image.copyTo(*pimage);
    for (size_t i=0; i<lines.size(); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1,pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = rho*a;
        double y0 = rho*b;
        pt1.x = cvRound(x0+1000*(-b));
        pt1.y = cvRound(y0+1000*a);
        pt2.x = cvRound(x0-1000*(-b));
        pt2.y = cvRound(y0-1000*a);
        line(*pimage, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }

    emit statusChanged();
}

