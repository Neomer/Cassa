#ifndef FORMORDERVIEWMODEL_H
#define FORMORDERVIEWMODEL_H

#include <QWidget>
#include <ViewModel/orderitemviewmodel.h>

namespace Ui {
    class FormOrder;
}

class FormOrderViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit FormOrderViewModel(QWidget *parent = nullptr);

    void loadOrder(int orderId);
    void loadOrder(Order order);

private:
    Ui::FormOrder *ui;
    OrderItemViewModel *_orderItems;
};

#endif // FORMORDERVIEWMODEL_H
