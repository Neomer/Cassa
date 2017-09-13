#ifndef ITABLEMODEL_H
#define ITABLEMODEL_H

#include <QAbstractTableModel>
#include <Core/IStorageModel.h>

class ITableModel: public QAbstractTableModel
{
	Q_OBJECT
	
public:
	ITableModel(QObject *parent = 0);
	
// QAbstractItemModel interface
public:
	int columnCount(const QModelIndex &parent) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	int rowCount(const QModelIndex &parent) const;
	
	IStorageModel *model() { return _model; }
	
protected:
	QStringList _roles;
	IStorageModel *_model;
};

#endif // ITABLEMODEL_H
