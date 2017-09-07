#include "orderitemviewmodel.h"
#include <Core/logs/Logger.h>

OrderItemViewModel::OrderItemViewModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    LOG_TRACE;
    _order = new OrderDetails();
}

void OrderItemViewModel::getOrderItemsByOrderId(int id)
{
    LOG_TRACE << id;
    Condition c;
    c["order_id"] = id;
    if (!_order->select(c))
    {
        throw std::runtime_error("Заказ с переданным ID не найден!");
    }
    beginResetModel();
    endResetModel();
}

int OrderItemViewModel::rowCount(const QModelIndex &parent) const
{
    LOG_TRACE;

    Q_UNUSED(parent);

    return _order->count();
}

int OrderItemViewModel::columnCount(const QModelIndex &parent) const
{
    LOG_TRACE;

    Q_UNUSED(parent);

    return _order->columnCount();
}

QVariant OrderItemViewModel::data(const QModelIndex &index, int role) const
{
    LOG_TRACE << index.row() << role;

    if (index.isValid())
    {
        _order->at(index.row());
    }
    if (role == Qt::DisplayRole)
    {
        return QString("row %1 col %2").arg(
                    QString::number(index.row()),
                    QString::number(index.column()));
    }
    return QVariant();
}
