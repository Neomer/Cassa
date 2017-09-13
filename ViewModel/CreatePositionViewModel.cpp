#include "CreatePositionViewModel.h"
#include <ui_FormOrderPosition.h>
#include <QKeyEvent>

#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>
#include <Model/OrderDetails.h>

CreatePositionViewModel::CreatePositionViewModel(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FormOrderPosition)
	
{
	LOG_TRACE;
	_products = new ProductViewModel();
	
	ui->setupUi(this);
	
	connect(ui->tv, SIGNAL(clicked(QModelIndex)), this, SLOT(indexChanged()));
	
	connect(ui->cmdSelect, SIGNAL(clicked(bool)), this, SLOT(createPosition()));
	connect(ui->cmdCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

QDialog::DialogCode CreatePositionViewModel::show(int orderId)
{
	LOG_TRACE;
	_orderId = orderId;
	
    ui->txtQuantity->setText("0");

	_products->getAll();
	ui->tv->setModel(_products);
	ui->tv->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	return (QDialog::DialogCode) QDialog::exec();
}

void CreatePositionViewModel::createPosition()
{
	LOG_TRACE;
	
	_products->product()->at(ui->tv->currentIndex().row());
	
	bool ok;
	double quantity = ui->txtQuantity->text().toDouble(&ok);
	if (!ok)
	{
		GuiUtils::showError("Ошибка в формате введенных данных!");
		return;
	}
	if (_products->product()->getIsWeight())
	{
		if (quantity <= 0)
		{
			GuiUtils::showError("Весовой товар! Укажите количество!");
			return;
		}
	}
	else
	{
		if (quantity == 0)
		{
			quantity = 1;
		}
		else if (quantity < 0)
		{
			GuiUtils::showError("Неверное количество!");
			return;
		}
	}
	
	
	OrderDetails od;
	if (!od.select(_orderId, _products->product()->getId()))
	{
		GuiUtils::showError("Ошибка при запросе к базе данных!");
		return;
	}
	
	if (od.count() > 0)
	{
		od.setQuantity(od.getQuantity() + quantity);
		od.setCost(od.getCost() + quantity * _products->product()->getPrice());
		if (!od.update())
		{
			GuiUtils::showError("Не удалось добавить позицию!");
		}
	}
	else
	{
		od.setOrderId(_orderId);
		od.setProductId(_products->product()->getId());
		od.setQuantity(quantity);
		od.setCost(quantity * _products->product()->getPrice());
		if (!od.insert())
		{
			GuiUtils::showError("Не удалось добавить позицию!");
		}
	}
	QDialog::accept();
}

void CreatePositionViewModel::indexChanged()
{
	LOG_TRACE;
	_products->product()->at(ui->tv->currentIndex().row());
	ui->lblUnit->setText(_products->product()->getUnit());
}

void CreatePositionViewModel::keyPressEvent(QKeyEvent *event)
{
	LOG_TRACE << event->key();
	
	switch (event->key())
	{
		case Qt::Key_Enter: case Qt::Key_Return:
			createPosition();
			break;
			
		case Qt::Key_F5:
			ui->txtQuantity->setFocus();
			ui->txtQuantity->setSelection(0, ui->txtQuantity->text().length());
			break;
			
		default:
			QDialog::keyPressEvent(event);
	}
}


