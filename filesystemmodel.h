#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>

#include "folderviewmodel.h"
#include "directorysortmodel.h"


class FileSystemModel : public FolderViewModel
{
    Q_OBJECT
public:
    static QAbstractItemModel* create(QObject* parent = nullptr);
private:
    FileSystemModel(QObject* parent = nullptr);

    void getExtendedInfos();

    QString path;

public slots:
    void setSalary(int newSalary);
signals:
    void salaryChanged(int newSalary);
};

#endif // FILESYSTEMMODEL_H
