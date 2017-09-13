#include "DayResult.h"
#include <Core/logs/Logger.h>

DayResult::DayResult(QObject *parent) : 
	IStorageModel()
{
	Q_UNUSED(parent);
	LOG_TRACE;
	
}

bool DayResult::selectLastDay()
{
	LOG_TRACE;
	
	try {
		execute(
					QString("select ") +
					"	creation_time, " +
					"	payment, " +
					"	count(id) as count, " +
					"	sum(summ) as summ " +
					"from ( " +
					"select  " +
					"	o.*, sum(od.cost) as summ  " +
					"from [Order] o  " +
					"left join OrderDetails od on od.order_id=o.id  " +
					"where o.is_payed='true' " +
					"group by o.id) " +
					"group by  " +
					"strftime('%Y-%m-%d', date(creation_time)), " +
					"payment " +
					"order by " +
					"creation_time desc,  " +
					"payment asc;"
		);
		parseStatement();
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}
}

bool DayResult::selectLastWeek()
{
	LOG_TRACE;
	
	try {
		execute(
					QString("select ") +
					"	creation_time, " +
					"	payment, " +
					"	count(id) as count, " +
					"	sum(summ) as summ " +
					"from ( " +
					"select  " +
					"	o.*, sum(od.cost) as summ  " +
					"from [Order] o  " +
					"left join OrderDetails od on od.order_id=o.id  " +
					"where o.is_payed='true' " +
					"group by o.id) " +
					"group by  " +
					"strftime('%W', date(creation_time)), " +
					"payment " +
					"order by " +
					"creation_time desc,  " +
					"payment asc;"
		);
		parseStatement();
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}
}

bool DayResult::selectLastMonth()
{
	LOG_TRACE;
	
	try {
		execute(
					QString("select ") +
					"	creation_time, " +
						"payment,  " +
						"count(id) as count,  " +
						"sum(summ) as summ  " +
					" from (  " +
					" select   " +
					"	o.*, sum(od.cost) as summ   " +
					" from [Order] o   " +
					" left join OrderDetails od on od.order_id=o.id   " +
					" where o.is_payed='true'  " +
					"	and creation_time >= date('now','start of month', '-1 month')  " +
					"	and creation_time < date('now','start of month', '+1 month')  " +
					" group by o.id)  " +
					" group by   " +
					" strftime('%Y-%m', date(creation_time)),  " +
					" payment " +
					" order by " +
					" creation_time desc,  " +
					" payment asc;"
		);
		parseStatement();
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}

}
/*
select
	creation_time,
	count(id) as count,
	sum(summ) as summ
from (
select 
	o.*, sum(od.cost) as summ 
from [Order] o 
left join OrderDetails od on od.order_id=o.id 
where o.is_payed='true'
group by o.id)
group by date(creation_time, '%d')
*/
