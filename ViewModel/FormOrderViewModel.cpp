#include <QKeyEvent>
#include "FormOrderViewModel.h"
#include <ui_FormOrder.h>
#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>
#include <QCompleter>

FormOrderViewModel::FormOrderViewModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormOrder)
{
    LOG_TRACE;

    ui->setupUi(this);

    _orderItems = new OrderItemViewModel(this);
	_createPosition = new CreatePositionViewModel();
	_orderNames = new OrderNameListViewModel();
	_order = new Order();
	
	connect(ui->cmdAddPosition, SIGNAL(clicked(bool)), this, SLOT(createPosition()));
	connect(ui->cmdRemovePosition, SIGNAL(clicked(bool)), this, SLOT(removePosition()));
	connect(ui->txtName, SIGNAL(textChanged(QString)), this, SLOT(updateName(QString)));
	connect(ui->cmdCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
	
	QCompleter *comp = new QCompleter(_orderNames);
	comp->setCaseSensitivity(Qt::CaseInsensitive);
	comp->setCompletionMode(QCompleter::PopupCompletion);
	comp->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	ui->txtName->setCompleter(comp);
}

FormOrderViewModel::~FormOrderViewModel()
{
	delete _order;
	delete _orderNames;
	delete _createPosition;
	delete _orderItems;
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
    Order o;
    if (!o.selectOrderWithSumm(_order->getId()))
    {
        GuiUtils::showError("Ошибка при запросе к базе данных!");
    }
    else
    {
        ui->lblSumm->setText(QString::number(o.getSumm(), 'f', 2));
    }

    ui->lblCreated->setText(_order->getCreationTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lblID->setText(QString::number(_order->getId()));
	ui->txtName->setText(_order->getBuyer());
	ui->tv->setModel(_orderItems);
	ui->tv->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	
	ui->cmdAddPosition->setEnabled(!(_order->getIsPayed()||_order->getIsCredited()));
	ui->cmdRemovePosition->setEnabled(!(_order->getIsPayed()||_order->getIsCredited()));
}

void FormOrderViewModel::createPosition()
{
	LOG_TRACE;
	
	if (_order->getIsCredited() || _order->getIsPayed())
	{
		return;
	}
	
	if (_createPosition->show(_order->getId()) == QDialog::Accepted)
	{
		loadOrder();
	}
}

void FormOrderViewModel::removePosition()
{
	LOG_TRACE;
	if (_order->getIsCredited() || _order->getIsPayed())
	{
		return;
	}
    _orderItems->items()->at(ui->tv->currentIndex().row());
    if (!_orderItems->items()->remove())
    {
        GuiUtils::showError("Ошибка при записи в базу данных!");
    }
    loadOrder();
}

void FormOrderViewModel::updateName(QString text)
{
	LOG_TRACE;
	if (_order->getIsCredited() || _order->getIsPayed())
	{
		return;
	}
	if (_order->getBuyer() != text)
	{
		_order->setBuyer(text);
		if (!_order->update())
		{
			GuiUtils::showError("Ошибка при записи в базу данных!");
		}
	}
}


void FormOrderViewModel::keyPressEvent(QKeyEvent *event)
{
	LOG_TRACE;
	switch (event->key()) 
	{
		case Qt::Key_F5:
			createPosition();
			break;
		
		case Qt::Key_F8:
			removePosition();
			break;
			
		case Qt::Key_Escape:
			reject();
			break;
		
		default:
			QDialog::keyPressEvent(event);
			return;
	}
	event->accept();
}
