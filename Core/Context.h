#ifndef CONTEXT_H
#define CONTEXT_H

#include <QDir>
#include <QCryptographicHash>
#include <QSettings>

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
	void setDatabaseDirectory(QString value);
    DatabaseConnection *defaultConnection() { return _dbconn; }
	
	bool checkPassword(QString value);
	void setPassword(QString value);

private:
    Context();
    ~Context();
    Context(const Context&);
    void operator=(Context const&);

    QDir _databasePath;
    DatabaseConnection *_dbconn;
	QByteArray _pswHash;
	QSettings *_sets;
};



#endif // CONTEXT_H
