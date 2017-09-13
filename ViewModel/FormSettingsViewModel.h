#ifndef FORMSETTINGSVIEWMODEL_H
#define FORMSETTINGSVIEWMODEL_H

#include <QDialog>

namespace Ui {
	class FormSettings;
}

class FormSettingsViewModel : public QDialog
{
	Q_OBJECT
public:
	explicit FormSettingsViewModel(QWidget *parent = 0);
	int exec();
	
private slots:
	void save();

private:
	Ui::FormSettings *ui;	
};

#endif // FORMSETTINGSVIEWMODEL_H
