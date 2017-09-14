#include "OrderName.h"
#include <Core/logs/Logger.h>

OrderName::OrderName() : IStorageModel()
{
	LOG_TRACE;
}

bool OrderName::select()
{
	LOG_TRACE;
	
	try {
		execute("select buyer as name from [Order] group by buyer order by buyer asc;");
		parseStatement();
		return true;
	}
	catch (std::exception &ex)
	{
		LOG_ERROR << ex.what();
		return false;
	}
}

