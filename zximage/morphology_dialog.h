/*
 * FileName : morphology_dialog.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 23 Dec 2014 09:39:36 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _MORPHOLOGY_DIALOG_H
#define  _MORPHOLOGY_DIALOG_H

#include <QDialog>
#include <cv.h>

class QPushButton;
class QRadioButton;
class QSlider;
class QLabel;

class MorphologyDialog : public QDialog {
    Q_OBJECT

public:
    MorphologyDialog(cv::Mat& img, QWidget *parent=0);

signals:
    void statusChanged();
    void dialogClosed();

public slots:
    void okClicked();
    void closeClicked();
    void setDilateOpt();
    void setErodeOpt();
    void setRectType();
    void setCrossType();
    void setEllipseType();
    void sizeSliderChanged(int value);

private:
    void morphology();

    QPushButton *okButton;
    QPushButton *closeButton;
    QRadioButton *dilateRB;
    QRadioButton *erodeRB;
    QRadioButton *rectRB;
    QRadioButton *crossRB;
    QRadioButton *ellipseRB;
    QSlider *sizeSlider;
    QLabel *sizeLabel;

    enum {
        DILATE = 1,
        ERODE = 2,
    } opt;

    enum {
        TYPE_RECT = 1,
        TYPE_CROSS = 2,
        TYPE_ELLIPSE = 3,
    } ele_type;

    int size_ele;
    static const int size_step=1;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;
};


#endif  /*_MORPHOLOGY_DIALOG_H*/
