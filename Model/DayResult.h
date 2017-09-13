#ifndef DAYRESULT_H
#define DAYRESULT_H

#include <QObject>
#include <Core/IStorageModel.h>
#include <QDateTime>

class DayResult : public IStorageModel
{
	Q_OBJECT
	
	Q_PROPERTY(QDateTime creation_time READ getCreationTime WRITE setCreationTime)
	Q_PROPERTY(int payment READ getPayment WRITE setPayment)
	Q_PROPERTY(int count READ getCount WRITE setCount)
	Q_PROPERTY(double summ READ getSumm WRITE setSumm)
	
	QDateTime m_creation_time;
	int m_payment;
	int m_count;
	double m_summ;

public:
	explicit DayResult(QObject *parent = 0);
	
	bool selectLastDay();
	bool selectLastWeek();
	bool selectLastMonth();
	
	QString tableName() { return ""; }
	QDateTime getCreationTime() const
	{
		return m_creation_time;
	}
	int getPayment() const
	{
		return m_payment;
	}
	
	int getCount() const
	{
		return m_count;
	}
	
	double getSumm() const
	{
		return m_summ;
	}
	
public slots:
	void setCreationTime(QDateTime creation_time)
	{
		m_creation_time = creation_time;
	}
	void setPayment(int payment)
	{
		m_payment = payment;
	}
	void setCount(int count)
	{
		m_count = count;
	}
	void setSumm(double summ)
	{
		m_summ = summ;
	}
};

#endif // DAYRESULT_H
