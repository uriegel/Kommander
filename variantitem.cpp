#include "variantitem.h"

VariantItem::VariantItem(const QVariant& var)
    : var(var)
{
}

QVariant VariantItem::data(int role) const
{
    return role == Qt::DisplayRole ? var : QVariant();
}
