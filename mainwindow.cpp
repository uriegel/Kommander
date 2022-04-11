#include <QFileSystemModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto model = new QFileSystemModel(this);
    auto path = QDir::homePath() + "/Dokumente";
    model->setRootPath(path);
    ui->folderView->setModel(model);
    ui->folderView->setRootIndex(model->index(path));
}

MainWindow::~MainWindow()
{
    delete ui;
}

