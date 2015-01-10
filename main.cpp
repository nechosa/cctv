//#include "mainwindow.h"
#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("VLC-Qt Demo Player");

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    QApplication a(argc, argv);

    Window wgt;
     wgt.show();

    return a.exec();
}
