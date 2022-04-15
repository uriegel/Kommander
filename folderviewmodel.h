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

    const QString* getPath() const;
    virtual void changePath(const QString& path) = 0;
protected:
    QString path;
};

#endif // FOLDERVIEWMODEL_H
