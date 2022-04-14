#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QTreeView>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dateitemdelegate.h"
#include "variantitem.h"
#include "folderview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Größe")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("Datum")));

    auto fileModel = new QFileSystemModel(this);
    auto path = QDir::homePath() + "/Dokumente";
    fileModel->setRootPath(path);

    ui->folderView->setModel(model);
    ui->folderView->setItemDelegateForColumn(0, new ItemDelegate(ui->folderView));
    ui->folderView->setItemDelegateForColumn(1, new ItemDelegate(ui->folderView));
    ui->folderView->setItemDelegateForColumn(2, new DateItemDelegate(ui->folderView));

    connect(fileModel, &QFileSystemModel::directoryLoaded, [model, fileModel, this](const QString &directory) {
        auto parentIndex = fileModel->index(directory);
        int numRows = fileModel->rowCount(parentIndex);

        auto list = QList<QStandardItem*>();
        list.append(new QStandardItem(QIcon("/home/uwe/Projekte/Qt/Kommander/parent.svg"), ".."));
        list.append(new VariantItem(QVariant(0)));
        list.append(new VariantItem(QVariant()));
        ui->folderView->setColumnWidth(0, 300);
        ui->folderView->setColumnWidth(1, 140);

        model->appendRow(list);


        for (auto i = 0; i < numRows; i++) {
            auto indexi = fileModel->index(i, 0, parentIndex);
            auto content = fileModel->data(indexi, Qt::DisplayRole).toString();
            auto eikon = fileModel->fileIcon(indexi);
            auto seize = fileModel->size(indexi);
            auto lm = fileModel->lastModified(indexi);

            auto list = QList<QStandardItem*>();
            list.append(new QStandardItem(eikon, content));
            list.append(new VariantItem(QVariant(seize)));
            list.append(new VariantItem(QVariant(lm)));

            model->appendRow(list);
        }
        delete fileModel;
    });

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
    auto path = QDir::homePath() + "/Dokumente";
    model->setRootPath(path);

    auto oldModel = ui->folderView->model();
    ui->folderView->setModel(model);
    delete oldModel;
    ui->folderView->setRootIndex(model->index(path));
}
