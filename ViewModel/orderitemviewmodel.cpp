#include "orderitemviewmodel.h"
#include <Core/logs/Logger.h>

OrderItemViewModel::OrderItemViewModel(QObject *parent) :
    ITableModel(parent)
{
    LOG_TRACE;
    _order = new OrderDetails();
	_roles << "Продукт" << "Количество" << "Сумма";
	
}

void OrderItemViewModel::getOrderItemsByOrderId(int id)
{
    LOG_TRACE << id;
    if (!_order->loadWithProductName(id))
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


QVariant OrderItemViewModel::data(const QModelIndex &index, int role) const
{
    LOG_TRACE << index.row() << role;

	if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			_order->at(index.row());
		}
		
		switch (index.column())
		{
			case 0: return _order->getProductName();
			case 1: return _order->getQuantity();
			case 2: return _order->getCost();
		}
		
		return QVariant();
	}
	
	return QVariant();
}

