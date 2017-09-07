#ifndef ORDERITEMVIEWMODEL_H
#define ORDERITEMVIEWMODEL_H

#include <QAbstractTableModel>
#include <Model/OrderDetails.h>
#include <Model/Order.h>

class OrderItemViewModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    OrderItemViewModel(QObject *parent = 0);

    void getOrderItemsByOrderId(int id);


private:
    OrderDetails *_order;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // ORDERITEMVIEWMODEL_H
