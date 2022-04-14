#ifndef VARIANTITEM_H
#define VARIANTITEM_H

#include <QStandardItem>

class VariantItem : public QStandardItem
{
public:
    VariantItem(const QVariant& var);

    ~VariantItem();

    virtual QVariant data(int role = Qt::UserRole + 1) const;

private:
    QVariant var;
};

#endif // VARIANTITEM_H
