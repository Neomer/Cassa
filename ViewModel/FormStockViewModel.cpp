#include "FormStockViewModel.h"
#include <ui_FormStock.h>
#include <Core/logs/Logger.h>

FormStockViewModel::FormStockViewModel(QWidget *parent) : 
	QWidget(parent),
	ui(new Ui::FormStock)
{
    LOG_TRACE;

	ui->setupUi(this);

    _model = new StockViewModel();
}

FormStockViewModel::~FormStockViewModel()
{
    LOG_TRACE;
    delete _model;
}

void FormStockViewModel::show()
{
    LOG_TRACE;
    update();
    QWidget::show();
}

void FormStockViewModel::update()
{
    LOG_TRACE;
    _model->load();
    ui->tableView->setModel(_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

