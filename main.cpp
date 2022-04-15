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

// TODO Select first item when path changed
// TODO Select last item when path changed to parent
// TODO Edit control to show path and change it -> tab
// TODO two folder views, focus handling
// TODO show hidden semi transparent/filter hidden
// TODO new model: show drives
// TODO Restrict view by entering letters
