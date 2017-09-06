#include "Context.h"
#include <Core/logs/Logger.h>
#include <QFile>
#include <QSettings>
#include <QCoreApplication>

bool Context::load(QString filename)
{
    LOG_TRACE << filename;

    QFile file(filename);
    if (!file.exists())
    {
        LOG_ERROR << "Файл конфигурации не найден!";
        return false;
    }

//    if (!file.open())
//    {
//        LOG_ERROR << "Невозможно прочитать файл настроек!";
//        return false;
//    }

    QSettings set(filename, QSettings::IniFormat);

    QString tmp;
    set.beginGroup("Paths");
    tmp = set.value("DatabasePath", qApp->applicationDirPath()).toString();
    if (tmp.isEmpty())
    {
        _databasePath.setPath(qApp->applicationDirPath());
    }
    else
    {
        _databasePath.setPath(tmp);
    }

    _dbconn = new DatabaseConnection();
    if (!_dbconn->open("db.sqlite"))
    {
        throw std::runtime_error("Невозможно подключиться к базе данных!");
    }

    return true;
}

Context::Context()
{
    LOG_TRACE;
}

Context::~Context()
{
    LOG_TRACE;
    delete _dbconn;
}
