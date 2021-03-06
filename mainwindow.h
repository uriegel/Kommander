#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *target, QEvent *event) override;
private:
    Ui::MainWindow *ui;

    QLabel statusCount;
    QLabel statusCurrentItem;
    QProgressBar progress;
private slots:
    void onCurrentItemCountChanged(int folders, int items);
    void showHidden(bool show);
    void showPreview(bool show);
};

