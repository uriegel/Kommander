#pragma once
#include "itemdelegate.h"
#include <QObject>

class SizeDelegate : public ItemDelegate
{
    Q_OBJECT
public:
    SizeDelegate(QAbstractItemView* parent)
        : ItemDelegate(parent) {}

    QString displayText(const QVariant& value, const QLocale& locale) const override;
};


