#pragma once
#include <time.h>
#include <string>

class CYTimeUtils{
public:
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

public:
	static std::string GetCurrDate(DATE_FORMAT dformat = Date_Format_0);
	static std::string GetCurrTime(bool bMilliSeconds = false);
	static std::string GetCurrDateTime(DATE_FORMAT dformat = Date_Format_0, bool bMilliSeconds = false);
	static std::string GetAddedDate(int nAddedDays, DATE_FORMAT dformat = Date_Format_0);
};