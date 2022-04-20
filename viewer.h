#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QGraphicsView>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    Viewer(QWidget *parent = nullptr);

    void init(QGraphicsView* graphicsView);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QString currentFile;
    QGraphicsView* graphicsView;
public slots:
    void setFile(QString file);
};

#endif // VIEWER_H
