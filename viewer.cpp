#include <QVBoxLayout>
#include <QGraphicsPixmapItem>

#include <QLabel>

#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
    , graphicsView(nullptr)
{
}

void Viewer::init(QStackedWidget* stackedWidget, QGraphicsView* graphicsView, QLayout* mediaPlayerView)
{
    this->stackedWidget = stackedWidget;
    this->graphicsView = graphicsView;
    //this->mediaPlayerView = mediaPlayerView;
    this->graphicsView->hide();
    //this->mediaPlayerView->hide();
}

void Viewer::setFile(QString file)
{
    if (file.compare(currentFile) == 0)
        return;
    currentFile = file;
    if (file.endsWith("jpg", Qt::CaseInsensitive) || file.endsWith("png", Qt::CaseInsensitive))
    {
        stackedWidget->setCurrentIndex(2);
        auto scene = new QGraphicsScene();
        auto item = new QGraphicsPixmapItem(QPixmap(file));
        scene->addItem(item);
        graphicsView->show();
        graphicsView->setScene(scene);
        graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else if (file.endsWith("avi", Qt::CaseInsensitive)
            || file.endsWith("mp4", Qt::CaseInsensitive)
            || file.endsWith("mp3", Qt::CaseInsensitive)
            || file.endsWith("mkv", Qt::CaseInsensitive))
    {
        stackedWidget->setCurrentIndex(1);
    }
    else
        stackedWidget->setCurrentIndex(0);
}

void Viewer::resizeEvent(QResizeEvent*)
{
    if (!graphicsView->isHidden())
        graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
