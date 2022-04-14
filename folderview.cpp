#include <QKeyEvent>

#include "folderview.h"

FolderView::FolderView(QWidget* parent)
    : QTreeView(parent)
{
    setSelectionMode(MultiSelection);
    setAllColumnsShowFocus(true);
    setTabKeyNavigation(false);
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
    default:
        QTreeView::keyPressEvent(event);
    break;
    }
}
