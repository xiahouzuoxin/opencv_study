/*
 * FileName : hough_dialog.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Mon 22 Dec 2014 11:23:45 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _HOUGH_DIALOG_H
#define  _HOUGH_DIALOG_H

#include <QDialog>
#include <cv.h>

class QLabel;
class QSlider;
class QSpinBox;
class QPushButton;
class QGroupBox;
class QHBoxLayout;

class HoughDialog : public QDialog {
    Q_OBJECT
public:
    HoughDialog(cv::Mat& img, QWidget *parent=0);
signals:
    void statusChanged();
    void dialogClosed();
public slots:
    void okClicked();
    void closeClicked();
    void moreClicked();
    void rhoChanged(int value);
    void thetaChanged(int value);
    void thrChanged(int value);
    void ksizeChanged(int value);
    void lthrChanged(int value);
    void hthrChanged(int value);
private:
    void hough(void);

    QLabel *rhoLabel;
    QLabel *thetaLabel;
    QLabel *thrLabel;
    QSlider *rhoSlider;
    QSlider *thetaSlider;
    QSlider *thrSlider;
    QSpinBox *rhoEdit;
    QSpinBox *thetaEdit;
    QSpinBox *thrEdit;
    QPushButton *okButton;
    QPushButton *closeButton;
    
    double rho;
    double theta;
    int thr;
    static const double rho_step = 1;
    static const double theta_step = CV_PI/360;
    static const int thr_step = 1;

    /* Canny arguments */
    QLabel *ksizeLabel;
    QLabel *lthrLabel;
    QLabel *hthrLabel;
    QSlider *ksizeSlider;
    QSlider *lthrSlider;
    QSlider *hthrSlider;
    QSpinBox *ksizeEdit;
    QSpinBox *lthrEdit;
    QSpinBox *hthrEdit;
    QPushButton *moreButton;

    double ksize;
    double lthr;
    int hthr;
    static const int ksize_step = 2;
    static const int lthr_step = 1;
    static const int hthr_step = 1;
    QHBoxLayout *mainLayout;
    QGroupBox *ex_win;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;
};

#endif  /*_HOUGH_DIALOG_H*/

