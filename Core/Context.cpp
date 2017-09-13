#include "Context.h"
#include <Core/logs/Logger.h>
#include <QFile>
#include <QSettings>
#include <QCoreApplication>

bool Context::load(QString filename)
{
    LOG_TRACE << filename;

    QFile file(filename);
    if (!file.exists())
    {
        LOG_ERROR << "Файл конфигурации не найден!";
        return false;
    }

    _sets = new QSettings(filename, QSettings::IniFormat);

    QString tmp;
    //_sets->beginGroup("Cassa");
    tmp = _sets->value("Paths/DatabasePath", "").toString();
    if (tmp.isEmpty())
    {
        _databasePath.setPath(qApp->applicationDirPath());
    }
    else
    {
        _databasePath.setPath(tmp);
    }
	tmp = _sets->value("Security/Password", "").toString();
	if (tmp.isEmpty())
	{
		_pswHash = QCryptographicHash::hash(QString("Bober1234").toUtf8(), QCryptographicHash::Sha256);
	}
	else
	{
		_pswHash = QByteArray::fromHex(tmp.toUtf8());
	}
	//_sets->endGroup();

    _dbconn = new DatabaseConnection();
    if (!_dbconn->open("db.sqlite"))
    {
        throw std::runtime_error("Невозможно подключиться к базе данных!");
    }

	return true;
}

void Context::setDatabaseDirectory(QString value)
{
	LOG_TRACE << value;
	//_sets->beginGroup("Cassa");
	_sets->setValue("Paths/DatabasePath", value);
	//_sets->endGroup();
}

bool Context::checkPassword(QString value)
{
	LOG_TRACE << value;
	return QCryptographicHash::hash(value.toUtf8(), QCryptographicHash::Sha256) == _pswHash;
}

void Context::setPassword(QString value)
{
	LOG_TRACE;
	//_sets->beginGroup("Cassa");
	_sets->setValue("Security/Password", QString(QCryptographicHash::hash(value.toUtf8(), QCryptographicHash::Sha256).toHex()));
	//_sets->endGroup();
}

Context::Context()
{
    LOG_TRACE;
}

Context::~Context()
{
    LOG_TRACE;
    delete _dbconn;
}
