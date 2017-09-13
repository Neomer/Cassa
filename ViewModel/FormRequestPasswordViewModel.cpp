#include "FormRequestPasswordViewModel.h"
#include <ui_FormPasswordRequest.h>
#include <Core/logs/Logger.h>

FormRequestPasswordViewModel::FormRequestPasswordViewModel(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::FormRequestPassword)
{
	LOG_TRACE;
	ui->setupUi(this);
	ui->txtPassword->setEchoMode(QLineEdit::Password);
	
	connect(ui->cmdOK, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

QString FormRequestPasswordViewModel::password()
{
	LOG_TRACE;
	return ui->txtPassword->text();
}

int FormRequestPasswordViewModel::exec()
{
	ui->txtPassword->clear();
	
	return QDialog::exec();
}

