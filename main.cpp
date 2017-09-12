#include <QApplication>

#include <Core/Context.h>
#include <Core/logs/Logger.h>

#include <ViewModel/FormMainViewModel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        if (!Context::instance().load(QDir(a.applicationDirPath()).absoluteFilePath("Cassa.ini")))
		{
			return -1;
		}
    }
    catch (std::exception ex)
    {
        LOG_ERROR << "Ошибка при загрузке файла конфигурации!" << ex.what();
		return -1;
    }

    FormMainViewModel formMain;
    formMain.show();
	formMain.resetModel();

    return a.exec();
}
