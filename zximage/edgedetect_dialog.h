/*
 * FileName : edge_detect.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Fri 19 Dec 2014 05:27:21 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _EDGE_DETECT_H
#define  _EDGE_DETECT_H

#include <QDialog>
#include <cv.h>

class QTabWidget;
class QPushButton;
class QLabel;
class QSlider;
class QSpinBox;

class LOGDialog : public QDialog {
    Q_OBJECT

public:
    LOGDialog(int ksize, double scale, double delta, QWidget *parent=0);
private:
    QSlider *log_ksizeSlider;
    QSlider *log_scaleSlider;
    QSlider *log_deltaSlider;
    QSlider *thrSlider;
    QLabel *log_ksizeLabel;
    QLabel *log_scaleLabel;
    QLabel *log_deltaLabel;
    QLabel *thrLabel;
    QSpinBox *log_ksizeSBx;
    QSpinBox *log_scaleSBx;
    QSpinBox *log_deltaSBx;
    QSpinBox *thrSBx;
};

class CannyDialog : public QDialog {
    Q_OBJECT
public:
    CannyDialog(int ksize, int lthr, int hthr, int max_lthr, int max_hthr, QWidget *parent=0);
private:
    QSlider *ksizeSlider;
    QSlider *lthrSlider;
    QSlider *hthrSlider;
    QLabel *ksizeLabel;
    QLabel *lthrLabel;
    QLabel *hthrLabel;
    QSpinBox *ksizeSBx;
    QSpinBox *lthrSBx;
    QSpinBox *hthrSBx;
};

class EdgedetectDialog : public QDialog {
    Q_OBJECT

public:
    EdgedetectDialog(cv::Mat& img, QWidget *parent=0);

signals:
    void statusChanged();
    void dialogClosed();

public slots:
    void okClicked();
    void closeEdgedetect();
    void log_ksizeChanged(int ksize);
    void log_scaleChanged(int scale);
    void log_deltaChanged(int delta);
    void log_thrChanged(int thr);
    void canny_ksizeChanged(int ksize);
    void canny_lthrChanged(int lthr);
    void canny_hthrChanged(int hthr);

private:
    void edge_detect(void);
    void edge_canny(void);

    QTabWidget *tabWidget;
    QPushButton *okButton;
    QPushButton *closeButton;

    int log_ksize;
    double log_scale;
    double log_delta;
    int log_thr;
    static const int log_ksize_step = 2;
    static const double log_scale_step = 0.5;
    static const double log_delta_step = 0.5;
    static const int log_thr_step = 1;

    int canny_ksize;
    int canny_lthr;
    int canny_hthr;
    static const int canny_ksize_step = 2;
    static const int canny_lthr_step = 1;
    static const int canny_hthr_step = 1;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;
};

#endif  /*_EDGE_DETECT_H*/

