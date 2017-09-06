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

    if (sqlite3_open(Context::instance().databaseDirectory().absoluteFilePath(filename).toUtf8().constData(),
                     &this->_conn) != SQLITE_OK)
    {
        LOG_ERROR << "Ошибка при открытии базы данных!";
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

bool DatabaseConnection::exec(QString query, sqlite3_stmt *stmt)
{
    LOG_TRACE << query;

    if (sqlite3_prepare(this->_conn,
                        query.toUtf8().constData(),
                        query.length(),
                        &stmt,
                        NULL) != SQLITE_OK)
    {
        LOG_ERROR << "Ошибка при выполнении запроса!";
        return false;
    }
    return true;
}

