#include <QVBoxLayout>
#include <QGraphicsPixmapItem>

#include <QLabel>

#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
    , graphicsView(nullptr)
{
}

void Viewer::init(QGraphicsView* graphicsView)
{
    this->graphicsView = graphicsView;
    this->graphicsView->hide();
}

void Viewer::setFile(QString file)
{
    if (file.compare(currentFile) == 0)
        return;
    currentFile = file;
    if (file.endsWith("jpg", Qt::CaseInsensitive) || file.endsWith("png", Qt::CaseInsensitive))
    {
        auto scene = new QGraphicsScene();
        auto item = new QGraphicsPixmapItem(QPixmap(file));
        scene->addItem(item);
        graphicsView->show();
        graphicsView->setScene(scene);
        graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else
        this->graphicsView->hide();
}

void Viewer::resizeEvent(QResizeEvent*)
{
    if (!graphicsView->isHidden())
        graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
