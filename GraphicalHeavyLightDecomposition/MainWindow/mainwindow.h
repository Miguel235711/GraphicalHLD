#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QStyle>

#include "UI/dummywidget.h"
#include "Reader/treereader.h"
#include "UI/canvas.h"
#include "UI/controls.h"

class MainWindow : QMainWindow
{
public:
    MainWindow(const QString & windowName,int titleBarHeight);
    void init();
protected:
private:
    const QString & windowName;
    int titleBarHeight;
    TreeReader treeReader;
    QGraphicsView * treeView;
    void resizeEvent(QResizeEvent* event)
    {
        init();
        qInfo() << "window resized";
    }

    QGridLayout * gridLayout = new QGridLayout();
};

#endif // MAINWINDOW_H
