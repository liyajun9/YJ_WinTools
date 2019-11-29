#include "stdafx.h"
#include "DBSQLite.h"
#include "..\Log\YLog.h"
#include "..\exceptions\SQliteException.h"
#include <sstream>

sqlite3* CDBSQLite::pDbconnection = NULL;
const char* CDBSQLite::pDbfilename = "netbar.db";

CDBSQLite& CDBSQLite::GetInstance()
{
	static CDBSQLite dbSqliteInstance;
	return dbSqliteInstance;
}

CDBSQLite::CDBSQLite() : m_nLastError(0)
{
	InitializeCriticalSection(&m_cs);
}

CDBSQLite::~CDBSQLite()
{
	sqlite3_close(pDbconnection);
	DeleteCriticalSection(&m_cs);
}

bool CDBSQLite::ExecuteSQL(const std::string& sSQL, unsigned int *pAffectedRows)
{
	CYCriticalSectionLock(&m_cs, true);
	char *pszErrMsg = NULL;
	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", sSQL.c_str(), "ExecuteSQL");

		int nRes(0);
		if(nRes = sqlite3_exec(pDbconnection, sSQL.c_str(), NULL, NULL, &pszErrMsg) != SQLITE_OK)
			throw CSQLiteException(pszErrMsg, sSQL.c_str(), "ExecuteSQL");

		if(pAffectedRows)
			*pAffectedRows = sqlite3_changes(pDbconnection);

		m_nLastError = SQLITE_QUERY_SUCCESS;
	}catch(CSQLiteException& e){
		LOG_ERROR(e.what());
		sqlite3_free(pszErrMsg);
		m_nLastError = SQLITE_QUERY_ERROR;
		return false;
	}

	if(pszErrMsg)		sqlite3_free(pszErrMsg);	
	return true;
}

bool CDBSQLite::GetIsExist(const std::string& sSQL)
{
	CYCriticalSectionLock(&m_cs, true);
	sqlite3_stmt *stmt = NULL;
	char *pszErrMsg = NULL;
	bool bRet(false);

	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", sSQL.c_str(), "GetIntField");

		int nRes(0);
		if(nRes = sqlite3_prepare_v2(pDbconnection, sSQL.c_str(), -1, &stmt, NULL) != SQLITE_OK)
			throw CSQLiteException("prepare statement error", sSQL.c_str(), "GetIntField");

		if(nRes = sqlite3_step(stmt) == SQLITE_ROW){
			bRet = true;
		}else if(nRes == SQLITE_DONE || nRes == SQLITE_OK){
			bRet = false;
		}else{
			std::stringstream ssErr;
			ssErr<<"step statement error("<<nRes<<")";
			throw CSQLiteException(ssErr.str().c_str(), sSQL.c_str(), "GetIntField");
		}
		m_nLastError = SQLITE_QUERY_SUCCESS;
	}catch(CSQLiteException& e){
		bRet = false;
		LOG_ERROR(e.what());
		m_nLastError = SQLITE_QUERY_ERROR;
	}

	if(stmt)		sqlite3_finalize(stmt);
	if(pszErrMsg)		sqlite3_free(pszErrMsg);
	return bRet;
}

int CDBSQLite::GetIntField(const std::string& sSQL)
{
	CYCriticalSectionLock(&m_cs, true);
	sqlite3_stmt *stmt = NULL;
	char *pszErrMsg = NULL;
	int nRet(-1);

	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", sSQL.c_str(), "GetIntField");

		int nRes(0);
		if(nRes = sqlite3_prepare_v2(pDbconnection, sSQL.c_str(), -1, &stmt, NULL) != SQLITE_OK)
			throw CSQLiteException("prepare statement error", sSQL.c_str(), "GetIntField");

		if(nRes = sqlite3_step(stmt) == SQLITE_ROW){
			nRet = sqlite3_column_int(stmt, 0);
		}else if(nRes == SQLITE_DONE || nRes == SQLITE_OK){
			nRet = -1;
		}else{
			std::stringstream ssErr;
			ssErr<<"step statement error("<<nRes<<")";
			throw CSQLiteException(ssErr.str().c_str(), sSQL.c_str(), "GetIntField");
		}
		m_nLastError = SQLITE_QUERY_SUCCESS;
	}catch(CSQLiteException& e){
		nRet = -1;
		LOG_ERROR(e.what());
		m_nLastError = SQLITE_QUERY_ERROR;
	}

	if(stmt)		sqlite3_finalize(stmt);
	if(pszErrMsg)		sqlite3_free(pszErrMsg);
	return nRet;
}

