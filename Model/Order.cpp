#include "Order.h"
#include <Core/logs/Logger.h>

Order::Order() :
    IStorageByIdModel()
{

}

OrderDetails Order::getOrderDetails()
{
    LOG_TRACE;

    OrderDetails ret;

    Condition c;
    c["order_id"] = getId();

	return ret;
}

bool Order::selectOrderWithSumm(int orderId)
{
	LOG_TRACE << orderId;
	
	try {
		IStorageModel::execute("select o.*, sum(cost) as summ from [Order] o left join OrderDetails od on od.order_id = o.id where o.id=" + QString::number(orderId) + " group by o.id;");
		parseStatement();
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}
}

bool Order::selectOrdersWithSumm()
{
	LOG_TRACE;
	
	try {
		IStorageModel::execute("select o.*, sum(cost) as summ from [Order] o left join OrderDetails od on od.order_id = o.id group by o.id order by o.is_credited, o.is_payed, o.buyer;");
		parseStatement();
		
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}
}
