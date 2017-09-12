#include "OrderDetails.h"
#include <Core/logs/Logger.h>

OrderDetails::OrderDetails() :
    IStorageModel()
{
	LOG_TRACE;
}

bool OrderDetails::loadWithProductName(int orderId)
{
	LOG_TRACE << orderId;
	
	try
    {
		IStorageModel::execute(" select od.*, p.name as product_name from OrderDetails od left join Product p on p.id=od.product_id  where order_id=" + QString::number(orderId) + " order by p.name;");
        IStorageModel::parseStatement();
		return true;
    }
    catch (std::exception ex)
    {
        LOG_ERROR << ex.what();
		return false;
	}
}

bool OrderDetails::select(int orderId, int productId)
{
	LOG_TRACE;
	
	Condition c;
	c["order_id"] = orderId;
	c["product_id"] = productId;
	return IStorageModel::select(c);
}

bool OrderDetails::select(Condition c)
{
	LOG_TRACE;
	return IStorageModel::select(c);
}

bool OrderDetails::update()
{
	LOG_TRACE;
	
	Condition c;
	c["order_id"] = getOrderId();
	c["product_id"] = getProductId();
	
	return IStorageModel::update(c);
}

bool OrderDetails::update(Condition c)
{
	LOG_TRACE;
    return IStorageModel::update(c);
}

bool OrderDetails::remove()
{
    LOG_TRACE;

    Condition c;
    c["order_id"] = getOrderId();
    c["product_id"] = getProductId();

    return IStorageModel::remove(c);
}

bool OrderDetails::remove(Condition c)
{
    LOG_TRACE;
    return IStorageModel::remove(c);
}
