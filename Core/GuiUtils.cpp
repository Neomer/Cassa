#include "GuiUtils.h"
#include <QMessageBox>

GuiUtils::GuiUtils()
{

}

void GuiUtils::showError(QString text, QWidget *widget)
{
    QMessageBox::critical(widget, "Ошибка!", text);
}

void GuiUtils::showInformation(QString text, QWidget *widget)
{
    QMessageBox::information(widget, "Информация", text);
}

void GuiUtils::showWarning(QString text, QWidget *widget)
{
    QMessageBox::warning(widget, "Внимание!", text);
}
