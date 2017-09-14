#ifndef ORDERNAME_H
#define ORDERNAME_H

#include <QObject>
#include <Core/IStorageModel.h>

class OrderName : public IStorageModel
{
	Q_OBJECT
	
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	
	QString m_name;

public:
	explicit OrderName();
	
	bool select();

	QString tableName() { return "[Order]"; }
	QString getName() const
	{
		return m_name;
	}
public slots:
	void setName(QString name)
	{
		if (m_name == name)
			return;
		
		m_name = name;
		emit nameChanged(name);
	}
signals:
	void nameChanged(QString name);
};

#endif // ORDERNAME_H
