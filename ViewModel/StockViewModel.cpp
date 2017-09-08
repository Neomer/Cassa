#include "StockViewModel.h"
#include <Core/logs/Logger.h>

StockViewModel::StockViewModel(QObject *parent) :
	ITableModel(parent)
{
	LOG_TRACE;
	_roles << "ИД" << "Продукт" << "Количество" << "Цена";
	s = new Stock();
}

int StockViewModel::rowCount(const QModelIndex &parent) const
{
	LOG_TRACE;
	Q_UNUSED(parent);
	
	return s->count();
}

QVariant StockViewModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			s->at(index.row());
			switch (index.column())
			{
				case 0: return s->getId();
				case 1: return s->getProductId();
				case 2: return s->getQuantity();
				case 3: return s->getPrice();
			}
		}
	}
	return QVariant();
}

