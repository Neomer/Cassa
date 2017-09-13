#ifndef FORMMAINVIEWMODEL_H
#define FORMMAINVIEWMODEL_H

#include <QWidget>
#include <QGraphicsPixmapItem>

#include <ViewModel/FormOrderViewModel.h>
#include <ViewModel/EditProductsViewModel.h>
#include <ViewModel/FormStockViewModel.h>
#include <ViewModel/OrderListViewModel.h>
#include <ViewModel/FormCloseOrderViewModel.h>
#include <ViewModel/FormResultsViewModel.h>
#include <ViewModel/FormRequestPasswordViewModel.h>
#include <ViewModel/FormSettingsViewModel.h>

namespace Ui {
    class FormMain;
}

class FormMainViewModel : public QWidget
{
    Q_OBJECT

public:
    FormMainViewModel(QWidget *parent = 0);
	
public slots:
	void resetModel();
	
private slots:
    void createOrder();
    void closeOrder();
	void editProducts();
	void editStock();
	void showResults();
	void showSettings();
	
	void showDetails(QModelIndex index);

private:
    Ui::FormMain *ui;
    FormOrderViewModel *_orderView;
	EditProductsViewModel * _editProductsView;
    FormStockViewModel *_editStock;
	OrderListViewModel *_orderList;
	FormCloseOrderViewModel *_closeOrder;
	FormResultsViewModel *_resultView;
	FormRequestPasswordViewModel *_requestPasswordView;
	FormSettingsViewModel *_settingsView;
	
	void resizeEvent(QResizeEvent *e);
	
	QGraphicsPixmapItem *_pixItem;
	QPixmap _pixmap;
	
	// QObject interface
public:
	bool eventFilter(QObject *watched, QEvent *event);
	
	// QWidget interface
protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif // FORMMAINVIEWMODEL_H
