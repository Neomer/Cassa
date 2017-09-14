#ifndef CREATEPOSITIONVIEWMODEL_H
#define CREATEPOSITIONVIEWMODEL_H

#include <QWidget>
#include <QDialog>

#include <ViewModel/ProductViewModel.h>
#include <ViewModel/FormInputValue.h>

namespace Ui {
    class FormOrderPosition;
}

class CreatePositionViewModel : public QDialog
{
	Q_OBJECT
	
public:
	CreatePositionViewModel(QWidget *parent = 0);
	
	DialogCode show(int orderId);
	
private slots:
	void createPosition();
	void indexChanged();
	
private:
	Ui::FormOrderPosition *ui;
	
	ProductViewModel *_products;
	int _orderId;
	FormInputValue *_inputValueView;
	
protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif // CREATEPOSITIONVIEWMODEL_H
