#include "folderviewmodel.h"

FolderViewModel::FolderViewModel(QObject* parent)
    : QStandardItemModel(parent)
{
}

FolderViewModel::~FolderViewModel()
{
    printf("~FolderViewModel\n");
}
