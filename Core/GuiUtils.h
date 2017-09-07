#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QWidget>

class GuiUtils
{
public:
    GuiUtils();

    static void showError(QString text, QWidget *widget = 0);
    static void showInformation(QString text, QWidget *widget = 0);
    static void showWarning(QString text, QWidget *widget = 0);
};

#endif // GUIUTILS_H
