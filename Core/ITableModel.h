#ifndef ITABLEMODEL_H
#define ITABLEMODEL_H

#include <QAbstractTableModel>

class ITableModel: public QAbstractTableModel
{
	Q_OBJECT
	
public:
	ITableModel(QObject *parent = 0);
	
// QAbstractItemModel interface
public:
	int columnCount(const QModelIndex &parent) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	
protected:
	QStringList _roles;
};

#endif // ITABLEMODEL_H
