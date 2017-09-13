#include "FormSettingsViewModel.h"
#include <ui_FromSettings.h>

#include <Core/logs/Logger.h>
#include <Core/Context.h>
#include <Core/GuiUtils.h>

FormSettingsViewModel::FormSettingsViewModel(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::FormSettings)
{
	LOG_TRACE;
	
	ui->setupUi(this);

	ui->LineEditPassword->setEchoMode(QLineEdit::Password);
	
	connect(ui->cmdSave, SIGNAL(clicked(bool)), this, SLOT(save()));
	connect(ui->cmdCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

int FormSettingsViewModel::exec()
{
	ui->LineEditDatabase->setText(Context::instance().databaseDirectory().absolutePath());
	ui->LineEditPassword->clear();
	
	return QDialog::exec();
}

void FormSettingsViewModel::save()
{
	LOG_TRACE;
	
	if (ui->LineEditPassword->text().isEmpty() ||
			ui->LineEditDatabase->text().isEmpty())
	{
		GuiUtils::showError("Заполните все поля!");
		return;
	}
	
	Context::instance().setPassword(ui->LineEditPassword->text());
	Context::instance().setDatabaseDirectory(ui->LineEditDatabase->text());
	
	Context::instance().load(QDir(qApp->applicationDirPath()).absoluteFilePath("Cassa.ini"));
	
	accept();
}

