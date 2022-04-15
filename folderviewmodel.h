#ifndef FOLDERVIEWMODEL_H
#define FOLDERVIEWMODEL_H

#include <QStandardItemModel>
#include <QObject>

class FolderViewModel : public QStandardItemModel
{
    Q_OBJECT
public:
    FolderViewModel(QObject* parent = nullptr);
    ~FolderViewModel();
};

#endif // FOLDERVIEWMODEL_H
