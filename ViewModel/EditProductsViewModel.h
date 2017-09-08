#ifndef EDITPRODUCTS_H
#define EDITPRODUCTS_H

#include <QDialog>
#include <Model/Product.h>
#include <ViewModel/ProductViewModel.h>

namespace Ui {
    class FormEditProducts;
}


class EditProductsViewModel : public QDialog
{
	Q_OBJECT
	
public:
	explicit EditProductsViewModel(QWidget *parent = 0);
	~EditProductsViewModel();
	
	void show();
	
private slots:
	void rowSelected(const QModelIndex &index);
	
	void createProduct();
	void editProduct();
	void removeProduct();
	
private:
	void update();	
	
	Ui::FormEditProducts *ui;
	ProductViewModel *_products;
};


#endif // EDITPRODUCTS_H
