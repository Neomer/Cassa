#include "DayResultViewModel.h"
#include <Core/logs/Logger.h>

DayResultViewModel::DayResultViewModel(QObject *parent) : ITableModel(parent)
{
	LOG_TRACE;
	
	_roles << "Дата" << "Тип оплаты" << "Количество" << "Сумма";
	r = new DayResult();
}

int DayResultViewModel::rowCount(const QModelIndex &parent) const
{
	LOG_TRACE;
	Q_UNUSED(parent);
	
	return r->count();
}

QVariant DayResultViewModel::data(const QModelIndex &index, int role) const
{
	LOG_TRACE;
	
	if (role == Qt::TextAlignmentRole)
	{
		switch (index.column())
		{
			case 0: return Qt::AlignRight;
			case 1: return Qt::AlignCenter;
			case 2: return Qt::AlignRight;
			case 3: return Qt::AlignRight;
		}
	}
	else if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			r->at(index.row());
		}
		
		switch (index.column())
		{
			case 0: return r->getCreationTime().toString("yyyy-MM-dd");
			case 1: 
			{
				switch (r->getPayment())
				{
					case 1: return "Наличными";
					case 2: return "По карте";
				}
			}
			case 2: return r->getCount();
			case 3: return QString::number(r->getSumm(), 'f', 2);
		}
		
		
		return QVariant();
	}
	
	return QVariant();

}

