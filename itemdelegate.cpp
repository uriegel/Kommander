#include <QPainter>

#include "itemdelegate.h"

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto view = qobject_cast<QAbstractItemView*>(this->parent());
    if (option.state & QStyle::State_Selected && option.state & QStyle::State_Active && index.row() == view->currentIndex().row())
    {
        QStyledItemDelegate::paint(painter, option, index);
        painter->save();
        QPen pen(QColor(0, 0, 255));
        painter->setPen(pen);
        painter->drawLine(option.rect.left(), option.rect.bottom()-1, option.rect.right(), option.rect.bottom()-1);
        painter->restore();
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

ItemDelegate::~ItemDelegate()
{
    printf("~ItemDelegate\n");
}
