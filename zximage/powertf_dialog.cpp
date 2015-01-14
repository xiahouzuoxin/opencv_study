/*
 * FileName : powertf_dialog.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 18 Dec 2014 07:05:42 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "powertf_dialog.h" 
#include <math.h>

PowertfDialog::PowertfDialog(cv::Mat& img, QWidget *parent)
    : QDialog(parent)
{
    r = 1;
    c = 1;
    b = 0;
    img.copyTo(image);
    pimage = &img;

    rSlider = new QSlider(Qt::Horizontal);
    rSlider->setRange(0,10);
    rSlider->setValue(r);
    cSlider = new QSlider(Qt::Horizontal);
    cSlider->setRange(0,10);
    cSlider->setValue(c);
    bSlider = new QSlider(Qt::Horizontal);
    bSlider->setRange(0,10);
    bSlider->setValue(b);

    rSBx = new QSpinBox();
    rSBx->setRange(0,10);
    rSBx->setValue(r);
    cSBx = new QSpinBox();
    cSBx->setRange(0,10);
    cSBx->setValue(c);
    bSBx = new QSpinBox();
    bSBx->setRange(0,10);
    bSBx->setValue(b);

    connect(rSlider,SIGNAL(valueChanged(int)),this,SLOT(rChanged(int)));
    connect(cSlider,SIGNAL(valueChanged(int)),this,SLOT(cChanged(int)));
    connect(bSlider,SIGNAL(valueChanged(int)),this,SLOT(bChanged(int)));
    connect(rSlider,SIGNAL(valueChanged(int)),rSBx,SLOT(setValue(int)));
    connect(cSlider,SIGNAL(valueChanged(int)),cSBx,SLOT(setValue(int)));
    connect(bSlider,SIGNAL(valueChanged(int)),bSBx,SLOT(setValue(int)));

    connect(rSBx,SIGNAL(valueChanged(int)),this,SLOT(rChanged(int)));
    connect(cSBx,SIGNAL(valueChanged(int)),this,SLOT(cChanged(int)));
    connect(bSBx,SIGNAL(valueChanged(int)),this,SLOT(bChanged(int)));
    connect(rSBx,SIGNAL(valueChanged(int)),rSlider,SLOT(setValue(int)));
    connect(cSBx,SIGNAL(valueChanged(int)),cSlider,SLOT(setValue(int)));
    connect(bSBx,SIGNAL(valueChanged(int)),bSlider,SLOT(setValue(int)));

    rLabel = new QLabel(tr("r"));
    cLabel = new QLabel(tr("c"));
    bLabel = new QLabel(tr("b"));

    okButton = new QPushButton(tr("&OK"));
    okButton->setDefault(true);
    okButton->setEnabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));

    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closePowertf()));

    QHBoxLayout *rLayout = new QHBoxLayout;
    rLayout->addWidget(rLabel);
    rLayout->addWidget(rSlider);
    rLayout->addWidget(rSBx);
    QHBoxLayout *cLayout = new QHBoxLayout;
    cLayout->addWidget(cLabel);
    cLayout->addWidget(cSlider);
    cLayout->addWidget(cSBx);
    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addWidget(bLabel);
    bLayout->addWidget(bSlider);
    bLayout->addWidget(bSBx);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(rLayout);
    leftLayout->addLayout(cLayout);
    leftLayout->addLayout(bLayout);
    
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(okButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Power Tranform"));
    setFixedHeight(sizeHint().height());
}

void PowertfDialog::okClicked()
{
    //QMessageBox::about(this,tr("PowerDialog"),tr("Hello"));
    this->close();
    emit powertfClosed();
}

void PowertfDialog::rChanged(int r)
{
    this->r = r;
    powertf();
}

void PowertfDialog::bChanged(int b)
{
    this->b = b;
    powertf();
}

void PowertfDialog::cChanged(int c)
{
    this->c = c;
    powertf();
}

void PowertfDialog::powertf(void)
{
    uchar *p = pimage->data;
    long nrows = pimage->rows;
    long ncols = pimage->cols * pimage->channels();

    for (long i=0; i<nrows * ncols; i++) {
        *(p+i) = static_cast<uchar>( (255 * c * pow((double)(image.data[i])/255,r) +b ) );
    }

    emit statusChanged();
}

void PowertfDialog::closePowertf()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit powertfClosed();
}

