#include "DatabaseQuery.h"
#include <Core/logs/Logger.h>
#include <Core/Context.h>

DatabaseQuery::DatabaseQuery(QObject *parent) :
    QObject(parent),
    _stmt(0)
{
    LOG_TRACE;
}

void DatabaseQuery::execute(QString query)
{
    LOG_TRACE << query;

    if (_stmt)
    {
        clear();
    }

    if (!Context::instance().defaultConnection()->exec(query, &_stmt))
    {
        throw std::runtime_error("Не удалось выполнить запрос!");
    }
    if (!next())
    {
        throw std::runtime_error("Не удалось выполнить запрос!");
    }
}

int DatabaseQuery::columnCount()
{
    return sqlite3_column_count(_stmt);
}

int DatabaseQuery::count()
{
    LOG_TRACE;
    throw std::runtime_error("Не поддерживается!");
}

bool DatabaseQuery::first()
{
    LOG_TRACE;
    throw std::runtime_error("Не поддерживается!");
}

bool DatabaseQuery::next()
{
    int res = sqlite3_step(_stmt);
    LOG_DEBUG << res;
    return res == SQLITE_ROW || res == SQLITE_DONE;
}

QVariant DatabaseQuery::value(int column)
{
    if (column > columnCount())
    {
        throw std::runtime_error("Выход за пределы диапазона!");
    }

    int type = sqlite3_column_type(_stmt, column);
    switch (type)
    {
        case  SQLITE_INTEGER:
            return QVariant::fromValue(sqlite3_column_int(_stmt, column));

        case SQLITE_FLOAT:
            return QVariant::fromValue(sqlite3_column_double(_stmt, column));

        case SQLITE_TEXT:
            return QVariant::fromValue(QString::fromUtf8((const char *)sqlite3_column_text(_stmt, column)));

        case SQLITE_BLOB:
            return QVariant();//QVariant::fromValue(sqlite3_column_blob(_stmt, column));

        case SQLITE_NULL:
            return QVariant();

        default:
            LOG_ERROR << "Неизвестный тип данных" << type;
            return QVariant();
    }
}

QVariant DatabaseQuery::value(QString column)
{
    const char *t = column.toUtf8().constData();

    for (int i = 0; i < columnCount(); i++)
    {
        if (!strcmp(sqlite3_column_name(_stmt, i), t))
        {
            return value(i);
        }
    }
    throw std::runtime_error("Колонки с заданным именем не найдено!");
}

int DatabaseQuery::hasColumn(QString name)
{
    LOG_TRACE << name;
    const char *t = name.toUtf8().constData();
    for (int i = 0; i < columnCount(); i++)
    {
        if (!strcmp(sqlite3_column_name(_stmt, i), t))
        {
            return i;
        }
    }
    return -1;
}

int DatabaseQuery::hasColumn(const char *name)
{
    LOG_TRACE << name;
    for (int i = 0; i < columnCount(); i++)
    {
        if (!strcmp(sqlite3_column_name(_stmt, i), name))
        {
            return i;
        }
    }
    return -1;

}

void DatabaseQuery::clear()
{
    LOG_TRACE;
    try
    {
        sqlite3_finalize(_stmt);
        _stmt = 0;
    }
    catch (...)
    {
        throw std::runtime_error("Не удалось очистить результат запроса!");
    }
}
