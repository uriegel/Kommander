#include "directorysortmodel.h"
#include "filesystemmodel.h"
#include "types.h"

DirectorySortModel::DirectorySortModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    this->setSortCaseSensitivity(Qt::CaseInsensitive);
}

DirectorySortModel::~DirectorySortModel()
{
    delete sourceModel();
    printf("~DirectorySortModel\n");
}

void DirectorySortModel::sort(int column, Qt::SortOrder order)
{
    descending = order == Qt::DescendingOrder;
    this->column = column;
    QSortFilterProxyModel::sort(column, order);
}

bool DirectorySortModel::lessThenByOrder(bool less) const
{
    return descending ? !less : less;
}

bool DirectorySortModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto leftType = left.model()->data(left.model()->index(left.row(), 0), QtRoleItemType);
    auto rightType = right.model()->data(right.model()->index(right.row(), 0), QtRoleItemType);

    if (leftType == (int)ItemType::Item && rightType == (int)ItemType::Item)
    {
        if (column == 0)
        {
            auto leftFile = left.model()->data(left.model()->index(left.row(), 0), Qt::DisplayRole).toString();
            auto rightFile = right.model()->data(right.model()->index(right.row(), 0), Qt::DisplayRole).toString();
            return QString::localeAwareCompare(leftFile, rightFile) < 0;
        }
        else
            return QSortFilterProxyModel::lessThan(left, right);
    }
    else if (leftType == 1 && rightType == 1)
    {
        auto leftDir = left.model()->data(left.model()->index(left.row(), 0), Qt::DisplayRole).toString();
        auto rightDir = right.model()->data(right.model()->index(right.row(), 0), Qt::DisplayRole).toString();
        return lessThenByOrder(QString::localeAwareCompare(leftDir, rightDir) < 0);
    }
    else if (leftType == 0)
        return lessThenByOrder(true);
    else if (rightType == 0)
        return lessThenByOrder(false);
    else if (leftType == 1)
        return lessThenByOrder(true);
    else if (rightType == 1)
        return lessThenByOrder(false);
    else
        return lessThenByOrder(false);
}

