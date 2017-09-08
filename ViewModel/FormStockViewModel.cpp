#include "FormStockViewModel.h"
#include <ui_FormStock.h>

FormStockViewModel::FormStockViewModel(QWidget *parent) : 
	QWidget(parent),
	ui(new Ui::FormStock)
{
	ui->setupUi(this);
}

