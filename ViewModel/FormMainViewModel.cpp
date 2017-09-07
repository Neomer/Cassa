#include "FormMainViewModel.h"
#include <ui_FormMain.h>

#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>
#include <Model/Order.h>

FormMainViewModel::FormMainViewModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    LOG_TRACE;

    ui->setupUi(this);

    connect(ui->cmdAddOrder, SIGNAL(clicked(bool)), this, SLOT(createOrder()));
    connect(ui->cmdCloseOrder, SIGNAL(clicked(bool)), this, SLOT(closeOrder()));

    _orderView = new FormOrderViewModel();
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
    _orderView->show();
}

void FormMainViewModel::closeOrder()
{
    LOG_TRACE;
}
