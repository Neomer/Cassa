#ifndef FORMMAINVIEWMODEL_H
#define FORMMAINVIEWMODEL_H

#include <QWidget>
#include <ViewModel/FormOrderViewModel.h>
#include <ViewModel/EditProductsViewModel.h>
#include <ViewModel/FormStockViewModel.h>
#include <ViewModel/OrderListViewModel.h>
#include <ViewModel/FormCloseOrderViewModel.h>

namespace Ui {
    class FormMain;
}

class FormMainViewModel : public QWidget
{
    Q_OBJECT

public:
    FormMainViewModel(QWidget *parent = 0);
	
public slots:
	void resetModel();
	
private slots:
    void createOrder();
    void closeOrder();
	void editProducts();
	void editStock();
	
	void showDetails(QModelIndex index);

private:
    Ui::FormMain *ui;
    FormOrderViewModel *_orderView;
	EditProductsViewModel * _editProductsView;
    FormStockViewModel *_editStock;
	OrderListViewModel *_orderList;
	FormCloseOrderViewModel *_closeOrder;
};

#endif // FORMMAINVIEWMODEL_H
