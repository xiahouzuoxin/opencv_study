/*
 * FileName : main.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 23 Nov 2014 04:29:47 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <QApplication>
#include <QTextCodec>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}

