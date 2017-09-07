#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>

#include <Core/IStorageByIdModel.h>
#include <Model/OrderDetails.h>

class Order : public IStorageByIdModel
{
    Q_OBJECT

    Q_PROPERTY(QDateTime creation_time READ getCreationTime WRITE setCreationTime NOTIFY creationTimeChanged)
    Q_PROPERTY(bool is_payed READ getIsPayed WRITE setIsPayed NOTIFY isPayedChanged)
    Q_PROPERTY(bool is_credited READ getIsCredited WRITE setIsCredited NOTIFY isCreditedChanged)
    Q_PROPERTY(QString buyer READ getBuyer WRITE setBuyer NOTIFY buyerChanged)

    QDateTime m_creation_time;
    bool m_is_payed;
    bool m_is_credited;
    QString m_buyer;

public:
    Order();
    QDateTime getCreationTime() const
    {
        return m_creation_time;
    }
    bool getIsPayed() const
    {
        return m_is_payed;
    }

    bool getIsCredited() const
    {
        return m_is_credited;
    }

    QString getBuyer() const
    {
        return m_buyer;
    }

    OrderDetails getOrderDetails();

public slots:
    void setCreationTime(QDateTime creation_time)
    {
        if (m_creation_time == creation_time)
            return;

        m_creation_time = creation_time;
        emit creationTimeChanged(m_creation_time);
    }
    void setIsPayed(bool is_payed)
    {
        if (m_is_payed == is_payed)
            return;

        m_is_payed = is_payed;
        emit isPayedChanged(m_is_payed);
    }

    void setIsCredited(bool is_credited)
    {
        if (m_is_credited == is_credited)
            return;

        m_is_credited = is_credited;
        emit isCreditedChanged(m_is_credited);
    }

    void setBuyer(QString buyer)
    {
        if (m_buyer == buyer)
            return;

        m_buyer = buyer;
        emit buyerChanged(m_buyer);
    }

signals:
    void creationTimeChanged(QDateTime creation_time);
    void isPayedChanged(bool is_payed);
    void isCreditedChanged(bool is_credited);
    void buyerChanged(QString buyer);

    // IStorageModel interface
public:
    QString tableName() { return "[Order]"; }
};

#endif // ORDER_H
