#include <QApplication>

#include <Core/Context.h>
#include <Core/logs/Logger.h>

#include <ViewModel/FormMainViewModel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        Context::instance().load(QDir(a.applicationDirPath()).absoluteFilePath("Cassa.ini"));
    }
    catch (std::exception ex)
    {
        LOG_ERROR << "Ошибка при загрузке файла конфигурации!" << ex.what();
    }

    FormMainViewModel formMain;
    formMain.show();

    return a.exec();
}
