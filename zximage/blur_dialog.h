/*
 * FileName : blur_dialog.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Tue 23 Dec 2014 04:09:15 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _BLUR_DIALOG_H
#define  _BLUR_DIALOG_H

#include <QDialog>
#include <cv.h>

class QPushButton;
class QRadioButton;
class QSlider;
class QSpinBox;
class QLabel;

class BlurDialog : public QDialog {
    Q_OBJECT
public:
    BlurDialog(cv::Mat& img, QWidget *parent=0);
signals:
    void statusChanged();
    void dialogClosed();
public slots:
    void okClicked();
    void closeClicked();
    void setHomogeneousOpt();
    void setGuassianOpt();
    void setMedianOpt();
    void setBilateralOpt();
    void setGuidedOpt();
    void ksizeChanged(int value);

private:
    void blur_opt(void);

    QRadioButton *homogeneousBtn;
    QRadioButton *guassianBtn;
    QRadioButton *medianBtn;
    QRadioButton *bilateralBtn;
    QRadioButton *guidedBtn;
    QSlider *ksizeSlider;
    QSpinBox *ksizeSBox;
    QLabel *ksizeLabel;
    QPushButton *okButton;
    QPushButton *closeButton;

    enum {
        OPT_HOMOGENEOUS = 1,
        OPT_GUASSIAN = 2,
        OPT_MEDIAN = 3,
        OPT_BILATERAL = 4,
        OPT_GUIDED = 5,
    } opt;

    int ksize;
    static const int ksize_step = 2;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;
};


#endif  /*_BLUR_DIALOG_H*/
