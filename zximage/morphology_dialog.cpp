/*
 * FileName : /home/xiahouzuoxin/opencv_study/20_facedector/morphology_dialog.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 23 Dec 2014 09:44:51 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "morphology_dialog.h" 
#include "imgproc/imgproc.hpp"

MorphologyDialog::MorphologyDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }

    opt = DILATE;
    ele_type = TYPE_RECT;
    size_ele = 1;

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

    /* RadioButton */
    QGroupBox *optGroup = new QGroupBox("Morphology",this);
    dilateRB = new QRadioButton("Dilate");
    erodeRB = new QRadioButton("Erode");
    QVBoxLayout *optLayout = new QVBoxLayout();
    optLayout->addWidget(dilateRB);
    optLayout->addWidget(erodeRB);
    optGroup->setLayout(optLayout);
    optGroup->setVisible(true);
    dilateRB->setChecked(true);

    connect(dilateRB, SIGNAL(clicked()), this, SLOT(setDilateOpt()));
    connect(erodeRB, SIGNAL(clicked()), this, SLOT(setErodeOpt()));

    /* RadioButton */
    QGroupBox *eleGroup = new QGroupBox("Structures",this);
    rectRB = new QRadioButton("Rectangle");
    crossRB = new QRadioButton("Cross");
    ellipseRB = new QRadioButton("Ellipse");
    QVBoxLayout *eleLayout = new QVBoxLayout();
    eleLayout->addWidget(rectRB);
    eleLayout->addWidget(crossRB);
    eleLayout->addWidget(ellipseRB);
    eleGroup->setLayout(eleLayout);
    eleGroup->setVisible(true);
    rectRB->setChecked(true);

    connect(rectRB, SIGNAL(clicked()), this, SLOT(setRectType()));
    connect(crossRB, SIGNAL(clicked()), this, SLOT(setCrossType()));
    connect(ellipseRB, SIGNAL(clicked()), this, SLOT(setEllipseType()));

    QHBoxLayout *midLayout = new QHBoxLayout();
    midLayout->addWidget(optGroup);
    midLayout->addWidget(eleGroup);
    
    /* elementsize Slider */
    sizeSlider = new QSlider(Qt::Horizontal);
    sizeSlider->setRange(0,10);
    sizeSlider->setValue(1);
    sizeLabel = new QLabel(tr("EleSize(2n+1)"));

    connect(sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(sizeSliderChanged(int)));

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(sizeLabel);
    topLayout->addWidget(sizeSlider);
    
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(midLayout);
    mainLayout->addLayout(bntLayout);
    
    setLayout(mainLayout);
    setWindowTitle(tr("Morphology Operation"));
    setFixedHeight(sizeHint().height());
}

void MorphologyDialog::okClicked()
{
    this->close();
    emit dialogClosed();
}

void MorphologyDialog::closeClicked()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit dialogClosed();
}

void MorphologyDialog::morphology()
{
    int type = 0;

    switch (ele_type) {
    case TYPE_RECT:
        type = cv::MORPH_RECT;
        break;
    case TYPE_CROSS:
        type = cv::MORPH_CROSS;
        break;
    case TYPE_ELLIPSE:
        type = cv::MORPH_ELLIPSE;
    default:
        type = cv::MORPH_RECT;
        break;
    }

    cv::Mat ele = getStructuringElement(type, cv::Size(2*size_ele+1,2*size_ele+1), 
            cv::Point(size_ele, size_ele));

    switch (opt) {
    case DILATE:
        dilate(gray_image, *pimage, ele);
        break;
    case ERODE:
        erode(gray_image, *pimage, ele);
    default:
        break;
    }

    emit statusChanged();
}

void MorphologyDialog::setDilateOpt()
{
    opt = DILATE;
    morphology();
}

void MorphologyDialog::setErodeOpt()
{
    opt = ERODE;
    morphology();
}

void MorphologyDialog::setRectType()
{
    ele_type = TYPE_RECT;
    morphology();
}

void MorphologyDialog::setCrossType()
{
    ele_type = TYPE_CROSS;
    morphology();
}

void MorphologyDialog::setEllipseType()
{
    ele_type = TYPE_ELLIPSE;
    morphology();
}

void MorphologyDialog::sizeSliderChanged(int value)
{
    size_ele = value;
    morphology();
}

