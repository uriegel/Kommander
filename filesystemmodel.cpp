#include <QFileSystemModel>
#include <QDateTime>
#include <QThreadPool>
#include <QThread>

#include "filesystemmodel.h"
#include "directorysortmodel.h"
#include "variantitem.h"

QAbstractItemModel* FileSystemModel::create(QObject* parent)
{
    auto model = new FileSystemModel(parent);
    auto sortModel = new DirectorySortModel(parent);
    sortModel->setSourceModel(model);
    return sortModel;
}

FileSystemModel::FileSystemModel(QObject* parent)
    : FolderViewModel(parent)
{
    setHorizontalHeaderItem(0, new QStandardItem(tr("Name")));
    setHorizontalHeaderItem(1, new QStandardItem(tr("Größe")));
    setHorizontalHeaderItem(2, new QStandardItem(tr("Datum")));

    auto fileModel = new QFileSystemModel(this);
    path = QDir::homePath() + "/Dokumente";
    //path = "/media/uwe/Home/Bilder/Fotos/2017/Abu Dabbab/";
    fileModel->setRootPath(path);

    connect(this, SIGNAL(salaryChanged(int)), this, SLOT(setSalary(int)));

    connect(fileModel, &QFileSystemModel::directoryLoaded, this, [this, fileModel](const QString &directory) {
        auto parentIndex = fileModel->index(directory);
        int numRows = fileModel->rowCount(parentIndex);
        auto list = QList<QStandardItem*>();
        list.append(new QStandardItem(QIcon("/home/uwe/Projekte/Qt/Kommander/parent.svg"), ".."));
        list.append(new VariantItem(QVariant(0)));
        list.append(new VariantItem(QVariant()));

        list[0]->setData(QVariant(1), Qt::UserRole+1);
        appendRow(list);

        for (auto i = 0; i < numRows; i++) {
            auto index = fileModel->index(i, 0, parentIndex);
            auto content = fileModel->data(index, Qt::DisplayRole).toString();
            auto icon = fileModel->fileIcon(index);
            auto size = fileModel->size(index);
            auto lastModified = fileModel->lastModified(index);

            auto list = QList<QStandardItem*>();
            list.append(new QStandardItem(icon, content));
            list.append(new VariantItem(QVariant(size)));
            list.append(new VariantItem(QVariant(lastModified)));

            list[0]->setData(QVariant(fileModel->isDir(index) ? 1 : 2), Qt::UserRole+1);
            appendRow(list);
        }

        getExtendedInfos();
        delete fileModel;
    });
}

void FileSystemModel::getExtendedInfos()
{
    QThreadPool::globalInstance()->start([this]() {
        QThread::sleep(4);
        emit salaryChanged(345);
    });
}

void FileSystemModel::setSalary(int newSalary)
{
    auto affe = data(index(5, 0), Qt::DisplayRole);
    setData(index(5, 0), "Habs geändert", Qt::DisplayRole);
    auto affe4 = data(index(5, 0), Qt::DisplayRole);
    emit dataChanged(index(5, 0), index(5, 1));
}
