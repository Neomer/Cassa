#ifndef FORMMAINVIEWMODEL_H
#define FORMMAINVIEWMODEL_H

#include <QWidget>
#include <ui_FormMain.h>

class FormMainViewModel : public QWidget
{
    Q_OBJECT

public:
    FormMainViewModel(QWidget *parent = 0);

private slots:
    void createOrder();
    void closeOrder();

private:
    Ui::Form *ui;
};

#endif // FORMMAINVIEWMODEL_H
