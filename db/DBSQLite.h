#pragma once
#include "..\sqlite\include\sqlite3.h"
#include <winbase.h>
#include <vector>

typedef std::vector<std::string> SQLTransac;

class CDBSQLite{
public:
	static CDBSQLite& GetInstance();

	bool ExecuteSQL(const std::string& sSQL);
	bool IsExist(const std::string& sSQL);
	int GetIntField(const std::string& sSQL);
	std::string GetStringField(const std::string& sSQL);
	bool ExecuteTransac(const SQLTransac& vecSQL);

private:
	void InitConnection();

private:	
	CDBSQLite();
	CDBSQLite(const CDBSQLite& );
	~CDBSQLite();

	void operator=(const CDBSQLite&);

private:
	static sqlite3 *pDbconnection;
	static const char *pDbfilename;
	CRITICAL_SECTION m_cs;  

	char *m_pszErrMsg;
};