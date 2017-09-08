#include "ITableModel.h"

ITableModel::ITableModel(QObject *parent) :
	QAbstractTableModel(parent)
{
	
}

int ITableModel::columnCount(const QModelIndex &parent) const
{
	return _roles.count();
}

QVariant ITableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		if (section < _roles.count() && section >= 0)
		{
			return _roles[section];
		}
		else
		{
			return QVariant();
		}
	}
	else
	{
		return QVariant();
	}
}

