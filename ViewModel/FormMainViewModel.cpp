#include "FormMainViewModel.h"
#include <ui_FormMain.h>
#include <QGraphicsScene>
#include <QImage>
#include <QResizeEvent>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QKeyEvent>

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

	QMenuBar *menu = new QMenuBar(this);
	QList<QAction *> al;
	QAction *actSettings = new QAction("Н&астройки");
	al << actSettings;
	
	menu->addActions(al);
	ui->widget = menu;
	((QVBoxLayout *) this->layout())->insertWidget(0, menu);
	
    connect(ui->cmdAddOrder, SIGNAL(clicked(bool)), this, SLOT(createOrder()));
    connect(ui->cmdCloseOrder, SIGNAL(clicked(bool)), this, SLOT(closeOrder()));
	connect(ui->cmdProducts, SIGNAL(clicked(bool)), this ,SLOT(editProducts()));
	//connect(ui->cmdStock, SIGNAL(clicked(bool)), this, SLOT(editStock()));
	connect(ui->cmdResults, SIGNAL(clicked(bool)), this, SLOT(showResults()));
	connect(actSettings, SIGNAL(triggered(bool)), this, SLOT(showSettings()));	
	
	connect(ui->tableView, SIGNAL(activated(QModelIndex)), this, SLOT(showDetails(QModelIndex)));

	QDir dir(qApp->applicationDirPath());
    if (!_pixmap.load(dir.absoluteFilePath("circle.png")))
	{
		LOG_ERROR << "Не далось загрузить изображение!";
	}
    QGraphicsScene *scene = new QGraphicsScene(this);
	int sz = qMin(ui->graphicsView->width(), ui->graphicsView->height());
    _pixItem = scene->addPixmap(_pixmap.scaled(sz, sz, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
			
    _orderView = new FormOrderViewModel();
	_editProductsView = new EditProductsViewModel();
    _editStock = new FormStockViewModel();
	_closeOrder = new FormCloseOrderViewModel();
	_orderList = new OrderListViewModel();
	_resultView = new FormResultsViewModel();
	_requestPasswordView = new FormRequestPasswordViewModel(this);
	_settingsView = new FormSettingsViewModel(this);
	
	ui->tableView->installEventFilter(this);
	
	//this->setWindowState(Qt::WindowMaximized);
}

void FormMainViewModel::resetModel()
{
	LOG_TRACE;
	_orderList->loadAll();
	ui->tableView->setModel(_orderList);
	if (_orderList->order()->count() > 0)
	{
		ui->tableView->selectRow(0);
	}
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
    int res = _orderView->exec();
	if (o.getOrderDetails().count() == 0)
	{
		if (!o.remove())
		{
			GuiUtils::showError("Не удалось записать в базу данных!");
		}
	}
	if (res == QDialog::Accepted)
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
	
	if (_requestPasswordView->exec() == QDialog::Rejected)
		return;
	
	if (Context::instance().checkPassword(_requestPasswordView->password()))
	{
		_editProductsView->show();
	}
	else
	{
		GuiUtils::showError("Сказано же тебе - ИДИ НАХУЙ!");
	}
}

void FormMainViewModel::editStock()
{
	LOG_TRACE;
	
	if (_requestPasswordView->exec() == QDialog::Rejected)
		return;
	

	if (Context::instance().checkPassword(_requestPasswordView->password()))
	{
	}
	else
	{
		GuiUtils::showError("Сказано же тебе - ИДИ НАХУЙ!");
	}
}

void FormMainViewModel::showResults()
{
	LOG_TRACE;
	
	if (_requestPasswordView->exec() == QDialog::Rejected)
		return;
	
	if (Context::instance().checkPassword(_requestPasswordView->password()))
	{
		_resultView->exec();
	}
	else
	{
		GuiUtils::showError("Сказано же тебе - ИДИ НАХУЙ!");
	}
}

void FormMainViewModel::showSettings()
{
	LOG_TRACE;
	if (_requestPasswordView->exec() == QDialog::Rejected)
		return;
	
	if (Context::instance().checkPassword(_requestPasswordView->password()))
	{
		_settingsView->exec();
	}
	else
	{
		GuiUtils::showError("Сказано же тебе - ИДИ НАХУЙ!");
	}
}

void FormMainViewModel::showDetails(QModelIndex index)
{
	LOG_TRACE << index.row();
	Order *o = _orderList->order();
	o->at(index.row());
	_orderView->loadOrder(o->getId());
	int res = _orderView->exec();
	o->at(index.row());
	OrderDetails od = o->getOrderDetails();
	if (od.count() == 0)
	{
		if (!o->remove())
		{
			GuiUtils::showError("Не удалось записать в базу данных!");
		}
		resetModel();
	}
	else if (res == QDialog::Accepted)
	{
		resetModel();
	}
}

void FormMainViewModel::resizeEvent(QResizeEvent *e)
{
	
	int sz = qMin(ui->graphicsView->width(), ui->graphicsView->height());
	LOG_TRACE << sz;
    _pixItem->setPixmap(_pixmap.scaled(sz, sz, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	_pixItem->setPos(0, 0);
	ui->graphicsView->setAlignment(Qt::AlignCenter);
	e->accept();
	ui->graphicsView->update();
	ui->graphicsView->ensureVisible(ui->graphicsView->scene()->itemsBoundingRect(), 0, 0);
}


bool FormMainViewModel::eventFilter(QObject *watched, QEvent *event)
{
	Q_UNUSED(watched);
	if (event->type() == QEvent::KeyPress)
	{
		LOG_TRACE << "key pressed";
		QKeyEvent * keyEvent = static_cast<QKeyEvent *>(event);
		keyPressEvent(keyEvent);
		if (!event->isAccepted())
		{
			return false;
		}
		return true;
	}
	event->accept();
	return false;
}


void FormMainViewModel::keyPressEvent(QKeyEvent *event)
{
 	switch (event->key())
	{
		case Qt::Key_Space: case Qt::Key_F5:
			createOrder();
			event->accept();
			break;
			
		case Qt::Key_F9:
			closeOrder();
			event->accept();
			break;
			
		case Qt::Key_Up: case Qt::Key_Down:
			event->setAccepted(false);
			break;
		
		default:
			QWidget::keyPressEvent(event);
	}
}
