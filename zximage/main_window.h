/*
 * FileName : main_window.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 18 Dec 2014 11:14:16 AM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _MAIN_WINDOW_H
#define  _MAIN_WINDOW_H

#include <QMainWindow>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class QAction;
class QLabel;
class PowertfDialog;
class EdgedetectDialog; 
class HoughDialog;
class MorphologyDialog;
class BlurDialog;
class FacedetectDialog;
class HisteqDialog;

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    void open();
    bool save();
    void exit();

    void facedetect();  // detection
    void powertf();
    void edgedetect();
    void houghcheck();
    void morphology();
    void bluropt();
    void histeqopt();
    void forward();
    void backward();
    void camera_start(void);
    void camera_stop(void);

    void clean_facedetect();
    void clean_powertf();
    void clean_edgedetect();
    void clean_houghcheck();
    void clean_morphology();
    void clean_bluropt();
    void clean_histeqopt();

    void disp_image();
    void about();
    void doc();
    
private:
    void createActions();
    void createMenus();
    void createToolBar();
    void loadFile(const QString &filename);
    bool loadCheck();
    QImage Mat2QImage(Mat& image);
    void show_image();
    int savePrevStatus(void);
    int loadPrevStatus(void);
    int saveCurStatus(void);
    int loadCurStatus(void);

    bool loadPrevCheck;
    bool loadCurCheck;
    bool cam_on;
    bool cam_save;

    FacedetectDialog *facedetectDlg;
    PowertfDialog *powertfDlg;
    EdgedetectDialog *edgedetectDlg;
    HoughDialog *houghDlg;
    MorphologyDialog *morphDlg;
    BlurDialog *blurDlg;
    HisteqDialog *histeqDlg;

    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;
    QToolBar *editToolBar;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *facedetectAction;
    QAction *powertfAction;
    QAction *edgedetectAction;
    QAction *houghAction;
    QAction *morphAction;
    QAction *blurAction;
    QAction *histeqAction;
    QAction *cameraAction;
    QAction *aboutAction;
    QAction *docAction;

    QAction *backwardAction;
    QAction *forwardAction;
    QAction *camstartAction;
    QAction *camstopAction;

    QTimer *cam_timer;

    Mat img;
    Mat cur_img;
    CvCapture *capture;

    QLabel *img_label;
};

#endif  /*_MAIN_WINDOW_H*/

