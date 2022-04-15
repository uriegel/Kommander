#include <memory>
#include <vector>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QThreadPool>
#include <QThread>

#include "filesystemmodel.h"
#include "directorysortmodel.h"
#include "dateitemdelegate.h"
#include "variantitem.h"
#include "exifdatetimereader.h"
#include "exifdateitem.h"
#include "folderview.h"
#include "types.h"

using namespace std;

void FileSystemModel::attach(FolderView* folderView)
{
    auto model = new FileSystemModel(folderView);
    auto sortModel = new DirectorySortModel(folderView);
    sortModel->setSourceModel(model);
    folderView->setModels(model, sortModel);
    folderView->setItemDelegateForColumn(0, new ItemDelegate(folderView));
    folderView->setItemDelegateForColumn(1, new ItemDelegate(folderView));
    folderView->setItemDelegateForColumn(2, new DateItemDelegate(folderView));
    folderView->header()->setSortIndicator(0, Qt::AscendingOrder);
    folderView->setColumnWidth(0, 300);
    folderView->setColumnWidth(1, 140);
}

FileSystemModel::FileSystemModel(QObject* parent)
    : FolderViewModel(parent)
{
    setHorizontalHeaderItem(0, new QStandardItem(tr("Name")));
    setHorizontalHeaderItem(1, new QStandardItem(tr("Größe")));
    setHorizontalHeaderItem(2, new QStandardItem(tr("Datum")));

    auto fileModel = new QFileSystemModel(this);


    fileModel->setFilter(QDir::Files|QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);

    fileModel->setNameFilterDisables(false);
    path = QDir::cleanPath(QDir::homePath() + "/Dokumente");
    //path = QDir::cleanPath(QDir::homePath());
    //path = QDir::cleanPath("/media/uwe/Home/Bilder/Fotos/2017/Abu Dabbab/");

    fileModel->setRootPath(path);

    connect(fileModel, &QFileSystemModel::directoryLoaded, this, [this, fileModel](const QString &directory) {
        auto parentIndex = fileModel->index(directory);
        int numRows = fileModel->rowCount(parentIndex);
        auto list = QList<QStandardItem*>();
        list.append(new QStandardItem(QIcon("/home/uwe/Projekte/Qt/Kommander/parent.svg"), ".."));
        list.append(new VariantItem(QVariant(0)));
        list.append(new VariantItem(QVariant()));

        list[0]->setData(QVariant((int)ItemType::Parent), QtRoleItemType);
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
            list.append(new ExifDateItem(QVariant(lastModified)));

            list[0]->setData(QVariant(int(fileModel->isDir(index) ? ItemType::Folder : ItemType::Item)), QtRoleItemType);
            appendRow(list);
        }

        getExtendedInfos();
        delete fileModel;
    });
}

void FileSystemModel::getExtendedInfos()
{
    auto extendedInfos = make_shared<vector<ExtendedInfo>>();
    for (auto i = 0; i < rowCount(); i++)
    {
        auto name = data(index(i, 0), Qt::DisplayRole).toString();
        if (name.endsWith("jpg", Qt::CaseInsensitive))
            extendedInfos->push_back({i, path + "/"  + name, QDateTime() });
    }

    auto setExtendedInfos = [extendedInfos, this]()
    {
        auto insertExif = [this](ExtendedInfo& info)
        {
            if (info.exifDate.isValid())
                setData(index(info.index, 2), QVariant(info.exifDate), Qt::EditRole);
        };

        for_each(extendedInfos->begin(), extendedInfos->end(), insertExif);
        emit dataChanged(index(0, 0), index(rowCount() - 1, 2));
    };

    connect(this, &FileSystemModel::extendedInfosRetrieved, this, setExtendedInfos);

    QThreadPool::globalInstance()->start([extendedInfos, setExtendedInfos, this]() {
//        QThread::sleep(4);

        auto checkExif = [](ExtendedInfo& info)
        {
            info.exifDate = getExifDateTime(info.file);
        };

        for_each(extendedInfos->begin(), extendedInfos->end(), checkExif);
        emit extendedInfosRetrieved();
       // TODO disconnect(this, &FileSystemModel::extendedInfosRetrieved, this, setExtendedInfos);
    });
}

