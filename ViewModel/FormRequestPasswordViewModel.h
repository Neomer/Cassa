#ifndef FORMREQUESTPASSWORDVIEWMODEL_H
#define FORMREQUESTPASSWORDVIEWMODEL_H

#include <QObject>
#include <QDialog>

namespace Ui {
	class FormRequestPassword;
}

class FormRequestPasswordViewModel : public QDialog
{
	Q_OBJECT
public:
	explicit FormRequestPasswordViewModel(QWidget *parent = 0);
	QString password();
	
	int exec();
	
private:
	Ui::FormRequestPassword *ui;
	
};

#endif // FORMREQUESTPASSWORDVIEWMODEL_H
