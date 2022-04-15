#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO helper funcitons getPath(index), isDir(index)
// TODO Base class FolderViewModel with function changePath
// TODO Edit control to show path and change it -> tab
// TODO two folder views, focus handling
// TODO show hidden semi transparent/filter hidden
// TODO new model: show drives
// TODO Restrict view by entering letters
