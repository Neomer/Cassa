#include "OrderListViewModel.h"
#include <Core/logs/Logger.h>

OrderListViewModel::OrderListViewModel(QObject *parent) : 
	ITableModel(parent)
{
	LOG_TRACE;
	_roles << "ИД" << "Дата" << "Наименование" << "Сумма" << "Состояние" << "Способ оплаты";
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
			case 0: return Qt::AlignRight;
			case 1: return Qt::AlignCenter;
			case 2: return Qt::AlignLeft;
			case 3: return Qt::AlignRight;
			case 4: return Qt::AlignCenter;
			case 5: return Qt::AlignCenter;
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
			case 4: return o->getIsPayed() ? "Оплачен" : o->getIsCredited() ? "В долг" : "";
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

