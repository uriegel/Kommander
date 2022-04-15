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
    connect(ui->changeModelButton, SIGNAL(clicked()), this, SLOT(on_changeModel()));

    auto path = QDir::cleanPath(QDir::homePath());
    ui->folderView->changePath(path);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changeModel()
{
    auto model = new QFileSystemModel(this);
    //auto path = "/media/uwe/Home/Bilder/Fotos/2017/Abu Dabbab/";
    auto path = QDir::homePath();
    //model->setRootPath(path);
    //model->setNameFilterDisables(true);
    auto oldModel = ui->folderView->model();
    ui->folderView->setModel(model);
    model->setFilter(QDir::Files|QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot|QDir::Drives);
    delete oldModel;
    //ui->folderView->setRootIndex(model->index(path));
}
