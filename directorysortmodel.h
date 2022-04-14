#ifndef DIRECTORYSORTMODEL_H
#define DIRECTORYSORTMODEL_H

#include <QSortFilterProxyModel>

class DirectorySortModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    DirectorySortModel(QObject *parent = nullptr);
    ~DirectorySortModel();

    void sort(int column, Qt::SortOrder order=Qt::AscendingOrder) override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
private:
    bool lessThenByOrder(bool less) const;
    bool descending;
};

#endif // DIRECTORYSORTMODEL_H
