#pragma once
#include <time.h>
#include <string>
#include "ttype.h"

namespace NS_Yutils{

	enum DATE_FORMAT{
		Date_Format_0,	//yyyy-mm-dd
		Date_Format_1,	//yy-mm-dd
		Date_Format_2,	//yyyymmdd
		Date_Format_3,	//yymmdd
		Date_Format_4,	//yyyy mm dd
		Date_Format_5,	//yy mm dd
		Date_Format_6,	//yyyy/mm/dd
		Date_Format_7,	//yy/mm/dd
		Date_Format_8,	//mm/dd/yyyy
		Date_Format_9,	//mm/dd/yy
		Date_Format_10,	//dd/mm/yyyy
		Date_Format_11	//dd/mm/yy
	};

	tstring GetCurrDate(DATE_FORMAT dformat = Date_Format_0);
	tstring GetCurrTime(bool bMilliSeconds = false);
	tstring GetCurrDateTime(DATE_FORMAT dformat = Date_Format_0, bool bMilliSeconds = false);
	tstring GetAddedDate(int nAddedDays, DATE_FORMAT dformat = Date_Format_0);
};