std::string CDBSQLite::GetStringField(const std::string& sSQL)
{
	CYCriticalSectionLock(&m_cs, true);
	sqlite3_stmt *stmt = NULL;
	char *pszErrMsg = NULL;
	std::string sRet = "";

	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", sSQL.c_str(), "GetIntField");

		int nRes(0);
		if(nRes = sqlite3_prepare_v2(pDbconnection, sSQL.c_str(), -1, &stmt, NULL) != SQLITE_OK)
			throw CSQLiteException("prepare statement error", sSQL.c_str(), "GetIntField");

		if(nRes = sqlite3_step(stmt) == SQLITE_ROW){
			sRet = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		}else if(nRes == SQLITE_DONE || nRes == SQLITE_OK){
			sRet = "";
		}else{
			std::stringstream ssErr;
			ssErr<<"step statement error("<<nRes<<")";
			throw CSQLiteException(ssErr.str().c_str(), sSQL.c_str(), "GetIntField");
		}
		m_nLastError = SQLITE_QUERY_SUCCESS;
	}catch(CSQLiteException& e){
		sRet = "";
		LOG_ERROR(e.what());
		m_nLastError = SQLITE_QUERY_ERROR;
	}

	if(stmt)		sqlite3_finalize(stmt);
	if(pszErrMsg)		sqlite3_free(pszErrMsg);
	return sRet;
}

bool CDBSQLite::ExecuteTransac(const TransactSQLs& vecSQL)
{
	CYCriticalSectionLock(&m_cs, true);
	sqlite3_stmt *stmt = NULL;
	char *pszErrMsg = NULL;
	bool bRet(false);

	try{
		InitConnection();
		if(!pDbconnection)
			throw CSQLiteException("invalid connection!", "DBSQLite", "ExecuteTransac");

		int nRes(0);
		sqlite3_exec(pDbconnection, "begin", NULL, NULL, &pszErrMsg);

		for(TransactSQLs::const_iterator iter = vecSQL.begin(); iter != vecSQL.end(); ++iter){
			const std::string& sSQL = (std::string)(*iter);
			if(nRes = sqlite3_exec(pDbconnection, sSQL.c_str(), NULL, NULL, &pszErrMsg) != SQLITE_OK)
				throw CSQLiteException(pszErrMsg, sSQL.c_str(), "ExecuteTransac");
		}

		sqlite3_exec(pDbconnection, "commit", NULL, NULL, NULL);
		m_nLastError = SQLITE_QUERY_SUCCESS;
	}catch(CSQLiteException& e){
		sqlite3_exec(pDbconnection, "rollback", NULL, NULL, NULL);
		LOG_ERROR(e.what());
		sqlite3_free(pszErrMsg);
		m_nLastError = SQLITE_QUERY_ERROR;
		return false;
	}

	if(pszErrMsg)		sqlite3_free(pszErrMsg);	
	return true;
}

bool CDBSQLite::GetIsTableExist(const std::string& sTable)
{
	std::stringstream ssSQL;
	ssSQL<<"select count(*) from sqlite_master where type = \'table\' and name = \'"<<sTable<<"\'";

	return GetIntField(ssSQL.str()) > 0;
}

bool CDBSQLite::GetIsColumnExist(const std::string& sTable, const std::string& sCol)
{
	std::stringstream ssSQL;
	ssSQL<<"select count(*) from PRAGMA_table_info(\'"<<sTable<<"\') where name=\'"<<sCol<<"\'";

	return GetIntField(ssSQL.str()) > 0;
}

void CDBSQLite::InitConnection()
{
	if(!pDbconnection)
		sqlite3_open_v2(pDbfilename, &pDbconnection, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
}

int CDBSQLite::GetLastError()
{
	return m_nLastError;
}


