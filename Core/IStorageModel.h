#ifndef ISTORAGEMODEL_H
#define ISTORAGEMODEL_H

#include <QObject>
#include <Core/db/DatabaseQuery.h>

typedef QMap<QString, QVariant>     Condition;

class IStorageModel : public DatabaseQuery
{
    Q_OBJECT

public:
    IStorageModel();
    IStorageModel(const IStorageModel &other);

    virtual QString tableName() = 0;

    bool select(Condition cond);
    bool update(Condition cond);
    bool insert();

protected:
    void parseStatement();
    QString formatValue(QVariant value);
};

#endif // ISTORAGEMODEL_H
