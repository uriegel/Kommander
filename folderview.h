#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QTreeView>
#include <QObject>

#include "types.h"

class FolderViewModel;

class FolderView : public QTreeView
{
    Q_OBJECT
public:
    FolderView(QWidget* parent = nullptr);

    void setModels(FolderViewModel* folderViewModel, QAbstractItemModel* model);
    QString getPath(int row) const;
    QString getCurrentPath() const;
    ItemType getItemType(int row) const;
    ItemType getCurrentItemType() const;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    int findItemIndex(QString itemToFind);
private:
    void onAction();
    FolderViewModel* folderViewModel;
public slots:
    void onItemsRetrieved(QString previousFolder);
    void changePath(QString path);
signals:
    void pathChanged(QString path);
};

#endif // FOLDERVIEW_H
