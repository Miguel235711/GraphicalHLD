#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>

#include "UI/dummywidget.h"

class MainWindow : QMainWindow
{
public:
    MainWindow(const QString & windowName);
protected:
private:
    QGridLayout * gridLayout = new QGridLayout();
};

#endif // MAINWINDOW_H
