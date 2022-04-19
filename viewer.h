#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QGraphicsView>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    Viewer(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsView* graphicsView;
    QString currentFile;
public slots:
    void setFile(QString file);
};

#endif // VIEWER_H
