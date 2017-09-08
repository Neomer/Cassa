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
	bool select();
    bool update(Condition cond);
    bool insert();

	bool at(int index);
	bool next();
	bool first();
	
protected:
    void parseStatement();
    QString formatValue(QVariant value);
};

#endif // ISTORAGEMODEL_H
