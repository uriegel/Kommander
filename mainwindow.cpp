#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QTreeView>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dateitemdelegate.h"
#include "variantitem.h"
#include "folderview.h"
#include "filesystemmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);





    auto model = FileSystemModel::create(this);
    ui->folderView->setModel(model);
    ui->folderView->setItemDelegateForColumn(0, new ItemDelegate(ui->folderView));
    ui->folderView->setItemDelegateForColumn(1, new ItemDelegate(ui->folderView));
    ui->folderView->setItemDelegateForColumn(2, new DateItemDelegate(ui->folderView));
    ui->folderView->header()->setSortIndicator(0, Qt::AscendingOrder);
    ui->folderView->setColumnWidth(0, 300);
    ui->folderView->setColumnWidth(1, 140);




    connect(ui->changeModelButton, SIGNAL(clicked()), this, SLOT(on_changeModel()));
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
    model->setRootPath(path);
    model->setNameFilterDisables(true);
    auto oldModel = ui->folderView->model();
    ui->folderView->setModel(model);
    model->setFilter(QDir::Files|QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);
    delete oldModel;
    ui->folderView->setRootIndex(model->index(path));
}
