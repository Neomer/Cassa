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
	bool select(QStringList order = QStringList());
    bool update(Condition cond);
    bool insert();
	bool remove(Condition cond);
	bool remove();

	bool at(int index);
	bool next();
	bool first();
	
	bool execute(QString query, bool parseResult = true);
	
protected:
    void parseStatement();
    QString formatValue(QVariant value);
};

#endif // ISTORAGEMODEL_H
