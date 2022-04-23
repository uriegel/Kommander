#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <phonon/audiooutput.h>

#include "ui_mainwindow.h"
#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
{
}

void Viewer::init(Ui::MainWindow *ui)
{
    this->ui = ui;
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, ui->videoWidget);
    auto audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    ui->seekSlider->setMediaObject(mediaObject);
    ui->volumeSlider->setAudioOutput(audioOutput);
}

void Viewer::setFile(QString file, bool force)
{
    if (force || (!isHidden() && file.compare(currentFile) != 0))
    {
        if (file.endsWith("jpg", Qt::CaseInsensitive) || file.endsWith("png", Qt::CaseInsensitive))
        {
            mediaObject->stop();
            ui-> stackedWidget->setCurrentIndex(2);
            auto scene = new QGraphicsScene();
            auto item = new QGraphicsPixmapItem(QPixmap(file));
            scene->addItem(item);
            ui->graphicsView->show();
            ui->graphicsView->setScene(scene);
            ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
        else if (file.endsWith("avi", Qt::CaseInsensitive)
                || file.endsWith("mp4", Qt::CaseInsensitive)
                || file.endsWith("mp3", Qt::CaseInsensitive)
                || file.endsWith("mkv", Qt::CaseInsensitive))
        {
            ui->stackedWidget->setCurrentIndex(1);
            mediaObject->stop();
            mediaObject->setCurrentSource(QString(file));
            mediaObject->play();
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(0);
            mediaObject->stop();
        }
    }
    currentFile = file;
}

void Viewer::resizeEvent(QResizeEvent*)
{
    if (ui->stackedWidget->currentIndex() == 2)
        ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Viewer::showEvent(QShowEvent*)
{
    setFile(currentFile, true);
}

void Viewer::hideEvent(QHideEvent*)
{
    ui->stackedWidget->setCurrentIndex(0);
    mediaObject->stop();
}
