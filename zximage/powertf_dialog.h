/*
 * FileName : powertf_dialog.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 18 Dec 2014 06:54:32 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _POWERTF_DIALOG_H
#define  _POWERTF_DIALOG_H

#include <QDialog>
#include <cv.h>
#include <imgproc/imgproc.hpp>

class QLabel;
//class QLineEdit;
class QPushButton;
class QSlider;
class QSpinBox;

class QCloseEvent;

class PowertfDialog : public QDialog {
    Q_OBJECT

public:
    PowertfDialog(cv::Mat& img, QWidget *parent=0);

private slots:
    void okClicked();
    void closePowertf(void);
    void rChanged(int r);
    void bChanged(int b);
    void cChanged(int c);

signals:
    void statusChanged();
    void powertfClosed();

private:
    void powertf(void);

    cv::Mat image;
    cv::Mat *pimage;
    int r;
    int b;
    int c;

    QPushButton *okButton;
    QPushButton *closeButton;
    QLabel *rLabel;
    QLabel *cLabel;
    QLabel *bLabel;
    QSlider *rSlider;
    QSlider *cSlider;
    QSlider *bSlider;
    QSpinBox *rSBx;
    QSpinBox *cSBx;
    QSpinBox *bSBx;
};

#endif  /*_POWERTF_DIALOG_H*/

