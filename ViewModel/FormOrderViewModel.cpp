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
	_order = new Order();
	
	connect(ui->cmdAddPosition, SIGNAL(clicked(bool)), this, SLOT(createPosition()));
	connect(ui->cmdRemovePosition, SIGNAL(clicked(bool)), this, SLOT(removePosition()));
}

void FormOrderViewModel::loadOrder(int orderId)
{
    LOG_TRACE << orderId;

    if (!_order->select(orderId))
    {
        throw std::runtime_error("Заказ с указанным ID не найден!");
    }
    loadOrder();
}

void FormOrderViewModel::loadOrder()
{
    LOG_TRACE << _order->getId();

    _orderItems->getOrderItemsByOrderId(_order->getId());

    ui->lblCreated->setText(_order->getCreationTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lblID->setText(QString::number(_order->getId()));
	ui->tv->setModel(_orderItems);
	ui->tv->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

void FormOrderViewModel::createPosition()
{
	LOG_TRACE;
	
	_createPosition->show(_order->getId());
	loadOrder();
}

void FormOrderViewModel::removePosition()
{
	LOG_TRACE;
}
