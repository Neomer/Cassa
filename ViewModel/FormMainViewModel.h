#ifndef FORMMAINVIEWMODEL_H
#define FORMMAINVIEWMODEL_H

#include <QWidget>
#include <ViewModel/FormOrderViewModel.h>
#include <ViewModel/EditProductsViewModel.h>

namespace Ui {
    class FormMain;
}

class FormMainViewModel : public QWidget
{
    Q_OBJECT

public:
    FormMainViewModel(QWidget *parent = 0);

private slots:
    void createOrder();
    void closeOrder();
	void editProducts();
	void editStock();

private:
    Ui::FormMain *ui;
    FormOrderViewModel *_orderView;
	EditProductsViewModel * _editProductsView;
};

#endif // FORMMAINVIEWMODEL_H
