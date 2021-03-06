#include "IStorageModel.h"
#include <Core/logs/Logger.h>
#include <QMetaObject>
#include <QMetaProperty>

IStorageModel::IStorageModel() :
    DatabaseQuery()
{
    LOG_TRACE;
}

IStorageModel::IStorageModel(const IStorageModel &other) :
    DatabaseQuery()
{
    LOG_TRACE;

    const QMetaObject *mo = this->metaObject();
    const QMetaObject *moOther = other.metaObject();
    while (mo)
    {
        for (int p = mo->propertyOffset(); p < mo->propertyCount() - 1; ++p)
        {
            QMetaProperty prop = mo->property(p);
            QMetaProperty propOther = moOther->property(p);
            if (prop.isWritable() && prop.isReadable())
            {
                prop.write(this, propOther.read(&other));
            }
        }
        mo = mo->superClass();
        moOther = moOther->superClass();
    }

}

bool IStorageModel::select(Condition cond)
{
    LOG_TRACE << cond.count();
    QString filters;
    QStringList keys = cond.keys();

    foreach (QString k, keys)
    {
        filters += QString("`%1`=%2 and ").arg(
                    k,
                    formatValue(cond[k]));
    }
    filters = filters.left(filters.length() - 4);

    try
    {
        DatabaseQuery::execute(" select * from " + tableName() +
                " where " + filters);

        parseStatement();
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageModel::select(QStringList order)
{
	LOG_TRACE;
	
	QString sOrd;
	if (order.count() > 0)
	{
		sOrd = " order by " + order.join(',');
	}
	
	try
    {
        DatabaseQuery::execute("select * from " + tableName() + sOrd + ";");

        parseStatement();
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageModel::update(Condition cond)
{
    LOG_TRACE << cond.count();

    QString values;

    const QMetaObject *mo = this->metaObject();
    for (int p = mo->propertyOffset(); p < mo->propertyCount() - 1; ++p)
    {
        QMetaProperty prop = mo->property(p);
		if (prop.isStored(this))
		{
			values += QString("`%1`=%2, ").arg(
						prop.name(),
						formatValue(prop.read(this)));
		}
	}
	if (mo->property(mo->propertyCount() - 1).isStored(this))
	{
		values += QString("`%1`=%2").arg(
					mo->property(mo->propertyCount() - 1).name(),
					formatValue(mo->property(mo->propertyCount() - 1).read(this)));
	}
	else
	{
		values = values.left(values.length() - 2);
	}

    QString filters;
    QStringList keys = cond.keys();

    foreach (QString k, keys)
    {
        filters += QString("`%1`=%2 and ").arg(
                    k,
                    formatValue(cond[k]));
    }
    filters = filters.left(filters.length() - 4);

    try
    {
        DatabaseQuery::execute(" update " + tableName() +
                " set " + values +
                " where " + filters);

        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
    }

}

bool IStorageModel::insert()
{
    LOG_TRACE;

    QString fields;
    QString values;
    const QMetaObject *mo = this->metaObject();
    for (int p = mo->propertyOffset(); p < mo->propertyCount(); ++p)
    {
        QMetaProperty prop = mo->property(p);
		LOG_TRACE << prop.name() << prop.isStored(this);
        if (strcmp(prop.name(), "id") && prop.isStored(this))
        {
            fields += "`" + QString(prop.name()) + "`,";
            values += formatValue(prop.read(this)) + ",";
        }
    }
	fields = fields.left(fields.count() - 1);
	values = values.left(values.count() - 1);

    try
    {
        DatabaseQuery::execute(" insert into " + tableName() +
                " (" + fields + ") "
                " values (" + values + ");");
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
    }

    try
    {
        DatabaseQuery::execute("select last_insert_rowid() from " + tableName() + ";");
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
    }

    Condition c;
    c["ROWID"] = value(0);
	return select(c);
}

bool IStorageModel::remove(Condition cond)
{
	LOG_TRACE << cond.count();
    QString filters;
    QStringList keys = cond.keys();

    foreach (QString k, keys)
    {
        filters += QString("`%1`=%2 and ").arg(
                    k,
                    formatValue(cond[k]));
    }
    filters = filters.left(filters.length() - 4);

    try
    {
        DatabaseQuery::execute(" delete from " + tableName() +
                " where " + filters);

        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageModel::remove()
{
	LOG_TRACE;
	
	try
    {
        DatabaseQuery::execute("delete from " + tableName() + ";");

        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageModel::at(int index)
{
	bool ret = DatabaseQuery::at(index);
	if (ret)
	{
		parseStatement();
	}
	return ret;
}

bool IStorageModel::next()
{
	bool ret = DatabaseQuery::next();
	if (ret)
	{
		parseStatement();
	}
	return ret;
}

bool IStorageModel::first()
{
	bool ret = DatabaseQuery::first();
	if (ret)
	{
		parseStatement();
	}
	return ret;
}

bool IStorageModel::execute(QString query, bool parseResult)
{
	LOG_TRACE << query;
	
	try
    {
        DatabaseQuery::execute(query);
		if (parseResult)
		{
			parseStatement();
		}
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

void IStorageModel::parseStatement()
{
    LOG_TRACE;

    const QMetaObject *mo = this->metaObject();
    while (mo)
    {
        for (int p = mo->propertyOffset(); p < mo->propertyCount(); ++p)
        {
            QMetaProperty prop = mo->property(p);

            if (!strcmp(prop.name(), "objectName"))
                continue;

            int idx = hasColumn(prop.name());
            if (idx != -1)
            {
                prop.write(this, value(idx));
            }
        }
        mo = mo->superClass();
    }
}

QString IStorageModel::formatValue(QVariant value)
{
    switch (value.type())
    {
        case QVariant::String: 
			return QString("'%1'").arg(value.toString()).toUtf8().constData();
		
		case QVariant::Bool:
            return "'" + value.toString() + "'";

        case QVariant::DateTime:
            return "'" + value.toDateTime().toString("yyyy-MM-dd hh:mm:ss") + "'";

        case QVariant::Date:
            return "'" + value.toDateTime().toString("yyyy-MM-dd") + "'";

        case QVariant::Time:
            return "'" + value.toDateTime().toString("hh:mm:ss") + "'";

        default:
            return value.toString();
    }
}
