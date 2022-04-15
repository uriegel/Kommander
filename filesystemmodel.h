#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QDateTime>

#include "folderviewmodel.h"
#include "directorysortmodel.h"

struct ExtendedInfo
{
    int index;
    QString file;
    QDateTime exifDate;
};

class FileSystemModel : public FolderViewModel
{
    Q_OBJECT
public:
    static QAbstractItemModel* create(QObject* parent = nullptr);
private:
    FileSystemModel(QObject* parent = nullptr);

    void getExtendedInfos();

    QString path;

signals:
    void extendedInfosRetrieved();
};

#endif // FILESYSTEMMODEL_H
