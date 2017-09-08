#ifndef PRODUCTVIEWMODEL_H
#define PRODUCTVIEWMODEL_H

#include <Core/ITableModel.h>
#include <Model/Product.h>

class ProductViewModel : public ITableModel
{
	enum ProductRoles
	{
		enId,
		enName
	};
	
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
	QVariant data(const QModelIndex &index, int role) const;
};

#endif // PRODUCTVIEWMODEL_H
