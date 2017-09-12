#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QObject>
#include <sqlite3.h>

#define nullptr		0

class DatabaseConnection : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseConnection(QObject *parent = 0);

    bool open(QString filename);
    void close();
    bool exec(QString query, sqlite3_stmt **stmt);

private:
    sqlite3 *_conn;
};

#endif // DATABASECONNECTION_H
