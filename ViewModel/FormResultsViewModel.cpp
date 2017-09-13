#include "FormResultsViewModel.h"
#include <ui_FormResults.h>
#include <Core/logs/Logger.h>
#include <Core/GuiUtils.h>

#include <ViewModel/DayResultViewModel.h>

FormResultsViewModel::FormResultsViewModel(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::FormResults)
{
	LOG_TRACE;
	ui->setupUi(this);
	_model = new DayResultViewModel();
	
	connect(ui->cmdDay, SIGNAL(clicked(bool)), this, SLOT(showDayResult()));
	connect(ui->cmdWeek, SIGNAL(clicked(bool)), this, SLOT(showWeekResult()));
	connect(ui->cmdMonth, SIGNAL(clicked(bool)), this, SLOT(showMonthResult()));
}

FormResultsViewModel::~FormResultsViewModel()
{
	delete _model;
}

void FormResultsViewModel::showDayResult()
{
	LOG_TRACE;
//	if (_model)
//	{
//		delete _model;
//	}
//	_model = new DayResultViewModel();
	((DayResultViewModel *)_model)->setDateFormat("yyyy-MM-dd");
	((DayResultViewModel *)_model)->loadByDay();
	update();
}

void FormResultsViewModel::showWeekResult()
{
	LOG_TRACE;
	((DayResultViewModel *)_model)->setDateFormat("MMM yyyy dd");
	((DayResultViewModel *)_model)->loadByWeek();
	update();
}

void FormResultsViewModel::showMonthResult()
{
	LOG_TRACE;
//	if (_model)
//	{
//		delete _model;
//	}
//	_model = new DayResultViewModel();
	((DayResultViewModel *)_model)->setDateFormat("MMM yyyy");
	((DayResultViewModel *)_model)->loadByMonth();
	update();
}

void FormResultsViewModel::update()
{
	LOG_TRACE;
	ui->tableView->setModel(_model);
	ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

