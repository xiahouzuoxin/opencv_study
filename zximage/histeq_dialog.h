/*
 * FileName : /home/xiahouzuoxin/opencv_study/zximage/histeq_dialog.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Mon 29 Dec 2014 04:01:47 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _HISTEQ_DIALOG_H
#define  _HISTEQ_DIALOG_H

#include <QDialog>
#include <cv.h>

class QPushButton;
class QLabel;

class HisteqDialog : public QDialog {
    Q_OBJECT

public:
    HisteqDialog(cv::Mat& img, QWidget* parent=0);
public slots:
    void okClicked();
    void closeClicked();
    void histeq(void);
signals:
    void statusChanged();
    void dialogClosed();

private:
    void hist_graph_gray(cv::Mat& img, cv::Mat& hist);
    void hist_graph_color(cv::Mat& img, cv::Mat *rgb_hists);
    void hist_graph();
    void histeq_gray(cv::Mat& img);
    void histeq_color(cv::Mat& img);

    QPushButton *okButton;
    QPushButton *execButton;
    QPushButton *closeButton;

    cv::Mat image;
    cv::Mat gray_image;
    cv::Mat *pimage;

};

#endif  /*_HISTEQ_DIALOG_H*/

