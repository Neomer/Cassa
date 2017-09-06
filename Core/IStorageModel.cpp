#include "IStorageModel.h"
#include <Core/logs/Logger.h>
#include <QMetaObject>
#include <QMetaProperty>

IStorageModel::IStorageModel()
{

}

bool IStorageModel::get(int id)
{
    LOG_TRACE << id;

    try
    {
        execute("select * from " + tableName() +
                "where id=" + QString::number(id));
        return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
        return false;
    }

}

bool IStorageModel::save()
{
    LOG_TRACE;

    const QMetaObject *mo = this->metaObject();
    for (int p = mo->propertyOffset(); p < mo->propertyCount(); ++p)
    {
        QMetaProperty prop = mo->property(p);
        int idx = hasColumn(prop.name());
        if (idx != -1)
        {
            prop.write(this, value(idx));
        }
    }

    try
    {
        execute("update " + tableName() +
                "set " +
                "where id=" + QString::number(id));
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
    for (int p = mo->propertyOffset(); p < mo->propertyCount(); ++p)
    {
        QMetaProperty prop = mo->property(p);
        int idx = hasColumn(prop.name());
        if (idx != -1)
        {
            prop.write(this, value(idx));
        }
    }
}
