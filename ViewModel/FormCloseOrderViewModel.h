#ifndef FORMCLOSEORDERVIEWMODEL_H
#define FORMCLOSEORDERVIEWMODEL_H

#include <QDialog>
#include <Model/Order.h>

namespace Ui {
    class FormCloseOrder;
}

class FormCloseOrderViewModel : public QDialog
{
	Q_OBJECT
	
public:
	FormCloseOrderViewModel(QWidget *parent = 0);
	~FormCloseOrderViewModel();
	
	void loadByOrderId(int orderId);
	
private slots:
	void closeOrder();
	void closeCredit();
	
private:
	Order *o;
	Ui::FormCloseOrder *ui;
};

#endif // FORMCLOSEORDERVIEWMODEL_H
