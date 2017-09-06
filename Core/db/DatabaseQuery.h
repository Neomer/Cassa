#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QObject>
#include <sqlite3.h>

class DatabaseQuery : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseQuery(QObject *parent = nullptr);

    void execute(QString query);

    int columnCount();
    int count();

    bool first();
    bool next();

    QVariant value(int column);
    QVariant value(QString column);

    int hasColumn(QString name);
    int hasColumn(const char *name);

    void clear();

private:
    sqlite3_stmt *_stmt;
};

#endif // DATABASEQUERY_H
