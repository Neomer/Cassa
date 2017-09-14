#include "OrderNameListViewModel.h"
#include <Core/logs/Logger.h>

OrderNameListViewModel::OrderNameListViewModel(QObject *parent) : 
	QAbstractListModel(parent)
{
	_model = new OrderName();
	_model->select();
}

OrderNameListViewModel::~OrderNameListViewModel()
{
	delete _model;
}

int OrderNameListViewModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return  _model->count();
}

QVariant OrderNameListViewModel::data(const QModelIndex &index, int role) const
{
	switch (role)
	{
		case Qt::EditRole:
		{
			if (!_model->at(index.row()))
				return QVariant();
			
			return _model->getName();
		}
		case Qt::DisplayRole:
		{
			if (!_model->at(index.row()))
				return QVariant();
			
			return _model->getName();
		}
	}
	return QVariant();
}
