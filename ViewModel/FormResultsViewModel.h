#ifndef FORMRESULTSVIEWMODEL_H
#define FORMRESULTSVIEWMODEL_H

#include <QObject>
#include <QDialog>

#include <Core/ITableModel.h>

namespace Ui {
    class FormResults;
}

class FormResultsViewModel : public QDialog
{
	Q_OBJECT
public:
	explicit FormResultsViewModel(QWidget *parent = 0);
	~FormResultsViewModel();
	
private slots:
	void showDayResult();
	void showWeekResult();
	void showMonthResult();
	
private:
	void update();
	
	Ui::FormResults *ui;	
	ITableModel *_model;
};

#endif // FORMRESULTSVIEWMODEL_H
