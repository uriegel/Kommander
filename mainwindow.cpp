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

    ui->videoWidget->hide();

    FileSystemModel::attach(ui->leftFolderView);
    ui->leftFolderView->changePath(QDir::cleanPath(QDir::homePath()));

    FileSystemModel::attach(ui->rightFolderView);
    ui->rightFolderView->changePath(QDir::cleanPath(QDir::homePath()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

