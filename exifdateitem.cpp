#include "exifdateitem.h"

ExifDateItem::ExifDateItem(const QVariant& var)
    : VariantItem((var))
    , isExif(false)
{
}

void ExifDateItem::setData(const QVariant& var, int role)
{
    if (role == Qt::EditRole)
        isExif = true;
    VariantItem::setData(var, role);
}

QVariant ExifDateItem::data(int role) const
{
    if (role == Qt::TextColorRole && isExif)
        return QColor(Qt::blue);
    else
        return VariantItem::data(role);
}
