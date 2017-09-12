#ifndef STOCK_H
#define STOCK_H

#include <Core/IStorageByIdModel.h>

class Stock : public IStorageByIdModel
{
	Q_OBJECT
	
	Q_PROPERTY(int product_id READ getProductId WRITE setProductId NOTIFY productIdChanged STORED true)
	Q_PROPERTY(double quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged STORED true)
	Q_PROPERTY(double price READ getPrice WRITE setPrice NOTIFY priceChanged STORED true)
	Q_PROPERTY(bool isSold READ getIsSold WRITE setIsSold NOTIFY isSoldChanged STORED true)
	
	int m_product_id;
	double m_quantity;
	double m_price;
	int m_isSold;
	
public:
	Stock();

	QString tableName() { return "Stock"; }
	
	int getProductId() const
	{
		return m_product_id;
	}
	double getQuantity() const
	{
		return m_quantity;
	}
	
	double getPrice() const
	{
		return m_price;
	}
	
	int getIsSold() const
	{
		return m_isSold;
	}
	
public slots:
	void setProductId(int product_id)
	{
		if (m_product_id == product_id)
			return;

		m_product_id = product_id;
		emit productIdChanged(product_id);
	}
	void setQuantity(double quantity)
	{
		if (m_quantity == quantity)
			return;
		
		m_quantity = quantity;
		emit quantityChanged(quantity);
	}
	
	void setPrice(double price)
	{
		if (m_price == price)
			return;
		
		m_price = price;
		emit priceChanged(price);
	}
	
	void setIsSold(	int isSold)
	{
		if (m_isSold == isSold)
			return;
		
		m_isSold = isSold;
		emit isSoldChanged(isSold);
	}
	
signals:
	void productIdChanged(int product_id);
	void quantityChanged(double quantity);
	void priceChanged(double price);
	void isSoldChanged(	int isSold);
};

#endif // STOCK_H
