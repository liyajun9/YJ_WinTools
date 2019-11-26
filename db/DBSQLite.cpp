#include "stdafx.h"
#include "DBSQLite.h"
#include "..\Log\YLog.h"
#include "..\exceptions\SQliteException.h"

sqlite3* CDBSQLite::pDbconnection = NULL;
const char* CDBSQLite::pDbfilename = "netbar.db";

CDBSQLite& CDBSQLite::GetInstance()
{
	static CDBSQLite dbSqliteInstance;
	return dbSqliteInstance;
}

CDBSQLite::CDBSQLite()
{
	InitializeCriticalSection(&m_cs);
}

CDBSQLite::~CDBSQLite()
{
	sqlite3_close(pDbconnection);
	DeleteCriticalSection(&m_cs);
}

bool CDBSQLite::ExecuteSQL(const std::string& sSQL)
{
	CYCriticalSectionLock(&m_cs, true);

	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", "DBSQLite.cpp", "ExecuteSQL");

		int nRet(0);
		if(nRet = sqlite3_exec(pDbconnection, sSQL.c_str(), NULL, NULL, &((char *)m_pszErrMsg)) != SQLITE_OK)
			throw CSQLiteException(m_pszErrMsg, "DBSQLite.cpp", "ExecuteSQL");

		return true;
	}catch(CSQLiteException& e){
		LOG_ERROR(e.what());
		sqlite3_free(m_pszErrMsg);
		return false;
	}
}

bool CDBSQLite::IsExist(const std::string& sSQL)
{
	return true;
}

int CDBSQLite::GetIntField(const std::string& sSQL)
{
	return 0;
}

std::string CDBSQLite::GetStringField(const std::string& sSQL)
{
	return std::string("");
}

bool CDBSQLite::ExecuteTransac(const SQLTransac& vecSQL)
{
	return true;
}

void CDBSQLite::InitConnection()
{
	if(!pDbconnection){
		if(SQLITE_OK != sqlite3_open_v2(pDbfilename, &pDbconnection, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL)){
			m_pszErrMsg = const_cast<char *>(sqlite3_errmsg(pDbconnection));
			LOG_ERROR("open sqlite error: %s", m_pszErrMsg);
		}
	}
}


