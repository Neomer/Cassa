#ifndef ORDERDETAILS_H
#define ORDERDETAILS_H

#include <Core/IStorageModel.h>

class OrderDetails : public IStorageModel
{
    Q_OBJECT

    Q_PROPERTY(int order_id READ getOrderId WRITE setOrderId NOTIFY orderIdChanged STORED true)
    Q_PROPERTY(int product_id READ getProductId WRITE setProductId NOTIFY productIdChanged STORED true)
    Q_PROPERTY(double quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged STORED true)
    Q_PROPERTY(double cost READ getCost WRITE setCost NOTIFY costChanged STORED true)
	Q_PROPERTY(QString product_name READ getProductName WRITE setProductName NOTIFY productNameChanged STORED false)

    int m_order_id;
    int m_product_id;
    double m_quantity;
    double m_cost;
	QString m_productName;
	
public:
    OrderDetails();

    int getOrderId() const
    {
        return m_order_id;
    }
    int getProductId() const
    {
        return m_product_id;
    }

    double getQuantity() const
    {
        return m_quantity;
    }

    double getCost() const
    {
        return m_cost;
    }
	
	bool loadWithProductName(int orderId);
	
	bool select(int orderId, int productId);
	bool select(Condition c);
	
	bool update();
	bool update(Condition c);

    bool remove();
    bool remove(Condition c);

public slots:
    void setOrderId(int order_id)
    {
        if (m_order_id == order_id)
            return;

        m_order_id = order_id;
        emit orderIdChanged(m_order_id);
    }
    void setProductId(int product_id)
    {
        if (m_product_id == product_id)
            return;

        m_product_id = product_id;
        emit productIdChanged(m_product_id);
    }

    void setQuantity(double quantity)
    {
        if (qFuzzyCompare(m_quantity, quantity))
            return;

        m_quantity = quantity;
        emit quantityChanged(m_quantity);
    }

    void setCost(double cost)
    {
        if (qFuzzyCompare(m_cost, cost))
            return;

        m_cost = cost;
        emit costChanged(m_cost);
    }
	
	void setProductName(QString productName)
	{
		if (m_productName == productName)
			return;
		
		m_productName = productName;
		emit productNameChanged(productName);
	}
	
signals:
    void orderIdChanged(int order_id);
    void productIdChanged(int product_id);
    void quantityChanged(double quantity);
    void costChanged(double cost);

	// IStorageModel interface
	void productNameChanged(QString productName);
	
public:
QString tableName() { return "OrderDetails"; }
QString getProductName() const
{
	return m_productName;
}
};

#endif // ORDERDETAILS_H
