#include <QVBoxLayout>
#include <QGraphicsPixmapItem>

#include <QLabel>

#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
    , graphicsView(nullptr)
{
    setStyleSheet("background-color: red;");
}

void Viewer::setFile(QString file)
{
    if (file.compare(currentFile) == 0)
        return;
    currentFile = file;
    if (file.endsWith("jpg", Qt::CaseInsensitive) || file.endsWith("png", Qt::CaseInsensitive))
    {
        if (graphicsView == nullptr)
            graphicsView = new QGraphicsView(this);

        //graphicsView->setStyleSheet("background-color: blue;");
        auto scene = new QGraphicsScene();
        auto item = new QGraphicsPixmapItem(QPixmap(file));
        scene->addItem(item);

        if (!this->layout())
        {
            new QVBoxLayout(this);
            this->layout()->setSpacing(0);
        }

        this->layout()->addWidget(graphicsView);
        graphicsView->setScene(scene);
        graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else if (graphicsView)
    {
        this->layout()->removeWidget(graphicsView);
        delete graphicsView;
        graphicsView = nullptr;
    }
}

void Viewer::resizeEvent(QResizeEvent*)
{
    if (graphicsView)
        graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
