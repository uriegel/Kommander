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

    folderView = new FolderView;
    ui->centralwidget->layout()->addWidget(folderView);
    folderView->setModel(model);
    folderView->setItemDelegateForColumn(0, new ItemDelegate(folderView));
    folderView->setItemDelegateForColumn(1, new ItemDelegate(folderView));
    folderView->setItemDelegateForColumn(2, new DateItemDelegate(folderView));

    connect(fileModel, &QFileSystemModel::directoryLoaded, [model, fileModel, this](const QString &directory) {
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
            list.append(new VariantItem(QVariant(seize)));
            list.append(new VariantItem(QVariant(lm)));

            model->appendRow(list);
        }
        delete fileModel;
        folderView->resizeColumnToContents(0);
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
    auto path = "/media/uwe/Home/Bilder/Fotos/2017/Abu Dabbab/";
    model->setRootPath(path);

    auto oldModel = folderView->model();
    folderView->setModel(model);
    delete oldModel;
    folderView->setRootIndex(model->index(path));
}
