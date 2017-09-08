#include "DatabaseQuery.h"
#include <Core/logs/Logger.h>
#include <Core/Context.h>

DatabaseQuery::DatabaseQuery(QObject *parent) :
    QObject(parent),
    _stmt(0),
    _rows(0),
    _columns(0),
    _currentRow(-1),
    _eof(true)
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
	_eof = false;
    bool hasRows = false;
    if (!next(&hasRows))
    {
        throw std::runtime_error("Не удалось выполнить запрос!");
    }
    _columns = sqlite3_column_count(_stmt);
    if (hasRows)
    {
        _rows = 1;
        while (!eof())
        {
			next();
            if (!eof())
            {
				_rows++;
			}
        }
        first();
    }
}

int DatabaseQuery::columnCount()
{
    return _columns;
}

int DatabaseQuery::count()
{
    LOG_TRACE;
    return _rows;
}

bool DatabaseQuery::first()
{
    LOG_TRACE;
    if (sqlite3_reset(_stmt) != SQLITE_OK)
    {
        throw std::runtime_error("Не удалось сбросить запрос!");
    }
    next();
    _currentRow = 0;
    return true;
}


bool DatabaseQuery::next(bool *hasRows)
{
    int res = sqlite3_step(_stmt);
    LOG_DEBUG << res;

    if (hasRows)
    {
        *hasRows = res == SQLITE_ROW;
    }
    if (res == SQLITE_ROW)
    {
        _currentRow++;
    }
    else if (res == SQLITE_DONE)
    {
        _eof = true;
    }
    return res == SQLITE_ROW || res == SQLITE_DONE;
}

bool DatabaseQuery::at(int index)
{
    LOG_TRACE << index;

    if (index >= _rows)
    {
        return false;
    }

    int start = _currentRow;
    if (index < start)
    {
        start = 0;
        first();
    }
    for (int i = 0; i < index - start; i++)
    {
        next();
    }

    return true;
}

bool DatabaseQuery::eof()
{
    if (!_stmt)
        return true;
    return _eof;
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
        _rows = 0;
        _columns = 0;
        _eof = true;
        sqlite3_finalize(_stmt);
        _stmt = 0;
    }
    catch (...)
    {
        throw std::runtime_error("Не удалось очистить результат запроса!");
    }
}
