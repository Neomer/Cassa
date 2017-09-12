#ifndef FORMORDERVIEWMODEL_H
#define FORMORDERVIEWMODEL_H

#include <QWidget>
#include <ViewModel/orderitemviewmodel.h>
#include <ViewModel/CreatePositionViewModel.h>

namespace Ui {
    class FormOrder;
}

class FormOrderViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit FormOrderViewModel(QWidget *parent = 0);

    void loadOrder(int orderId);
    void loadOrder();

private slots:
	void createPosition();
	void removePosition();
	
private:
    Ui::FormOrder *ui;
    OrderItemViewModel *_orderItems;
	CreatePositionViewModel *_createPosition;
	Order *_order;
};

#endif // FORMORDERVIEWMODEL_H
