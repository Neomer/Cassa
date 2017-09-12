#include "CreatePositionViewModel.h"
#include <ui_FormOrderPosition.h>
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
	
	connect(ui->cmdSelect, SIGNAL(clicked(bool)), this, SLOT(createPosition()));
	connect(ui->cmdCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void CreatePositionViewModel::show(int orderId)
{
	LOG_TRACE;
	_orderId = orderId;
	
	_products->getAll();
	ui->tv->setModel(_products);
	ui->tv->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	QDialog::exec();
}

void CreatePositionViewModel::createPosition()
{
	LOG_TRACE;
	
	_products->product()->at(ui->tv->currentIndex().row());
	
	OrderDetails od;
	if (!od.select(_orderId, _products->product()->getId()))
	{
		GuiUtils::showError("Ошибка при запросе к базе данных!");
		return;
	}
	
	if (od.count() > 0)
	{
		bool ok = true;
		od.setQuantity(od.getQuantity() + ui->txtQuantity->text().toDouble(&ok));
		if (!ok)
		{
			GuiUtils::showError("Ошибка в формате введенных данных!");
			return;
		}
		od.setCost(od.getCost() + ui->txtQuantity->text().toDouble() * _products->product()->getPrice());
		if (!od.update())
		{
			GuiUtils::showError("Не удалось добавить позицию!");
		}
	}
	else
	{
		od.setOrderId(_orderId);
		od.setProductId(_products->product()->getId());
		bool ok = true;
		od.setQuantity(ui->txtQuantity->text().toDouble(&ok));
		if (!ok)
		{
			GuiUtils::showError("Ошибка в формате введенных данных!");
			return;
		}
		od.setCost(ui->txtQuantity->text().toDouble() * _products->product()->getPrice());
		if (!od.insert())
		{
			GuiUtils::showError("Не удалось добавить позицию!");
		}
	}
	QDialog::accept();
}


