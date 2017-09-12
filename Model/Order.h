#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>

#include <Core/IStorageByIdModel.h>
#include <Model/OrderDetails.h>

class Order : public IStorageByIdModel
{
    Q_OBJECT

    Q_PROPERTY(QDateTime creation_time READ getCreationTime WRITE setCreationTime NOTIFY creationTimeChanged STORED true)
    Q_PROPERTY(bool is_payed READ getIsPayed WRITE setIsPayed NOTIFY isPayedChanged STORED true)
    Q_PROPERTY(bool is_credited READ getIsCredited WRITE setIsCredited NOTIFY isCreditedChanged STORED true)
    Q_PROPERTY(QString buyer READ getBuyer WRITE setBuyer NOTIFY buyerChanged STORED true)
	Q_PROPERTY(double summ READ getSumm WRITE getSumm NOTIFY summChanged STORED false)
	Q_PROPERTY(int payment READ getPaymentType WRITE setPaymentType NOTIFY paymentTypeChanged)
	Q_PROPERTY(QString comment READ getComment WRITE setComment NOTIFY commentChanged)

    QDateTime m_creation_time;
    bool m_is_payed;
    bool m_is_credited;
    QString m_buyer;
	double m_summ;
	int m_payment;
	QString m_comment;
	
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
	
	QString tableName() { return "[Order]"; }
	double getSumm() const
	{
		return m_summ;
	}
	
	bool selectOrderWithSumm(int orderId);
	bool selectOrdersWithSumm();
	
	int getPaymentType() const
	{
		return m_payment;
	}
	
	QString getComment() const
	{
		return m_comment;
	}
	
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
	
	void getSumm(double summ)
	{
		if (m_summ == summ)
			return;
		
		m_summ = summ;
		emit summChanged(summ);
	}
	
	void setPaymentType(int payment)
	{
		if (m_payment == payment)
			return;
		
		m_payment = payment;
		emit paymentTypeChanged(payment);
	}
	
	void setComment(QString comment)
	{
		if (m_comment == comment)
			return;
		
		m_comment = comment;
		emit commentChanged(comment);
	}
	
signals:
    void creationTimeChanged(QDateTime creation_time);
    void isPayedChanged(bool is_payed);
    void isCreditedChanged(bool is_credited);
    void buyerChanged(QString buyer);
	void summChanged(double summ);
	void paymentTypeChanged(int payment);
	void commentChanged(QString comment);
};

#endif // ORDER_H
