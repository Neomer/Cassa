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
