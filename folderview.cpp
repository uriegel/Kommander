#include <QKeyEvent>
#include <QDir>

#include "folderview.h"
#include "folderviewmodel.h"
#include "directorysortmodel.h"

FolderView::FolderView(QWidget* parent)
    : QTreeView(parent)
    , folderViewModel(nullptr)
{
    setSelectionMode(MultiSelection);
    setAllColumnsShowFocus(true);
    setTabKeyNavigation(false);
}

void FolderView::setModels(FolderViewModel* folderViewModel, QAbstractItemModel* model)
{
    if (this->folderViewModel)
        disconnect(this->folderViewModel, &FolderViewModel::itemsRetrieved, this, &FolderView::onItemsRetrieved);
    this->folderViewModel = folderViewModel;
    connect(this->folderViewModel, &FolderViewModel::itemsRetrieved, this, &FolderView::onItemsRetrieved);
    QTreeView::setModel(model);
}

void FolderView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        selectionModel()->clearSelection();
    break;
    case Qt::Key_Insert:
    {
        auto index = currentIndex();

        selectionModel()->select(QItemSelection(model()->index(index.row(), 0), model()->index(index.row(), 2)), QItemSelectionModel::Toggle);
        selectionModel()->setCurrentIndex(model()->index(qMin(index.row()+1, model()->rowCount()-1), 0), QItemSelectionModel::Current);
    }
    break;
    case Qt::Key_Tab:
    break;
    case Qt::Key_Home:
        if (event->modifiers().testFlag(Qt::ShiftModifier))
        {
            auto index = currentIndex();
            selectionModel()->clearSelection();
            selectionModel()->select(QItemSelection(model()->index(1, 0), model()->index(index.row(), 2)), QItemSelectionModel::Select);
        }
        else
            QTreeView::keyPressEvent(event);
    break;
    case Qt::Key_End:
        if (event->modifiers().testFlag(Qt::ShiftModifier))
        {
            auto index = currentIndex();
            selectionModel()->clearSelection();
            selectionModel()->select(QItemSelection(model()->index(index.row(), 0), model()->index(model()->rowCount()-1, 2)), QItemSelectionModel::Select);
        }
        else
            QTreeView::keyPressEvent(event);
    break;
    case Qt::Key_Plus:
        if (event->modifiers().testFlag(Qt::KeypadModifier))
            selectionModel()->select(QItemSelection(model()->index(1, 0), model()->index(model()->rowCount()-1, 2)), QItemSelectionModel::Select);
        else
            QTreeView::keyPressEvent(event);
    break;
    case Qt::Key_Minus:
        if (event->modifiers().testFlag(Qt::KeypadModifier))
            selectionModel()->clearSelection();
        else
            QTreeView::keyPressEvent(event);
    break;
    case Qt::Key_Return:
        onAction();
    break;
    default:
        QTreeView::keyPressEvent(event);
    break;
    }
}

void FolderView::mouseDoubleClickEvent(QMouseEvent *)
{
    onAction();
}

void FolderView::onAction()
{
    if (getCurrentItemType() != ItemType::Item)
        changePath(getCurrentPath());

//    auto rows = selectionModel()->selectedRows();
//    if (rows.count() == 0)
//    {
//    }
}

void FolderView::changePath(QString path)
{
    this->folderViewModel->changePath(path);
}

QString FolderView::getCurrentPath() const
{
    return getPath(currentIndex().row());
}

QString FolderView::getPath(int row) const
{
    auto name = model()->data(model()->index(row, 0));
    auto path = folderViewModel->getPath();
    return QDir::cleanPath(*path + "/" + name.toString());
}

ItemType FolderView::getItemType(int row) const
{
    return (ItemType)model()->data(model()->index(row, 0), QtRoleItemType).toInt();
}

ItemType FolderView::getCurrentItemType() const
{
    return getItemType(currentIndex().row());
}

void FolderView::onItemsRetrieved(QString previousFolder)
{
    auto selectedItem = qMax(0, previousFolder.length() > 0 ? findItemIndex(previousFolder) : 0);
    selectionModel()->setCurrentIndex(model()->index(selectedItem, 0), QItemSelectionModel::Current);
    emit pathChanged(*folderViewModel->getPath());
}

int FolderView::findItemIndex(QString itemToFind)
{
    for (auto i = 0; i < model()->rowCount(); i++)
    {
        auto name = model()->data(model()->index(i, 0));
        if (name.toString().compare(itemToFind) == 0)
            return i;
    }
    return -1;
}
