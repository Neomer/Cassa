#include "ProductViewModel.h"
#include <Core/logs/Logger.h>

ProductViewModel::ProductViewModel(QObject *parent) : 
	QAbstractTableModel(parent)
{
	LOG_TRACE;
	p = new Product();
}

void ProductViewModel::getAll()
{
	LOG_TRACE;
	
	beginResetModel();
	p->select();
	endResetModel();
}

void ProductViewModel::rowSelected(int index)
{
	LOG_TRACE;
	
	p->at(index);
}

int ProductViewModel::rowCount(const QModelIndex &parent) const
{
	LOG_TRACE;
	Q_UNUSED(parent);
	
	return p->count();
}

int ProductViewModel::columnCount(const QModelIndex &parent) const
{
	LOG_TRACE;
	Q_UNUSED(parent);
	
	return p->columnCount();
}

QVariant ProductViewModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			p->at(index.row());
		}
		
		return p->value(index.column());
	}
	
	return QVariant();
}

QHash<int, QByteArray> ProductViewModel::roleNames() const
{
	LOG_TRACE;
	
	QHash<int, QByteArray> ret;
	ret[0] = "ID";
	ret[1] = "Наименование";
	ret[2] = "Остаток";
	ret[3] = "Цена";
	
	return ret;
}

QVariant ProductViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	LOG_TRACE;
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch (section)
		{
			case 0: return "Ид";
			case 1: return "Наименование";
			case 2: return "Количество";
			case 3: return "Цена";
		}
	}
	else
	{
		return QAbstractTableModel::headerData(section, orientation, role);
	}
	
	return QVariant();
}

