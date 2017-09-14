#ifndef FORMORDERVIEWMODEL_H
#define FORMORDERVIEWMODEL_H

#include <QWidget>
#include <ViewModel/orderitemviewmodel.h>
#include <ViewModel/OrderNameListViewModel.h>
#include <ViewModel/CreatePositionViewModel.h>

namespace Ui {
    class FormOrder;
}

class FormOrderViewModel : public QDialog
{
    Q_OBJECT

public:
    explicit FormOrderViewModel(QWidget *parent = 0);
	~FormOrderViewModel();

    void loadOrder(int orderId);
    void loadOrder();

private slots:
	void createPosition();
	void removePosition();
	void updateName(QString text);
	
private:
    Ui::FormOrder *ui;
    OrderItemViewModel *_orderItems;
	CreatePositionViewModel *_createPosition;
	Order *_order;
	OrderNameListViewModel *_orderNames;
	
	// QWidget interface
protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif // FORMORDERVIEWMODEL_H
