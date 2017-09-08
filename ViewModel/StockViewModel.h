#ifndef STOCKVIEWMODEL_H
#define STOCKVIEWMODEL_H

#include <Core/ITableModel.h>
#include <Model/Stock.h>

class StockViewModel : public ITableModel
{
	Q_OBJECT
	
public:
	StockViewModel(QObject *parent = 0);
	
    void load();

// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	
private:
	Stock *s;
};

#endif // STOCKVIEWMODEL_H
