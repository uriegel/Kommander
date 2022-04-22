#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/kirk.png"));
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO menu show/hide viewer F3
// TODO Pdfview https://doc.qt.io/qt-5/qtpdf-pdfviewer-example.html at first create sample
// TODO Media player at first create sample
// TODO Save window dimensions
// TODO show hidden semi transparent/filter hidden
// TODO new model: show drives
// TODO Save Model header sizes
// TODO Restrict view by entering letters
