#ifndef DATEITEMDELEGATE_H
#define DATEITEMDELEGATE_H

#include <QAbstractItemView>

#include "itemdelegate.h"

class DateItemDelegate : public ItemDelegate
{
    Q_OBJECT
public:
    DateItemDelegate(QAbstractItemView* parent) :
        ItemDelegate(parent) {};

    ~DateItemDelegate();

    QString displayText(const QVariant& value, const QLocale& locale) const;
};

#endif // DATEITEMDELEGATE_H
