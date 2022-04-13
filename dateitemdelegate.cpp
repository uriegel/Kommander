#include <QDateTime>
#include <QPainter>
#include <QLabel>


#include "dateitemdelegate.h"

QString DateItemDelegate::displayText(const QVariant& value, const QLocale& locale) const
{
    if (value.type() == QVariant::DateTime)
        return value.toDateTime().toString(Qt::ISODate);
    else
        return QStyledItemDelegate::displayText(value, locale);
}

void DateItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        if (option.state & QStyle::State_Selected && option.state & QStyle::State_Active)
        {



//            QStyleOptionViewItem opt = option;
//               initStyleOption(&opt, index);
//               QLabel widget;

//               QPalette pal;
//               pal.setColor(QPalette::Background, Qt::black);
//               widget.setPalette(pal);
//               widget.setStyleSheet("background-color:black;");
//               QStyle *style = widget.style();
//               //style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, &widget);
//               painter->setBackground(QBrush(QColor::fromRgb(0, 0, 255)));
//               painter->fillRect(opt.rect, QBrush(QColor::fromRgb(200, 200, 255)));
//               style->drawItemText(painter, opt.rect, opt.displayAlignment, opt.palette, true, opt.text);

                       //Control(QStyle::CE_ItemViewItem, &opt, painter, &widget);


//            QStyleOptionViewItem newOption = option;
//            int r; int g; int b;
//            option.backgroundBrush.color().getRgb(&r, &g, &b);
//            newOption.backgroundBrush = QBrush(QColor::fromRgb(255, g, b));
//            newOption.viewItemPosition = QStyleOptionViewItem::ViewItemPosition::End;
//            painter->save();
//            //painter->fillRect(option.rect, option.palette.highlight());
//            //painter->fillRect(option.rect, option.palette.Dark);
//            painter->setBrush(QBrush(QColor::fromRgb(255, 0, 0)));
//            painter->setBackground(QBrush(QColor::fromRgb(0, 0, 255)));
//            //QStyledItemDelegate::paint(painter, newOption, index);
//            //painter->drawText(option.rect.left(), option.rect.bottom(), "Guten Abend");
//            //QStyledItemDelegate::paint(painter, option, index);
            QStyledItemDelegate::paint(painter, option, index);
            painter->drawRect(option.rect);
//            painter->restore();

            //
        }
        else
            QStyledItemDelegate::paint(painter, option, index);
}
