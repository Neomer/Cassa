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
	
	void show();
	
private:
	Ui::FormOrderPosition *ui;
	
	ProductViewModel *_products;
};

#endif // CREATEPOSITIONVIEWMODEL_H
