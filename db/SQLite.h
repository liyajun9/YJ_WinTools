#pragma once
#include "..\sqlite\include\sqlite3.h"
#include <winbase.h>
#include <vector>
#include "ttype.h"

#define SQLITE_QUERY_SUCCESS 0
#define SQLITE_QUERY_ERROR 1
typedef std::vector<tstring> TransactSQLs;

#define SQLite YSQLite::GetInstance()

class YSQLite{
public:
	static YSQLite& GetInstance();

	bool GetIsExist(const tstring& sSQL);
	int GetIntField(const tstring& sSQL);//return -1 on error or empty result
	tstring GetStringField(const tstring& sSQL); //return "" on error or empty result

	bool ExecuteSQL(const tstring& sSQL, unsigned int *pAffectedRows = NULL);
	bool ExecuteTransac(const TransactSQLs& vecSQL);

	bool GetIsTableExist(const tstring& sTable);
	bool GetIsColumnExist(const tstring& sTable, const tstring&sCol);//note: column name is sensitive

	int GetLastError();//0(SQLITE_QUERY_SUCCESS) or 1(SQLITE_QUERY_ERROR)

private:
	void InitConnection();

private:	
	YSQLite();
	YSQLite(const YSQLite& );
	virtual ~YSQLite();

	void operator=(const YSQLite&);

private:
	static sqlite3 *pDbconnection;
	static const char *pDbfilename;
	CRITICAL_SECTION m_cs;  

	int m_nLastError; //0 - success    other-error
};