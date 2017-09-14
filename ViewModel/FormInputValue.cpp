#include "FormInputValue.h"
#include <ui_FromInputValue.h>
#include <QKeyEvent>

FormInputValue::FormInputValue(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::FormInputValue)
{
	ui->setupUi(this);
	
	ui->txtValue->installEventFilter(this);
	
	connect(ui->cmdOK, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

QString FormInputValue::value()
{
	return ui->txtValue->text();
}

void FormInputValue::setCaption(QString text)
{
	ui->lblCaption->setText(text);
}

void FormInputValue::setValidator(QValidator *value)
{
	ui->txtValue->setValidator(value);
}

int FormInputValue::exec()
{
	ui->txtValue->clear();
	return QDialog::exec();
}



bool FormInputValue::eventFilter(QObject *watched, QEvent *event)
{
	Q_UNUSED(watched);
	
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		switch (keyEvent->key())
		{
			case Qt::Key_Return: case Qt::Key_Enter:
				accept();
				return true;
				
			case Qt::Key_Escape:
				reject();
				return true;
				
			default:
				return ui->txtValue->event(event);
		}
	}
	return ui->txtValue->event(event);
}
