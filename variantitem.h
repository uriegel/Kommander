#ifndef VARIANTITEM_H
#define VARIANTITEM_H

#include <QStandardItem>

class VariantItem : public QStandardItem
{
public:
    VariantItem(const QVariant& var);

    ~VariantItem();

    QVariant data(int role = Qt::UserRole + 1) const override;
    void setData(const QVariant &value, int role = Qt::UserRole + 1) override;

private:
    QVariant var;
};

#endif // VARIANTITEM_H
