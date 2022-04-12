#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Subject"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Größe"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Datum"));

    auto fileModel = new QFileSystemModel(this);
    auto path = QDir::homePath() + "/Dokumente";
    fileModel->setRootPath(path);

    ui->folderView->setModel(model);

    connect(fileModel, &QFileSystemModel::directoryLoaded, [model, fileModel](const QString &directory) {
        auto parentIndex = fileModel->index(directory);
        int numRows = fileModel->rowCount(parentIndex);
        for (auto i = 0; i < numRows; i++) {
            auto indexi = fileModel->index(i, 0, parentIndex);
            auto content = fileModel->data(indexi, Qt::DisplayRole).toString();
            auto eikon = fileModel->fileIcon(indexi);
            auto seize = fileModel->size(indexi);
            auto lm = fileModel->lastModified(indexi);

            auto list = QList<QStandardItem*>();
            list.append(new QStandardItem(eikon, content));
            list.append(new QStandardItem(QString::number(seize)));
            list.append(new QStandardItem(lm.toString()));

            model->appendRow(list);
        }
        delete fileModel;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

