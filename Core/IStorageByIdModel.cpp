#include "IStorageByIdModel.h"
#include <Core/logs/Logger.h>
#include <QMetaObject>
#include <QMetaProperty>

IStorageByIdModel::IStorageByIdModel() :
    IStorageModel()
{

}

bool IStorageByIdModel::select(int id)
{
    LOG_TRACE << id;

    try
    {
        execute(" select * from " + tableName() +
                " where id=" + QString::number(id));
        parseStatement();
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageByIdModel::select(QStringList order)
{
	return IStorageModel::select(order);
}

bool IStorageByIdModel::update()
{
    LOG_TRACE;

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
		
    try
    {
        execute(" update " + tableName() +
                " set " + values +
                " where id=" + QString::number(getId()));
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}
}

bool IStorageByIdModel::remove(int id)
{
	LOG_TRACE << id;

    try
    {
        execute(" delete from " + tableName() +
                " where id=" + QString::number(id));
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}

}

bool IStorageByIdModel::remove()
{
	LOG_TRACE;

    try
    {
        execute(" delete from " + tableName() +
                " where id=" + QString::number(getId()));
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
	}

}


