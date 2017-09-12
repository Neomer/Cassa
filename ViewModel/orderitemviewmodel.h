#ifndef ORDERITEMVIEWMODEL_H
#define ORDERITEMVIEWMODEL_H

#include <Core/ITableModel.h>
#include <Model/OrderDetails.h>
#include <Model/Order.h>

class OrderItemViewModel : public ITableModel
{
    Q_OBJECT

public:
    OrderItemViewModel(QObject *parent = 0);

    void getOrderItemsByOrderId(int id);

    OrderDetails *items() { return _order; }


private:
    OrderDetails *_order;

public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // ORDERITEMVIEWMODEL_H
