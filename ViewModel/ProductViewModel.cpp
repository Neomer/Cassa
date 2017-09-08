#include "ProductViewModel.h"
#include <Core/logs/Logger.h>

ProductViewModel::ProductViewModel(QObject *parent) : 
	ITableModel(parent)
{
	LOG_TRACE;
	p = new Product();
	_roles << "ИД" << "Наименование";
}

void ProductViewModel::getAll()
{
	LOG_TRACE;
	
	beginResetModel();
	p->select(QStringList() << "name");
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

QVariant ProductViewModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.isValid())
		{
			p->at(index.row());
		}
		
		switch (index.column())
		{
			case 0: return p->getId();
			case 1: return p->getName();
		}
		
		
		return p->value(index.column());
	}
	
	return QVariant();
}

