#include "folderviewmodel.h"

FolderViewModel::FolderViewModel(QObject* parent)
    : QStandardItemModel(parent)
{
}

FolderViewModel::~FolderViewModel()
{
    printf("~FolderViewModel\n");
}

const QString* FolderViewModel::getPath() const
{
    return &path ;
}
