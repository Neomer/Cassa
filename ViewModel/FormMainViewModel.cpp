#include "FormMainViewModel.h"
#include <ui_FormMain.h>
#include <QGraphicsScene>
#include <QImage>

#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>
#include <Core/Context.h>
#include <Model/Order.h>

FormMainViewModel::FormMainViewModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    LOG_TRACE;

    ui->setupUi(this);

    connect(ui->cmdAddOrder, SIGNAL(clicked(bool)), this, SLOT(createOrder()));
    connect(ui->cmdCloseOrder, SIGNAL(clicked(bool)), this, SLOT(closeOrder()));
	connect(ui->cmdProducts, SIGNAL(clicked(bool)), this ,SLOT(editProducts()));
	//connect(ui->cmdStock, SIGNAL(clicked(bool)), this, SLOT(editStock()));
	
	connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
	connect(ui->tableView, SIGNAL(entered(QModelIndex)), this, SLOT(showDetails(QModelIndex)));


    QDir dir(qApp->applicationDirPath());
    QPixmap pixmap(dir.absoluteFilePath("rocker.jpg"));
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);

    _orderView = new FormOrderViewModel();
	_editProductsView = new EditProductsViewModel();
    _editStock = new FormStockViewModel();
	_closeOrder = new FormCloseOrderViewModel();
	_orderList = new OrderListViewModel();
	
	this->setWindowState(Qt::WindowMaximized);
}

void FormMainViewModel::resetModel()
{
	LOG_TRACE;
	_orderList->loadAll();
	ui->tableView->setModel(_orderList);
	ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//ui->tableView->horizontalHeader()->set
	ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

void FormMainViewModel::createOrder()
{
    LOG_TRACE;

    Order o;
    o.setCreationTime(QDateTime::currentDateTime());
    o.setIsCredited(false);
    o.setIsPayed(false);
    o.setBuyer("");
    if (o.insert())
    {
        LOG_ERROR << "Новый заказ создан! ID" << o.getId();
    }
    else
    {
        LOG_ERROR << "Не далось создать заказ!";
        GuiUtils::showError("Не далось создать заказ!", this);
    }

    _orderView->loadOrder(o.getId());
    if (_orderView->exec() == QDialog::Accepted)
	{
		resetModel();
	}
}

void FormMainViewModel::closeOrder()
{
	LOG_TRACE;
	_orderList->order()->at(ui->tableView->currentIndex().row());
	_closeOrder->loadByOrderId(_orderList->order()->getId());
	if (_closeOrder->exec() == QDialog::Accepted)
	{
		resetModel();
	}
}

void FormMainViewModel::editProducts()
{
	LOG_TRACE;
	
	_editProductsView->show();
}

void FormMainViewModel::editStock()
{
	LOG_TRACE;

	_editStock->show();
}

void FormMainViewModel::showDetails(QModelIndex index)
{
	LOG_TRACE << index.row();
	_orderList->order()->at(index.row());
	_orderView->loadOrder(_orderList->order()->getId());
	if (_orderView->exec() == QDialog::Accepted)
	{
		resetModel();
	}
}
