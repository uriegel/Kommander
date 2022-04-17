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
    void focusInEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    int findItemIndex(QString itemToFind);
private:
    void onAction();
    FolderViewModel* folderViewModel;
public slots:
    void onItemsRetrieved(QString previousFolder);
    void changePath(QString path);
private slots:
    void onCurrentRowChanged(const QModelIndex& current, const QModelIndex& previous);
signals:
    void pathChanged(QString path);
    void currentItemChanged(QString itemPath);
    void currentItemCountChanged(int folders, int items);

private:
    int folders = 0;
    int items = 0;
};

#endif // FOLDERVIEW_H
