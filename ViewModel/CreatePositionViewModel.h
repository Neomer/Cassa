#ifndef CREATEPOSITIONVIEWMODEL_H
#define CREATEPOSITIONVIEWMODEL_H

#include <QWidget>
#include <QDialog>

#include <ViewModel/ProductViewModel.h>

namespace Ui {
    class FormOrderPosition;
}

class CreatePositionViewModel : public QDialog
{
	Q_OBJECT
	
public:
	CreatePositionViewModel(QWidget *parent = 0);
	
	void show(int orderId);
	
private slots:
	void createPosition();
	
private:
	Ui::FormOrderPosition *ui;
	
	ProductViewModel *_products;
	int _orderId;
};

#endif // CREATEPOSITIONVIEWMODEL_H
