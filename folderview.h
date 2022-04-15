#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QTreeView>
#include <QObject>

class FolderViewModel;

class FolderView : public QTreeView
{
public:
    FolderView(QWidget* parent = nullptr);

    void setModels(FolderViewModel* folderViewModel, QAbstractItemModel* model);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
private:
    void onAction();
    FolderViewModel* folderViewModel;
};

#endif // FOLDERVIEW_H
