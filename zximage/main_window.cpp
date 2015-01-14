/*
 * FileName : main_window.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Thu 18 Dec 2014 02:36:23 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <fstream>
#include <QtGui>
#include <QTextBrowser>

#include "main_window.h" 
#include "powertf_dialog.h"
#include "edgedetect_dialog.h"
#include "hough_dialog.h"
#include "morphology_dialog.h"
#include "blur_dialog.h"
#include "facedetect_dialog.h"
#include "histeq_dialog.h"

#include "objdetect/objdetect.hpp"
#include "imgproc/imgproc.hpp"

const char *bakfile_name = "bakfile.xml";
const char *curfile_name = "curfile.xml";

MainWindow::MainWindow()
{
    img_label = new QLabel("",0);
    setCentralWidget(img_label);

    createActions();
    createMenus();
    createToolBar();

    powertfDlg = 0;
    edgedetectDlg = 0;
    houghDlg = 0;
    morphDlg = 0;
    blurDlg = 0;
    histeqDlg = 0;
    facedetectDlg = 0;

    cam_on = false;
    cam_save = false;
    capture = 0;

    setWindowIcon(QIcon(":/images/title.png"));

    img = imread("images/Home.png", 1);
    img.copyTo(cur_img);
    show_image();
}

MainWindow::~MainWindow()
{
    cvReleaseCapture(&capture);
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(0, "Open File", "", "*.jpg *.png *.bmp", 0);
    if (!filename.isEmpty()) {
        loadFile(filename);
        show_image();
    }
}

void MainWindow::exit()
{
    QFile::remove(bakfile_name);
    QFile::remove(curfile_name);
    this->close();
}

bool MainWindow::save()
{
    if (!loadCheck()) {
        return false;
    }

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Image"),".", "*.*"); //tr("*.jpg"));

    if (fileName.isEmpty()) {
        return false;
    } else {
        string fn = fileName.toStdString();
        if (!fileName.contains(".")) {
           fn += ".jpg"; 
        }
        imwrite(fn,cur_img);
        return true;
    }
}


void MainWindow::facedetect()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!facedetectDlg) {
        facedetectDlg = new FacedetectDialog(cur_img,this);

        connect(facedetectDlg, SIGNAL(statusChanged()), this, SLOT(disp_image())); 
        connect(facedetectDlg, SIGNAL(dialogClosed()), this, SLOT(clean_facedetect()));
    }
    facedetectDlg->show();
    facedetectDlg->activateWindow();
}

void MainWindow::powertf()
{
    // img.copyTo(cur_img);
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!powertfDlg) {
        powertfDlg = new PowertfDialog(cur_img,this);

        connect(powertfDlg, SIGNAL(statusChanged()), this, SLOT(disp_image())); 
        connect(powertfDlg, SIGNAL(powertfClosed()), this, SLOT(clean_powertf()));
    }
    powertfDlg->show();
    powertfDlg->activateWindow();
}

void MainWindow::edgedetect()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();

    if (!edgedetectDlg) {
        edgedetectDlg = new EdgedetectDialog(cur_img,this);
        
        connect(edgedetectDlg,SIGNAL(statusChanged()), this, SLOT(disp_image())); 
        connect(edgedetectDlg,SIGNAL(dialogClosed()), this, SLOT(clean_edgedetect()));
    }
    edgedetectDlg->show();
    edgedetectDlg->activateWindow();
}

void MainWindow::houghcheck()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!houghDlg) {
        houghDlg = new HoughDialog(cur_img, this);

        connect(houghDlg, SIGNAL(statusChanged()), this, SLOT(disp_image()));
        connect(houghDlg, SIGNAL(dialogClosed()), this, SLOT(clean_houghcheck()));
    }
    houghDlg->show();
    houghDlg->activateWindow();
}

void MainWindow::morphology()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!morphDlg) {
        morphDlg = new MorphologyDialog(cur_img, this);

        connect(morphDlg, SIGNAL(statusChanged()), this, SLOT(disp_image()));
        connect(morphDlg, SIGNAL(dialogClosed()), this, SLOT(clean_morphology()));
    }
    morphDlg->show();
    morphDlg->activateWindow();
}

void MainWindow::bluropt()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!blurDlg) {
        blurDlg = new BlurDialog(cur_img, this);

        connect(blurDlg, SIGNAL(statusChanged()), this, SLOT(disp_image()));
        connect(blurDlg, SIGNAL(dialogClosed()), this, SLOT(clean_bluropt()));
    }
    blurDlg->show();
    blurDlg->activateWindow();
}

void MainWindow::histeqopt()
{
    if (!loadCheck()) {
        return;
    }

    savePrevStatus();
    
    if (!histeqDlg) {
        histeqDlg= new HisteqDialog(cur_img, this);

        connect(histeqDlg, SIGNAL(statusChanged()), this, SLOT(disp_image()));
        connect(histeqDlg, SIGNAL(dialogClosed()), this, SLOT(clean_histeqopt()));
    }
    histeqDlg->show();
    histeqDlg->activateWindow();

}

void MainWindow::clean_facedetect()
{
    delete facedetectDlg;
    facedetectDlg = 0;
}

void MainWindow::clean_powertf()
{
    delete powertfDlg;
    powertfDlg = 0;
}

void MainWindow::clean_edgedetect()
{
    delete edgedetectDlg;
    edgedetectDlg = 0;
}

void MainWindow::clean_houghcheck()
{
    delete houghDlg;
    houghDlg = 0;
}

void MainWindow::clean_morphology()
{
    delete morphDlg;
    morphDlg = 0;
}

void MainWindow::clean_bluropt()
{
    delete blurDlg;
    blurDlg = 0;
}

void MainWindow::clean_histeqopt()
{
    delete histeqDlg;
    histeqDlg = 0;
}

void MainWindow::about()
{
    QMessageBox::about(this,tr("About zxface"),
        tr("<h2>zximage v1.0</h2>"
           "<p>Copyright &copy; 2014 Software Inc. autor:xiahouzuoxin"
           "<p>zximage is a small application that include some basic functions for image processing."));
}

void MainWindow::doc()
{
    std::ifstream in;
    std::string s,line;

    in.open("doc/help",ios::in);
    while (getline(in,line)) {
        s += line + "\n";
    }
    in.close();
    QString qstr = QString::fromStdString(s);
    //img_label->setText(qstr);
    
    QTextBrowser *doc = new QTextBrowser();
    doc->append(qstr); 
    doc->show();
    doc->setDocumentTitle(tr("Help"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(facedetectAction);
    toolMenu->addAction(powertfAction);
    toolMenu->addAction(edgedetectAction);
    toolMenu->addAction(houghAction);
    toolMenu->addAction(morphAction);
    toolMenu->addAction(blurAction);
    toolMenu->addAction(histeqAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(docAction);
}

void MainWindow::createToolBar()
{
    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(backwardAction);
    editToolBar->addAction(forwardAction);
    editToolBar->addAction(camstartAction);
    editToolBar->addAction(camstopAction);
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&open..."),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));
    saveAction = new QAction(tr("&save..."),this);
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));
    exitAction = new QAction(tr("&exit"), this);
    connect(exitAction, SIGNAL(triggered()),this,SLOT(exit()));

    facedetectAction = new QAction(tr("&Face Detect"),this);
    connect(facedetectAction, SIGNAL(triggered()),this,SLOT(facedetect()));
    powertfAction = new QAction(tr("&Power Transform"),this);
    connect(powertfAction, SIGNAL(triggered()),this,SLOT(powertf()));
    edgedetectAction = new QAction(tr("&Edge Detect"),this);
    connect(edgedetectAction, SIGNAL(triggered()),this,SLOT(edgedetect()));
    houghAction = new QAction(tr("&Hough Check"),this);
    connect(houghAction, SIGNAL(triggered()), this, SLOT(houghcheck()));
    morphAction = new QAction(tr("&Morphology"),this);
    connect(morphAction, SIGNAL(triggered()), this, SLOT(morphology()));
    blurAction = new QAction(tr("&Blur"),this);
    connect(blurAction, SIGNAL(triggered()), this, SLOT(bluropt()));
    histeqAction = new QAction(tr("&Histeq"),this);
    connect(histeqAction, SIGNAL(triggered()), this, SLOT(histeqopt()));

    aboutAction = new QAction(tr("&about"),this);
    connect(aboutAction, SIGNAL(triggered()),this,SLOT(about()));
    docAction = new QAction(tr("&doc"),this);
    connect(docAction, SIGNAL(triggered()),this,SLOT(doc()));

    backwardAction = new QAction(tr("&backward"),this);
    backwardAction->setIcon(QIcon(":/images/backward.png"));
    connect(backwardAction,SIGNAL(triggered()), this, SLOT(backward()));
    forwardAction = new QAction(tr("&forward"),this);
    forwardAction->setIcon(QIcon(":/images/forward.png"));
    connect(forwardAction,SIGNAL(triggered()), this, SLOT(forward()));
    camstartAction = new QAction(tr("&CAM_Start"), this);
    camstartAction->setIcon(QIcon(":/images/Start.png"));
    camstartAction->setEnabled(true);
    connect(camstartAction,SIGNAL(triggered()),this,SLOT(camera_start()));
    camstopAction = new QAction(tr("&CAM_Stop"), this);
    camstopAction->setIcon(QIcon(":/images/Stop.png"));
    camstopAction->setEnabled(false);
    connect(camstopAction,SIGNAL(triggered()),this,SLOT(camera_stop()));
}

void MainWindow::loadFile(const QString &filename)
{
    img = imread(filename.toAscii().data(), 1);
    img.copyTo(cur_img);
}

QImage MainWindow::Mat2QImage(Mat& image)
{
    QImage img;

    if (image.channels()==3) {
        cvtColor(image, image, CV_BGR2RGB);
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_RGB888);
    } else {  // gray images
        img = QImage(image.cols, image.rows, QImage::Format_RGB888);
        uchar *p = image.data;
        uchar v;
        for (int i=0; i<image.rows; i++) {
            for (int j=0; j<image.cols; j++) {
                v = p[i*image.cols+j];
                img.setPixel(j,i,qRgb(v,v,v));  // with flip
            }
        }
    }

    return img;
}

void MainWindow::show_image()
{
    Mat tmp_img;

    cur_img.copyTo(tmp_img);
    QImage qimg = Mat2QImage(tmp_img);
    img_label->setPixmap(QPixmap::fromImage(qimg));

}

void MainWindow::disp_image()
{
    Mat tmp_img;

    cur_img.copyTo(tmp_img);
    QImage qimg = Mat2QImage(tmp_img);
    img_label->setPixmap(QPixmap::fromImage(qimg));
}


bool MainWindow::loadCheck()
{
    if (!cur_img.data || !img.data) {
        QMessageBox::warning(this, tr("zxdetect"),tr("Please open a image first"), 
                QMessageBox::Ok);
        return false;
    } else {
        return true;
    }
}

int MainWindow::savePrevStatus()
{
    FileStorage fs(bakfile_name, FileStorage::WRITE);

    fs<<"premat"<<cur_img; 
    fs.release();

    loadPrevCheck = true;

    return 1;
}

int MainWindow::saveCurStatus()
{
    FileStorage fs(curfile_name, FileStorage::WRITE);

    fs<<"curmat"<<cur_img; 
    fs.release();

    return 1;
}

int MainWindow::loadPrevStatus()
{
    if (loadPrevCheck) {
        FileStorage fs(bakfile_name, FileStorage::READ);

        if (fs.isOpened()) {
            loadPrevCheck = false;
            saveCurStatus();
            fs["premat"]>>cur_img;
            show_image();
            return 1;
        } else {
            return 0; 
        }
    } else {
        return 0;
    }
}

int MainWindow::loadCurStatus()
{
    FileStorage fs(curfile_name, FileStorage::READ);

    if (fs.isOpened()) {
        loadPrevCheck = true;
        fs["curmat"]>>cur_img;
        show_image();
        return 1;
    } else {
        return 0; 
    }
}

void MainWindow::forward()
{
    if (!loadCurStatus()) {
        QMessageBox::warning(this, tr("zxdetect"),tr("No xml bak file is avilable"), QMessageBox::Ok);
    }
}

void MainWindow::backward()
{
    if (!loadPrevStatus()) {
        QMessageBox::warning(this, tr("zxdetect"),tr("No xml bak file is avilable"), QMessageBox::Ok);
    }
}

void MainWindow::camera_start()
{
    Mat frame;

    if (!capture) {
        capture = cvCaptureFromCAM(-1);
    }
    if (!capture) {
        QMessageBox::warning(this, tr("zxdetect"),tr("No Camera is aviable."), QMessageBox::Ok);
        return;
    }
    VideoWriter wr_vedio("TestVedio.avi",CV_FOURCC('D','E','V','I'),25.0,Size(640,480),true);

    camstartAction->setEnabled(false);
    camstopAction->setEnabled(true);
    //namedWindow("CAM",WINDOW_AUTOSIZE);
    QMessageBox::StandardButton bt = QMessageBox::information(this, tr("CAM"), tr("Save Camera Frame?"), 
            QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
    if (bt == QMessageBox::Yes) {
        if (wr_vedio.isOpened()) {
            cam_save = true;
        } else {
            cout<<"Warning: Vedio Writer is closed, write vedio failed."<<endl;
            cam_save = false;
        }
    } else {
        cam_save = false;
    }

    if (cam_on == true) {
        QMessageBox::warning(this, tr("zxdetect"),tr("Camera is working."), QMessageBox::Ok);
        return;
    }
    if (capture) {
        cam_on = true;
        while (cam_on) {
            frame = cvQueryFrame(capture);
            if (!frame.empty()) {
                //imshow("CAM", frame);
                cur_img = frame;
                show_image();
                if (cam_save) {
                    wr_vedio.write(frame);
                }
            } else {
                QMessageBox::warning(this, tr("zxdetect"),tr("No frame"), QMessageBox::Ok);
                break;
            }
            
            waitKey(10);
            //if ((char)c=='c') {
            //    break;
            //}
        }
        cur_img.copyTo(img);
    }
}

void MainWindow::camera_stop()
{
    camstartAction->setEnabled(true);
    camstopAction->setEnabled(false);
    cam_on = false; 
    if (cam_save) {
        cam_save = false;
    }
}

