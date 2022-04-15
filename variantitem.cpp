#include "variantitem.h"

VariantItem::VariantItem(const QVariant& var)
    : var(var)
{
}

VariantItem::~VariantItem()
{
    printf("~VariantItem\n");
}

QVariant VariantItem::data(int role) const
{
    return role == Qt::DisplayRole ? var : QVariant();
}

void VariantItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
        var = value;
}
