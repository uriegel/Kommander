#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QTreeView>
#include <QKeyEvent>
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

    ui->leftFolderView->installEventFilter(this);
    ui->rightFolderView->installEventFilter(this);

    ui->leftFolderView->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto keyEvent = reinterpret_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab)
        {
            if (target == ui->leftFolderView)
                ui->rightFolderView->setFocus();
            else if (target == ui->rightFolderView)
                ui->leftFolderView->setFocus();
            return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}

