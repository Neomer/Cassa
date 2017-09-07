#ifndef FORMMAINVIEWMODEL_H
#define FORMMAINVIEWMODEL_H

#include <QWidget>
#include <ViewModel/FormOrderViewModel.h>

namespace Ui {
    class FormMain;
}

class FormMainViewModel : public QWidget
{
    Q_OBJECT

public:
    FormMainViewModel(QWidget *parent = 0);

private slots:
    void createOrder();
    void closeOrder();

private:
    Ui::FormMain *ui;
    FormOrderViewModel *_orderView;
};

#endif // FORMMAINVIEWMODEL_H
