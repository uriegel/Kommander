#include "sizedelegate.h"

QString SizeDelegate::displayText(const QVariant& value, const QLocale& locale) const
{
    if (value.type() == QVariant::LongLong)
    {
        auto sizeStr = QString::number(value.toLongLong());
        if (sizeStr.length() > 3)
        {
            QString sep = ".";
            auto sizePart = sizeStr;
            sizeStr = "";
            for (auto i = 3; i < sizePart.length(); i += 3) {
                auto extract = sizePart.mid(sizePart.length() - i, 3);
                sizeStr = sep + extract + sizeStr;
            }
            auto strfirst = sizePart.mid(0, (sizePart.length() % 3 == 0) ? 3 : (sizePart.length() % 3));
            sizeStr = strfirst + sizeStr;

        }
        return sizeStr;
    }
    else
        return QStyledItemDelegate::displayText(value, locale);
}
