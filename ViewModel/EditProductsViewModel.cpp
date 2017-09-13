#include "EditProductsViewModel.h"
#include <ui_FormEditProducts.h>

#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>

EditProductsViewModel::EditProductsViewModel(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::FormEditProducts)
{
	LOG_TRACE;
	
	ui->setupUi(this);
	
	_products = new ProductViewModel();
	
	connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(rowSelected(QModelIndex)));
	connect(ui->cmdCreate, SIGNAL(clicked(bool)), this, SLOT(createProduct()));
	connect(ui->cmdEdit, SIGNAL(clicked(bool)), this, SLOT(editProduct()));
	connect(ui->cmdRemove, SIGNAL(clicked(bool)), this, SLOT(removeProduct()));
}

EditProductsViewModel::~EditProductsViewModel()
{
	LOG_TRACE;
	delete _products;
}

void EditProductsViewModel::show()
{
	LOG_TRACE;
	update();
	QDialog::show();
}

void EditProductsViewModel::rowSelected(const QModelIndex &index)
{
	LOG_TRACE << index.row();
	
	if (index.isValid())
	{
		Product *p = _products->product();
		if (p->at(index.row()))
		{
			ui->txtName->setText(p->getName());
			ui->txtPrice->setText(QString::number(p->getPrice(), 'f', 2));
			ui->txtUnit->setText(p->getUnit());
			ui->chkIsWeight->setChecked(p->getIsWeight());
		}
		else
		{
			GuiUtils::showError("Продукт с заданным индексом не найден!");
		}
	}
}

void EditProductsViewModel::createProduct()
{
	LOG_TRACE;
	Product p;
	p.setName(ui->txtName->text());
	p.setUnit(ui->txtUnit->text());
	p.setIsWeight(ui->chkIsWeight->isChecked());

	bool ok = true;
	p.setPrice(ui->txtPrice->text().toDouble(&ok));
	
	if (!ok)
	{
		GuiUtils::showError("Ошибка в формате введенных данных!");
		return;
	}
	
	if (!p.insert())
	{
		LOG_ERROR << "Не удалось создать продукт!";
		GuiUtils::showError("Не удалось создать продукт!");
	}
	update();
}

void EditProductsViewModel::removeProduct()
{
	LOG_TRACE;
	_products->product()->at(ui->tableView->currentIndex().row());
	if (!_products->product()->remove())
	{
		GuiUtils::showError("Не удалось удалить продукт!");
	}
	update();
}

void EditProductsViewModel::update()
{
	LOG_TRACE;
	_products->getAll();
	ui->tableView->setModel(_products);
	ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void EditProductsViewModel::editProduct()
{
	LOG_TRACE;
	_products->product()->at(ui->tableView->currentIndex().row());
	Product p;
	p.setId(_products->product()->getId());
	p.setName(ui->txtName->text());
	p.setUnit(ui->txtUnit->text());
	p.setIsWeight(ui->chkIsWeight->isChecked());

	bool ok = true;
	p.setPrice(ui->txtPrice->text().toDouble(&ok));
	if (!ok)
	{
		GuiUtils::showError("Ошибка в формате введенных данных!");
		return;
	}
	if (!p.update())
	{
		GuiUtils::showError("Не удалось обновить информацию по товару!");
	}
	update();
}

