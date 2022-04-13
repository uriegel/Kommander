#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QTreeView>
#include <QObject>

class FolderView : public QTreeView
{
public:
    FolderView(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // FOLDERVIEW_H
