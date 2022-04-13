#include <QKeyEvent>

#include "folderview.h"

FolderView::FolderView()
{
    setSelectionMode(MultiSelection);
    setAllColumnsShowFocus(true);
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

            selectionModel()->select(QItemSelection(model()->index(index.row(), 0), model()->index(index.row(), 2)), QItemSelectionModel::Select);
            selectionModel()->setCurrentIndex(model()->index(qMin(index.row()+1, model()->rowCount()-1), 0), QItemSelectionModel::Current);
        }
        break;
        default:
            QTreeView::keyPressEvent(event);
        break;
    }
}
