#ifndef ISTORAGEBYIDMODEL_H
#define ISTORAGEBYIDMODEL_H

#include <Core/IStorageModel.h>

class IStorageByIdModel : public IStorageModel
{
    Q_OBJECT

    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)

public:
    IStorageByIdModel();

    bool select(int id);
    bool update();


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
    int m_id;
};

#endif // ISTORAGEBYIDMODEL_H
