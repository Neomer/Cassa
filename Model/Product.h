#ifndef PRODUCT_H
#define PRODUCT_H

#include <Core/IStorageByIdModel.h>

class Product : public IStorageByIdModel
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString index_name READ getIndexName WRITE setIndexName NOTIFY nameIndexChanged)
    //Q_PROPERTY(double quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged)
    //Q_PROPERTY(double cost READ getCost WRITE setCost NOTIFY costChanged)

    QString m_name;
    double m_quantity;
    double m_cost;
	
	QString m_index_name;
	
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

	//    double getQuantity() const
//    {
//        return m_quantity;
//    }

//    double getCost() const
//    {
//        return m_cost;
//    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
		
		setIndexName(name.toUpper());
    }
//    void setQuantity(double quantity)
//    {
//        if (qFuzzyCompare(m_quantity, quantity))
//            return;

//        m_quantity = quantity;
//        emit quantityChanged(m_quantity);
//    }

//    void setCost(double cost)
//    {
//        if (qFuzzyCompare(m_cost, cost))
//            return;

//        m_cost = cost;
//        emit costChanged(m_cost);
//    }
	
	void setIndexName(QString index_name)
	{
		if (m_index_name == index_name)
			return;
		
		m_index_name = index_name;
		emit nameIndexChanged(index_name);
	}
	
signals:
    void nameChanged(QString name);
    void quantityChanged(double quantity);
    void costChanged(double cost);

	// IStorageModel interface
	void nameIndexChanged(QString index_name);
	
public:
QString tableName() { return "Product"; }
};

#endif // PRODUCT_H
