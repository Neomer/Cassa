#ifndef FORMSTOCKVIEWMODEL_H
#define FORMSTOCKVIEWMODEL_H

#include <QWidget>

namespace Ui {
    class FormStock;
}



class FormStockViewModel : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormStockViewModel(QWidget *parent = 0);

private:
	Ui::FormStock *ui;
};

#endif // FORMSTOCKVIEWMODEL_H
