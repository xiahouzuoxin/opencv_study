/*
 * FileName : facedetect.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 25 Dec 2014 04:55:38 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QtGui>
#include "facedetect_dialog.h" 
#include "imgproc/imgproc.hpp"
#include "objdetect/objdetect.hpp"

using namespace cv;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

FacedetectDialog::FacedetectDialog(cv::Mat& img, QWidget *parent)
    :QDialog(parent)
{
    img.copyTo(image);
    pimage = &img;
    if (pimage->channels()==3) {
        cvtColor(*pimage, gray_image, CV_RGB2GRAY);
    } else {
        pimage->copyTo(gray_image);
    }

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

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(bntLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Face Detect"));
    setFixedHeight(sizeHint().height());
}

void FacedetectDialog::facedetect()
{
    vector<Rect> faces;
    Mat gray_img;

    gray_image.copyTo(gray_img);

    equalizeHist(gray_img, gray_img);

    if (!face_cascade.load(face_cascade_name)) {
        QMessageBox::warning(this, tr("zxdetect"),tr("-- Error loading face detect xml"), 
                QMessageBox::Yes | QMessageBox::No);
    }
    if (!eyes_cascade.load(eyes_cascade_name)) {
        QMessageBox::warning(this, tr("zxdetect"),tr("-- Error loading eyes detect xml"), 
                QMessageBox::Yes | QMessageBox::No);
    }

    // Detect face
    face_cascade.detectMultiScale(gray_img, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30,30));

    image.copyTo(*pimage);
    for (unsigned int i=0; i<faces.size(); i++) {
        Point center(faces[i].x+faces[i].width*0.5,faces[i].y+faces[i].height*0.5);
        ellipse(*pimage, center, Size(faces[i].width*0.5,faces[i].height*0.5), 
                0,0,360,Scalar(255,0,255),2);

        // Detect eyes
        Mat faceROI = gray_img(faces[i]);
        vector<Rect> eyes;

        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1,2,0|CV_HAAR_SCALE_IMAGE, Size(30,30));
        for (unsigned int j=0; j<eyes.size(); j++) {
            Point center(faces[i].x+eyes[j].x+eyes[j].width*0.5, faces[i].y+eyes[j].y+eyes[j].height*0.5);
            int radius = cvRound((eyes[j].width+eyes[j].height)*0.25);
            circle(*pimage, center, radius, Scalar(255,0,0));
        }
    } 

    emit statusChanged();
}

void FacedetectDialog::okClicked()
{
    facedetect();
    this->close();
    emit dialogClosed();
}

void FacedetectDialog::closeClicked()
{
    image.copyTo(*pimage);
    emit statusChanged();

    this->close();
    emit dialogClosed();
}

