#include "DayResultViewModel.h"
#include <Core/logs/Logger.h>

DayResultViewModel::DayResultViewModel(QObject *parent) : 
	ITableModel(parent)
{
	LOG_TRACE;
	
	_roles << "Дата" << "Тип оплаты" << "Заказов" << "Сумма";
	_model = new DayResult();
	_format = "yyyy-MM-dd";
}

QVariant DayResultViewModel::data(const QModelIndex &index, int role) const
{
	LOG_TRACE;
	
	if (role == Qt::TextAlignmentRole)
	{
		switch (index.column())
		{
			case 0: return (int)(Qt::AlignRight | Qt::AlignVCenter);
			case 1: return (int)(Qt::AlignCenter | Qt::AlignVCenter);
			case 2: return (int)(Qt::AlignRight | Qt::AlignVCenter);
			case 3: return (int)(Qt::AlignRight | Qt::AlignVCenter);
		}
	}
	else if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			_model->at(index.row());
		}
		
		switch (index.column())
		{
			case 0: return ((DayResult *)_model)->getCreationTime().toString(_format);
			case 1: 
			{
				switch (((DayResult *)_model)->getPayment())
				{
					case 1: return "Наличными";
					case 2: return "По карте";
				}
			}
			case 2: return ((DayResult *)_model)->getCount();
			case 3: return QString::number(((DayResult *)_model)->getSumm(), 'f', 2);
		}
		
		
		return QVariant();
	}
	
	return QVariant();
	
}

void DayResultViewModel::loadByDay()
{
	LOG_TRACE;
	beginResetModel();
	((DayResult *)_model)->selectLastDay();
	endResetModel();
}

void DayResultViewModel::loadByWeek()
{
	LOG_TRACE;
	beginResetModel();
	((DayResult *)_model)->selectLastWeek();
	endResetModel();
}

void DayResultViewModel::loadByMonth()
{
	LOG_TRACE;
	beginResetModel();
	((DayResult *)_model)->selectLastMonth();
	endResetModel();
}

