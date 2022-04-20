#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QTreeView>
#include <QKeyEvent>
#include <QDateTime>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "folderview.h"
#include "filesystemmodel.h"
#include "viewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->viewer->init(ui->graphicsView);

//    ui->viewer->hide();
    ui->verticalSplitter->setSizes(QList<int>({INT_MAX, INT_MAX}));

    FileSystemModel::attach(ui->leftFolderView);
    ui->leftFolderView->changePath(QDir::cleanPath(QDir::homePath()));

    FileSystemModel::attach(ui->rightFolderView);
    ui->rightFolderView->changePath(QDir::cleanPath(QDir::homePath()));

    ui->leftFolderView->installEventFilter(this);
    ui->rightFolderView->installEventFilter(this);

    ui->statusbar->addPermanentWidget(&statusCurrentItem);
    ui->statusbar->addPermanentWidget(&statusCount);

    connect(ui->leftFolderView, &FolderView::currentItemChanged, &statusCurrentItem, &QLabel::setText);
    connect(ui->rightFolderView, &FolderView::currentItemChanged, &statusCurrentItem, &QLabel::setText);
    connect(ui->leftFolderView, &FolderView::currentItemCountChanged, this, &MainWindow::onCurrentItemCountChanged);
    connect(ui->rightFolderView, &FolderView::currentItemCountChanged, this, &MainWindow::onCurrentItemCountChanged);

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
                ui->rightFolderView->setFocus(Qt::FocusReason::TabFocusReason);
            else if (target == ui->rightFolderView)
                ui->leftFolderView->setFocus(Qt::FocusReason::TabFocusReason);
            return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::onCurrentItemCountChanged(int folders, int items)
{
    QString count;
    QTextStream(&count) << folders << " Verz.  " << items << " Dateien";
    statusCount.setText(count);
}
