#ifndef CONTEXT_H
#define CONTEXT_H

#include <QDir>
#include <Core/db/DatabaseConnection.h>

class Context
{
public:
    static Context &instance()
    {
        static Context i;
        return i;
    }

    bool load(QString filename);

    QDir databaseDirectory() { return _databasePath; }
    DatabaseConnection *defaultConnection() { return _dbconn; }

private:
    Context();
    ~Context();
    Context(const Context&);
    void operator=(Context const&);

    QDir _databasePath;
    DatabaseConnection *_dbconn;
};



#endif // CONTEXT_H
