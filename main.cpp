#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/kirk.png"));
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO Save window dimensions
// TODO Viewer
// TODO show hidden semi transparent/filter hidden
// TODO new model: show drives
// TODO Save Model header sizes
// TODO Restrict view by entering letters
