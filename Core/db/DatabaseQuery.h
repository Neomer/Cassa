#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QObject>
#include <sqlite3.h>

class DatabaseQuery : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseQuery(QObject *parent = 0);

    void execute(QString query);

    int columnCount();
    int count();

    bool first();
    bool next(bool *hasRows = 0);
    bool at(int index);

    bool eof();

    QVariant value(int column);
    QVariant value(QString column);

    int hasColumn(QString name);
    int hasColumn(const char *name);

    void clear();

private:
    sqlite3_stmt *_stmt;
    int _rows, _columns;
    int _currentRow;
    bool _eof;
};

#endif // DATABASEQUERY_H
