#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

#define nullptr		0


class Logger : public QObject
{
    Q_OBJECT
public:
	static Logger instance()
    {
        static Logger i;
        return i;
    }
	
	Logger operator << (QString value) { Q_UNUSED(value); return *this; }
	Logger operator << (const char *value) { Q_UNUSED(value); return *this; }
	Logger operator << (int value) { Q_UNUSED(value); return *this; }
	Logger operator << (double value) { Q_UNUSED(value); return *this; }
	

	Logger();
    ~Logger();
	Logger(const Logger&) : QObject() {}
    void operator=(Logger const&);
	
};


#define LOG_TRACE   Logger::instance() << "TRACE" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_DEBUG   qDebug() << "DEBUG" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_ERROR   qDebug() << "ERROR" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_INFO    qDebug() << "INFO " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")

#endif // LOGGER_H
