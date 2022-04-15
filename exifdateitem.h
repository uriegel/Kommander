#ifndef EXIFDATEITEM_H
#define EXIFDATEITEM_H

#include "variantitem.h"
#include <QObject>

class ExifDateItem : public VariantItem
{
public:
    ExifDateItem(const QVariant& var);

    QVariant data(int role = Qt::UserRole + 1) const override;
    void setData(const QVariant &value, int role = Qt::UserRole + 1) override;
private:
    bool isExif;
};

#endif // EXIFDATEITEM_H
