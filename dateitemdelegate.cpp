#include <QDateTime>

#include "dateitemdelegate.h"

QString DateItemDelegate::displayText(const QVariant& value, const QLocale& locale) const
{
    if (value.type() == QVariant::DateTime)
        return value.toDateTime().toString(Qt::ISODate);
    else
        return QStyledItemDelegate::displayText(value, locale);
}

DateItemDelegate::~DateItemDelegate()
{
    printf("~DateItemDelegate\n");
}
