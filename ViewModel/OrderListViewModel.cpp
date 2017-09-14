#include "OrderListViewModel.h"
#include <Core/logs/Logger.h>

OrderListViewModel::OrderListViewModel(QObject *parent) : 
	ITableModel(parent)
{
	LOG_TRACE;
    _roles << "ИД" << "Дата" << "Алкоголик" << "Сумма" << "Состояние" << "Способ оплаты";
	o = new Order();
}

OrderListViewModel::~OrderListViewModel()
{
	LOG_TRACE;
	delete o;
}

void OrderListViewModel::loadAll()
{
	LOG_TRACE;
	beginResetModel();
	
	o->selectOrdersWithSumm();
	
	endResetModel();
}

int OrderListViewModel::rowCount(const QModelIndex &parent) const
{
	LOG_TRACE;
	Q_UNUSED(parent);
	return o->count();
}

QVariant OrderListViewModel::data(const QModelIndex &index, int role) const
{
	LOG_TRACE << index.row() << role;

	if (role == Qt::TextAlignmentRole)
	{
		switch (index.column())
		{
			case 0: return (int)(Qt::AlignRight | Qt::AlignVCenter);
			case 1: return (int)(Qt::AlignCenter | Qt::AlignVCenter);
			case 2: return (int)(Qt::AlignLeft | Qt::AlignVCenter);
			case 3: return (int)(Qt::AlignRight | Qt::AlignVCenter);
			case 4: return (int)(Qt::AlignCenter | Qt::AlignVCenter);
			case 5: return (int)(Qt::AlignCenter | Qt::AlignVCenter);
		}
	}
	else if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			o->at(index.row());
		}
		
		switch (index.column())
		{
			case 0: return o->getId();
			case 1: return o->getCreationTime().toString("dd MMM hh:mm");
			case 2: return o->getBuyer();
			case 3: return QString::number(o->getSumm(), 'f', 2);
			case 4: 
			{
				switch (o->getPayState())
				{
					case ORDER_NOTPAYED:
						return "-";
					case ORDER_CREDITED:
						return "В долг";
					case ORDER_PAYED:
						return "Оплачен";
				}
			}
			case 5:
			{
				switch(o->getPaymentType())
				{
					case 0: return "-";
					case 1: return "Наличными";
					case 2: return "По карте";
				}
			}		
		}
		
		return QVariant();
	}
	
	return QVariant();
}

