#ifndef PRODUCTVIEWMODEL_H
#define PRODUCTVIEWMODEL_H

#include <QAbstractTableModel>
#include <Model/Product.h>

class ProductViewModel : public QAbstractTableModel
{
public:
	ProductViewModel(QObject *parent = 0);
	
	void getAll();
	
	void rowSelected(int index);
	Product *product() { return p; }
		
private:
	Product *p;
	
	// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // PRODUCTVIEWMODEL_H
