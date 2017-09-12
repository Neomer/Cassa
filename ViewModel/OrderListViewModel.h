#ifndef ORDERLISTVIEWMODEL_H
#define ORDERLISTVIEWMODEL_H

#include <Core/ITableModel.h>
#include <Model/Order.h>

class OrderListViewModel : public ITableModel
{
	Q_OBJECT
public:
	explicit OrderListViewModel(QObject *parent = 0);
	~OrderListViewModel();
	
	void loadAll();
	
// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	
	Order *order() { return o; }
	
private:
	Order *o;
};

#endif // ORDERLISTVIEWMODEL_H
