#ifndef ISTORAGEMODEL_H
#define ISTORAGEMODEL_H

#include <Core/db/DatabaseQuery.h>

class IStorageModel : public DatabaseQuery
{
    Q_OBJECT

    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)

public:
    IStorageModel();

    bool get(int id);

    virtual QString tableName() = 0;

    int getId() const
    {
        return m_id;
    }

public slots:
    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

signals:
    void idChanged(int id);

private:
    void parseStatement();
    int m_id;
};

#endif // ISTORAGEMODEL_H
