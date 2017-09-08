#include "FormOrderViewModel.h"
#include <ui_FormOrder.h>
#include <Core/logs/Logger.h>

FormOrderViewModel::FormOrderViewModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOrder)
{
    LOG_TRACE;

    ui->setupUi(this);

    _orderItems = new OrderItemViewModel(this);
	_createPosition = new CreatePositionViewModel();
	
	connect(ui->cmdAddPosition, SIGNAL(clicked(bool)), this, SLOT(createPosition()));
	connect(ui->cmdRemovePosition, SIGNAL(clicked(bool)), this, SLOT(removePosition()));
}

void FormOrderViewModel::loadOrder(int orderId)
{
    LOG_TRACE << orderId;

    Order o;
    if (!o.select(orderId))
    {
        throw std::runtime_error("Заказ с указанным ID не найден!");
    }
    loadOrder(o);
}

void FormOrderViewModel::loadOrder(Order order)
{
    LOG_TRACE << order.getId();

    _orderItems->getOrderItemsByOrderId(order.getId());

    ui->lblCreated->setText(order.getCreationTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lblID->setText(QString::number(order.getId()));
	ui->tv->setModel(_orderItems);
	ui->tv->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void FormOrderViewModel::createPosition()
{
	LOG_TRACE;
	_createPosition->show();
}

void FormOrderViewModel::removePosition()
{
	LOG_TRACE;
}
