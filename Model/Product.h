#ifndef PRODUCT_H
#define PRODUCT_H

#include <Core/IStorageByIdModel.h>

class Product : public IStorageByIdModel
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged STORED true)
	Q_PROPERTY(QString index_name READ getIndexName WRITE setIndexName NOTIFY nameIndexChanged STORED true)
    Q_PROPERTY(double price READ getPrice WRITE setPrice NOTIFY costPrice STORED true)
	Q_PROPERTY(QString unit READ getUnit WRITE setUnit NOTIFY unitChanged)
	Q_PROPERTY(bool is_weight READ getIsWeight WRITE setIsWeight NOTIFY isWeightChanged)

    QString m_name;
	QString m_index_name;
	double m_price;
	QString m_unit;
	bool m_is_weight;
	 
public:
    Product();
    QString getName() const
    {
        return m_name;
    }
	QString getIndexName() const
	{
		return m_index_name;
	}
	double getPrice() const
	{
		return m_price;
	}
	QString tableName() { return "Product"; }
	
	QString getUnit() const
	{
		return m_unit;
	}
	
	bool getIsWeight() const
	{
		return m_is_weight;
	}
	
public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
		
		setIndexName(name.toUpper());
    }

	void setIndexName(QString index_name)
	{
		if (m_index_name == index_name)
			return;
		
		m_index_name = index_name;
		emit nameIndexChanged(index_name);
	}
	
	void setPrice(double price)
	{
		if (m_price == price)
			return;
		m_price = price;
		emit costPrice(price);
	}
	
	void setUnit(QString unit)
	{
		if (m_unit == unit)
			return;
		
		m_unit = unit;
		emit unitChanged(unit);
	}
	
	void setIsWeight(bool is_weight)
	{
		if (m_is_weight == is_weight)
			return;
		
		m_is_weight = is_weight;
		emit isWeightChanged(is_weight);
	}
	
signals:
    void nameChanged(QString name);
	void nameIndexChanged(QString index_name);
	void costPrice(double price);
	
	void unitChanged(QString unit);
	void isWeightChanged(bool is_weight);
};

#endif // PRODUCT_H
