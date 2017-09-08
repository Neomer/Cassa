#include "DatabaseConnection.h"
#include <QDir>

#include <Core/logs/Logger.h>
#include <Core/Context.h>

DatabaseConnection::DatabaseConnection(QObject *parent) :
    QObject(parent),
    _conn(0)
{
    LOG_TRACE;


}

bool DatabaseConnection::open(QString filename)
{
    LOG_TRACE << filename;

    LOG_DEBUG << "Открываем файл БД" << Context::instance().databaseDirectory().absoluteFilePath(filename);
    if (sqlite3_open(Context::instance().databaseDirectory().absoluteFilePath(filename).toUtf8().constData(),
                     &this->_conn) != SQLITE_OK)
    {
        LOG_ERROR << "Ошибка при открытии базы данных!";
        return false;
    }
    if (sqlite3_initialize() != SQLITE_OK)
    {
        LOG_ERROR << "Ошибка при инициализации базы данных!";
        return false;
    }
    return true;
}

void DatabaseConnection::close()
{
    if (this->_conn)
    {
        sqlite3_close(this->_conn);
    }
}

bool DatabaseConnection::exec(QString query, sqlite3_stmt **stmt)
{
    LOG_TRACE << query;

    int r = sqlite3_prepare_v2(this->_conn,
                            query.toStdString().data(),
                            query.toStdString().length(),
                            stmt,
                            NULL);
    LOG_TRACE << r << sqlite3_errstr(r);
    if (r != SQLITE_OK)
    {
        LOG_ERROR << "Ошибка при выполнении запроса!" << sqlite3_errstr(r);
        return false;
    }
    return true;
}

