#include <QApplication>


#include "MainWindow/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow * mainWindow = new MainWindow("Heavy Light Decomposition",QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight));
    return app.exec();
}
