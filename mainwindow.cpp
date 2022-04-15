#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QTreeView>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "folderview.h"
#include "filesystemmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileSystemModel::attach(ui->folderView);
    ui->folderView->changePath(QDir::cleanPath(QDir::homePath()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

