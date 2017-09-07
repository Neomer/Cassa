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

bool IStorageByIdModel::update()
{
    LOG_TRACE;

    QString values;

    const QMetaObject *mo = this->metaObject();
    for (int p = mo->propertyOffset(); p < mo->propertyCount() - 1; ++p)
    {
        QMetaProperty prop = mo->property(p);
        values += QString("`%1`=%2, ").arg(
                    prop.name(),
                    formatValue(prop.read(this)));
    }
    values += QString("`%1`=%2").arg(
                mo->property(mo->propertyCount() - 1).name(),
                formatValue(mo->property(mo->propertyCount() - 1).read(this)));

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

