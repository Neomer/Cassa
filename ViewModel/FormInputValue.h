#ifndef FORMINPUTVALUE_H
#define FORMINPUTVALUE_H

#include <QWidget>
#include <QDialog>
#include <QValidator>

namespace Ui {
	class FormInputValue;
}

class FormInputValue : public QDialog
{
	Q_OBJECT
public:
	explicit FormInputValue(QWidget *parent = 0);
	
	QString value();
	
	void setCaption(QString text);
	void setValidator(QValidator *value);
	
	int exec();
	
private:
	Ui::FormInputValue *ui;
	
	// QObject interface
public:
	bool eventFilter(QObject *watched, QEvent *event);
};

#endif // FORMINPUTVALUE_H
