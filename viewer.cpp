#include <QVBoxLayout>
#include <QGraphicsPixmapItem>

#include <QLabel>

#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
    , graphicsView(nullptr)
{

}

void Viewer::setFile(QString file)
{
    if (file.compare(currentFile) != 0
            && (file.endsWith("jpg", Qt::CaseInsensitive) || file.endsWith("png", Qt::CaseInsensitive)))
    {
        currentFile = file;
        if (graphicsView == nullptr)
            graphicsView = new QGraphicsView(this);

        graphicsView->setStyleSheet("background-color: blue;");
        auto scene = new QGraphicsScene();
        auto item = new QGraphicsPixmapItem(QPixmap(file));
        scene->addItem(item);

        auto layout = new QVBoxLayout(this);
        layout->addWidget(graphicsView);
        graphicsView->setScene(scene);
        graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}

void Viewer::resizeEvent(QResizeEvent*)
{
    if (graphicsView)
        graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
