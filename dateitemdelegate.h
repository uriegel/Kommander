#ifndef DATEITEMDELEGATE_H
#define DATEITEMDELEGATE_H

#include <QStyledItemDelegate>

class DateItemDelegate : public QStyledItemDelegate
{
public:
    DateItemDelegate(QObject* parent) :
        QStyledItemDelegate(parent) {};

    QString displayText(const QVariant& value, const QLocale& locale) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DATEITEMDELEGATE_H
