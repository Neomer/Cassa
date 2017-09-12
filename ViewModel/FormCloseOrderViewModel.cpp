#include "FormCloseOrderViewModel.h"
#include <ui_FormCloseOrder.h>
#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>

FormCloseOrderViewModel::FormCloseOrderViewModel(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FormCloseOrder)
{
	LOG_TRACE;
	
	ui->setupUi(this);
	o = new Order();
	
	connect(ui->cmdApply, SIGNAL(clicked(bool)), this, SLOT(closeOrder()));
	connect(ui->cmdCredit, SIGNAL(clicked(bool)), this, SLOT(closeCredit()));
	connect(ui->cmdCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

FormCloseOrderViewModel::~FormCloseOrderViewModel()
{
	LOG_TRACE;
	delete o;
}

void FormCloseOrderViewModel::loadByOrderId(int orderId)
{
	LOG_TRACE << orderId;
	
	if (!o->selectOrderWithSumm(orderId))
	{
		GuiUtils::showError("Не удалось загрузить заказ!");
		reject();
		return;
	}
	ui->lblSumm->setText(QString::number(o->getSumm(), 'f', 2));
}

void FormCloseOrderViewModel::closeOrder()
{
	LOG_TRACE;

	int payType = 0;
	if (ui->rdCash->isChecked()) payType = 1;
	if (ui->rdCard->isChecked()) payType = 2;
	
	if (!payType)
	{
		GuiUtils::showError("Выберите способ оплаты!");
		return;
	}
	
	o->setIsPayed(true);
	o->setIsCredited(false);
	o->setPaymentType(payType);
	o->setComment(ui->txtComment->toPlainText());
	if (!o->update())
	{
		GuiUtils::showError("Не удалось записать изменения в базу данных!");
		reject();
		return;
	}
	accept();
}

void FormCloseOrderViewModel::closeCredit()
{
	LOG_TRACE;
	
}

