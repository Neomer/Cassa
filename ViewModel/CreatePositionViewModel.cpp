#include "CreatePositionViewModel.h"
#include <ui_FormOrderPosition.h>
#include <Core/logs/Logger.h>

CreatePositionViewModel::CreatePositionViewModel(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FormOrderPosition)
	
{
	LOG_TRACE;
	_products = new ProductViewModel();
	ui->setupUi(this);
}

void CreatePositionViewModel::show()
{
	LOG_TRACE;
	_products->getAll();
	ui->tv->setModel(_products);
	ui->tv->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	QDialog::show();
}

