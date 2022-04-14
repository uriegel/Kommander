#ifndef FOLDERVIEWMODEL_H
#define FOLDERVIEWMODEL_H

#include <QStandardItemModel>
#include <QObject>

class FolderViewModel : public QStandardItemModel
{
public:
    FolderViewModel(QObject* parent = nullptr);
};

#endif // FOLDERVIEWMODEL_H
