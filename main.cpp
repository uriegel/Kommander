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

// TODO Edit control to show path and change it -> tab
// TODO Suppress size for directories
// TODO Format date time
// TODO Save window dimensions
// TODO Save Model header sizes
// TODO two folder views, focus handling
// TODO show hidden semi transparent/filter hidden
// TODO new model: show drives
// TODO Restrict view by entering letters
