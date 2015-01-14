/*
 * FileName : facedetect.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 25 Dec 2014 04:54:52 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _FACEDETECT_H
#define  _FACEDETECT_H

#include <QDialog>
#include <cv.h>

class QPushButton;

class FacedetectDialog : public QDialog {
    Q_OBJECT
public:
    FacedetectDialog(cv::Mat& img, QWidget *parent=0);
public slots:
    void okClicked();
    void closeClicked();
signals:
    void statusChanged();
    void dialogClosed();
    
private:
    void facedetect();

    QPushButton *okButton;
    QPushButton *closeButton;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;
};

#endif  /*_FACEDETECT_H*/

