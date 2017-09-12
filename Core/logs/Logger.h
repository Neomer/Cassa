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
    explicit Logger(QObject *parent = 0);

signals:

public slots:
};


#define LOG_TRACE   qDebug() << "TRACE" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_DEBUG   qDebug() << "DEBUG" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_ERROR   qDebug() << "ERROR" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_INFO    qDebug() << "INFO " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")

#endif // LOGGER_H
