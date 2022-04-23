#pragma once

#include <QWidget>
#include <phonon/mediaobject.h>

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE


class Viewer : public QWidget
{
    Q_OBJECT
public:
    Viewer(QWidget *parent = nullptr);

    void init(Ui::MainWindow *ui);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
private:
    QString currentFile;
    Ui::MainWindow *ui;
    Phonon::MediaObject* mediaObject;
public slots:
    void setFile(QString file, bool force = false);
};


