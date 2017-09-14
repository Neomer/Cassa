#ifndef ORDERNAMELISTVIEWMODEL_H
#define ORDERNAMELISTVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <Model/OrderName.h>

class OrderNameListViewModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit OrderNameListViewModel(QObject *parent = 0);
	~OrderNameListViewModel();
	
private:
	OrderName *_model;
	
// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
};

#endif // ORDERNAMELISTVIEWMODEL_H
