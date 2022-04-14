#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>

#include "folderviewmodel.h"
#include "directorysortmodel.h"


class FileSystemModel : public FolderViewModel
{
public:
    static QAbstractItemModel* create(QObject* parent = nullptr);
private:
    FileSystemModel(QObject* parent = nullptr);
};

#endif // FILESYSTEMMODEL_H
