#ifndef FORMSTOCKVIEWMODEL_H
#define FORMSTOCKVIEWMODEL_H

#include <QWidget>
#include <ViewModel/StockViewModel.h>

namespace Ui {
    class FormStock;
}

class FormStockViewModel : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormStockViewModel(QWidget *parent = 0);
    ~FormStockViewModel();

    void show();
    void update();

private:
	Ui::FormStock *ui;
    StockViewModel *_model;
};

#endif // FORMSTOCKVIEWMODEL_H
