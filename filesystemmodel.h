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

class FolderView;

class FileSystemModel : public FolderViewModel
{
    Q_OBJECT
public:
    static void attach(FolderView* folderView);
    void changePath(QString path) override;
private:
    FileSystemModel(QObject* parent = nullptr);

    void getExtendedInfos();

signals:
    void extendedInfosRetrieved();
};

#endif // FILESYSTEMMODEL_H
