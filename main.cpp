#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO Tab Key process, no emitting -> focus stys in FolderView
// TODO Extend FilesModels with parent item ..
// TODO Sorting (string (name), integer (size) date time, but always directory sort by name before files
// TODO get exifs in a background thread, then change model
// TODO Sorting by datetime or exiftime
// TODO change path by enter and double click
// TODO Edit control to show path and change it -> tab
// TODO new model: show drives

