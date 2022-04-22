pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QStackedWidget>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    Viewer(QWidget *parent = nullptr);

    void init(QStackedWidget* stackedWidget, QGraphicsView* graphicsView, QLayout* mediaPlayerView);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QString currentFile;
    QStackedWidget* stackedWidget;
    QGraphicsView* graphicsView;
    QLayout* mediaPlayerView;
public slots:
    void setFile(QString file);
};


