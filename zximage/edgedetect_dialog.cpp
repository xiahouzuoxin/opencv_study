/*
 * FileName : /home/xiahouzuoxin/opencv_study/20_facedector/edge_detect.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Fri 19 Dec 2014 05:30:01 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "edgedetect_dialog.h" 
#include "imgproc/imgproc.hpp"
#include "highgui.h"

LOGDialog::LOGDialog(int ksize, double scale, double delta, QWidget *parent)
    : QDialog(parent)
{
    log_ksizeSlider = new QSlider(Qt::Horizontal);
    log_ksizeSlider->setRange(0,15);
    log_ksizeSlider->setValue(ksize);
    log_scaleSlider = new QSlider(Qt::Horizontal);
    log_scaleSlider->setRange(0,20);
    log_scaleSlider->setValue(scale);
    log_deltaSlider = new QSlider(Qt::Horizontal);
    log_deltaSlider->setRange(0,20);
    log_deltaSlider->setValue(delta);
    thrSlider = new QSlider(Qt::Horizontal);
    thrSlider->setRange(0,255);
    thrSlider->setValue(0);

    log_ksizeSBx = new QSpinBox();
    log_ksizeSBx->setRange(0,15);
    log_ksizeSBx->setValue(ksize);
    log_scaleSBx = new QSpinBox();
    log_scaleSBx->setRange(0,20);
    log_scaleSBx->setValue(scale);
    log_deltaSBx = new QSpinBox;
    log_deltaSBx->setRange(0,20);
    log_deltaSBx->setValue(delta);
    thrSBx = new QSpinBox;
    thrSBx->setRange(0,255);
    thrSBx->setValue(0);

    connect(log_ksizeSlider,SIGNAL(valueChanged(int)),parent,SLOT(log_ksizeChanged(int)));
    connect(log_scaleSlider,SIGNAL(valueChanged(int)),parent,SLOT(log_scaleChanged(int)));
    connect(log_deltaSlider,SIGNAL(valueChanged(int)),parent,SLOT(log_deltaChanged(int)));
    connect(thrSlider,SIGNAL(valueChanged(int)),parent,SLOT(log_thrChanged(int)));
    connect(log_ksizeSBx,SIGNAL(valueChanged(int)),parent,SLOT(log_ksizeChanged(int)));
    connect(log_scaleSBx,SIGNAL(valueChanged(int)),parent,SLOT(log_scaleChanged(int)));
    connect(log_deltaSBx,SIGNAL(valueChanged(int)),parent,SLOT(log_deltaChanged(int)));
    connect(thrSBx,SIGNAL(valueChanged(int)),parent,SLOT(log_thrChanged(int)));

    connect(log_ksizeSlider,SIGNAL(valueChanged(int)),log_ksizeSBx,SLOT(setValue(int)));
    connect(log_scaleSlider,SIGNAL(valueChanged(int)),log_scaleSBx,SLOT(setValue(int)));
    connect(log_deltaSlider,SIGNAL(valueChanged(int)),log_deltaSBx,SLOT(setValue(int)));
    connect(thrSlider,SIGNAL(valueChanged(int)),thrSBx,SLOT(setValue(int)));
    connect(log_ksizeSBx,SIGNAL(valueChanged(int)),log_ksizeSlider,SLOT(setValue(int)));
    connect(log_scaleSBx,SIGNAL(valueChanged(int)),log_scaleSlider,SLOT(setValue(int)));
    connect(log_deltaSBx,SIGNAL(valueChanged(int)),log_deltaSlider,SLOT(setValue(int)));
    connect(thrSBx,SIGNAL(valueChanged(int)),thrSlider,SLOT(setValue(int)));

    log_ksizeLabel = new QLabel(tr("ksize"));
    log_scaleLabel = new QLabel(tr("scale"));
    log_deltaLabel = new QLabel(tr("delta"));
    thrLabel = new QLabel(tr("thr  "));

    QHBoxLayout *log_ksizeLayout = new QHBoxLayout;
    log_ksizeLayout->addWidget(log_ksizeLabel);
    log_ksizeLayout->addWidget(log_ksizeSlider);
    log_ksizeLayout->addWidget(log_ksizeSBx);
    QHBoxLayout *log_scaleLayout = new QHBoxLayout;
    log_scaleLayout->addWidget(log_scaleLabel);
    log_scaleLayout->addWidget(log_scaleSlider);
    log_scaleLayout->addWidget(log_scaleSBx);
    QHBoxLayout *log_deltaLayout = new QHBoxLayout;
    log_deltaLayout->addWidget(log_deltaLabel);
    log_deltaLayout->addWidget(log_deltaSlider);
    log_deltaLayout->addWidget(log_deltaSBx);
    QHBoxLayout *log_thrLayout = new QHBoxLayout;
    log_thrLayout->addWidget(thrLabel);
    log_thrLayout->addWidget(thrSlider);
    log_thrLayout->addWidget(thrSBx);

    QVBoxLayout *logLayout = new QVBoxLayout();
    logLayout->addLayout(log_ksizeLayout);
    logLayout->addLayout(log_scaleLayout);
    logLayout->addLayout(log_deltaLayout);
    logLayout->addLayout(log_thrLayout);
    setLayout(logLayout);
}

CannyDialog::CannyDialog(int ksize, int lthr, int hthr, int max_lthr, int max_hthr, QWidget *parent) 
    : QDialog(parent)
{
    ksizeSlider = new QSlider(Qt::Horizontal);
    ksizeSlider->setRange(0,15);
    ksizeSlider->setValue(ksize);
    lthrSlider = new QSlider(Qt::Horizontal);
    lthrSlider->setRange(0,max_lthr);
    lthrSlider->setValue(lthr);
    hthrSlider = new QSlider(Qt::Horizontal);
    hthrSlider->setRange(0,max_hthr);
    hthrSlider->setValue(hthr);

    ksizeSBx = new QSpinBox();
    ksizeSBx->setRange(0,15);
    ksizeSBx->setValue(ksize);
    lthrSBx = new QSpinBox();
    lthrSBx->setRange(0,max_lthr);
    lthrSBx->setValue(lthr);
    hthrSBx = new QSpinBox;
    hthrSBx->setRange(0,max_hthr);
    hthrSBx->setValue(hthr);

    connect(ksizeSlider,SIGNAL(valueChanged(int)),parent,SLOT(canny_ksizeChanged(int)));
    connect(lthrSlider,SIGNAL(valueChanged(int)),parent,SLOT(canny_lthrChanged(int)));
    connect(hthrSlider,SIGNAL(valueChanged(int)),parent,SLOT(canny_hthrChanged(int)));
    connect(ksizeSBx,SIGNAL(valueChanged(int)),parent,SLOT(canny_ksizeChanged(int)));
    connect(lthrSBx,SIGNAL(valueChanged(int)),parent,SLOT(canny_lthrChanged(int)));
    connect(hthrSBx,SIGNAL(valueChanged(int)),parent,SLOT(canny_hthrChanged(int)));

    connect(ksizeSlider,SIGNAL(valueChanged(int)),ksizeSBx,SLOT(setValue(int)));
    connect(lthrSlider,SIGNAL(valueChanged(int)),lthrSBx,SLOT(setValue(int)));
    connect(hthrSlider,SIGNAL(valueChanged(int)),hthrSBx,SLOT(setValue(int)));
    connect(ksizeSBx,SIGNAL(valueChanged(int)),ksizeSlider,SLOT(setValue(int)));
    connect(lthrSBx,SIGNAL(valueChanged(int)),lthrSlider,SLOT(setValue(int)));
    connect(hthrSBx,SIGNAL(valueChanged(int)),hthrSlider,SLOT(setValue(int)));

    ksizeLabel = new QLabel(tr("ksize"));
    lthrLabel = new QLabel(tr("l_thr"));
    hthrLabel = new QLabel(tr("h_thr"));

    QHBoxLayout *ksizeLayout = new QHBoxLayout;
    ksizeLayout->addWidget(ksizeLabel);
    ksizeLayout->addWidget(ksizeSlider);
    ksizeLayout->addWidget(ksizeSBx);
    QHBoxLayout *lthrLayout = new QHBoxLayout;
    lthrLayout->addWidget(lthrLabel);
    lthrLayout->addWidget(lthrSlider);
    lthrLayout->addWidget(lthrSBx);
    QHBoxLayout *hthrLayout = new QHBoxLayout;
    hthrLayout->addWidget(hthrLabel);
    hthrLayout->addWidget(hthrSlider);
    hthrLayout->addWidget(hthrSBx);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(ksizeLayout);
    mainLayout->addLayout(lthrLayout);
    mainLayout->addLayout(hthrLayout);
    setLayout(mainLayout);
}

EdgedetectDialog::EdgedetectDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }

    log_ksize = 3;
    log_scale = 1;
    log_delta = 0;
    log_thr = 0;

    canny_ksize = 3;
    canny_lthr = 50;
    canny_hthr = 100;

    int max_lthr = pimage->cols + pimage->rows;
    int max_hthr = pimage->cols + pimage->rows;

    tabWidget = new QTabWidget();
    tabWidget->addTab(new LOGDialog(1, 2, 0,this),"LOG");
    tabWidget->addTab(new CannyDialog(1,50,200,max_lthr,max_hthr,this),"Canny"); 

    okButton = new QPushButton("&OK");
    okButton->setDefault(true);
    okButton->setEnabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));

    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeEdgedetect()));

    QVBoxLayout *top_layout = new QVBoxLayout();
    top_layout->addWidget(tabWidget);
    QHBoxLayout *btm_layout = new QHBoxLayout();
    btm_layout->addWidget(okButton);
    btm_layout->addWidget(closeButton);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(top_layout);
    layout->addLayout(btm_layout);

    this->setLayout(layout);
    this->setWindowTitle(tr("Edge Detect"));
    this->setFixedHeight(sizeHint().height());
}

void EdgedetectDialog::okClicked()
{
    this->close();
    emit dialogClosed();
}

void EdgedetectDialog::closeEdgedetect()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit dialogClosed();
}

void EdgedetectDialog::edge_detect(void)
{
    Laplacian(gray_image, *pimage, image.depth(), log_ksize, log_scale, log_delta, cv::BORDER_DEFAULT);
    threshold(*pimage, *pimage, log_thr, 255, 0);

    emit statusChanged();
}

void EdgedetectDialog::log_ksizeChanged(int ksize)
{
    this->log_ksize = 1 + ksize * log_ksize_step;
    edge_detect();
}

void EdgedetectDialog::log_scaleChanged(int scale)
{
    this->log_scale = scale * log_scale_step;
    edge_detect();
}

void EdgedetectDialog::log_deltaChanged(int delta)
{
    this->log_delta = delta * log_delta_step;
    edge_detect();
}

void EdgedetectDialog::log_thrChanged(int thr)
{
    this->log_thr = thr * log_thr_step;
    edge_detect();
}

void EdgedetectDialog::edge_canny(void)
{
    GaussianBlur(gray_image, *pimage, cv::Size(canny_ksize,canny_ksize), 0, 0);
    Canny(*pimage, *pimage, canny_lthr, canny_hthr, 3);

    emit statusChanged();
}

void EdgedetectDialog::canny_ksizeChanged(int ksize)
{
    this->canny_ksize = 1 + ksize * canny_ksize_step;
    edge_canny();
}

void EdgedetectDialog::canny_lthrChanged(int lthr)
{
    this->canny_lthr = lthr * canny_lthr_step;
    edge_canny();
}

void EdgedetectDialog::canny_hthrChanged(int hthr)
{
    this->canny_hthr = hthr * canny_hthr_step;
    edge_canny();
}

