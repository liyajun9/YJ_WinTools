#pragma once
#include "sqlite\include\sqlite3.h"
#include <winbase.h>
#include <vector>
#include "Macros\ttype.h"

constexpr int SQLITE_QUERY_SUCCESS = 0;
constexpr int SQLITE_QUERY_ERROR = 1;

using TransactSQLsA = std::vector<std::string>;
using TransactSQLsW = std::vector<std::wstring>;

#if defined(UNICODE) || defined(_UNICODE)
#define TOUTF8		NS_Yutils::WCharToUtf8
#define FROMUTF8	NS_Yutils::Utf8ToWChar
#else
#define TOUTF8		NS_Yutils::MBToUtf8
#define FROMUTF8	NS_Yutils::Utf8ToMB
#endif

#define SQLite YSQLite::GetInstance()

template<typename TString>
class YSQLite{
public:
	static YSQLite& GetInstance()
	{
		static YSQLite dbSqliteInstance;
		return dbSqliteInstance;
	}

	bool GetIsExist(const TString& sSQL) //return -1 on error or empty result
	{
		std::string sSQLutf8 = TOUTF8(sSQL);

		YCSLocker locker(m_cs);
		sqlite3_stmt* stmt = NULL;
		char* pszErrMsg = NULL;
		bool bRet(false);

		try {
			InitConnection();
			if (!pDbconnection)
				throw YSQLiteException("invalid connection!", sSQL.c_str(), "GetIntField");

			int nRes(0);
			if (nRes = sqlite3_prepare_v2(pDbconnection, sSQLutf8.c_str(), -1, &stmt, NULL) != SQLITE_OK)
				throw YSQLiteException("prepare statement error", sSQL.c_str(), "GetIntField");

			if (nRes = sqlite3_step(stmt) == SQLITE_ROW) {
				bRet = true;
			}
			else if (nRes == SQLITE_DONE || nRes == SQLITE_OK) {
				bRet = false;
			}
			else {
				std::stringstream ssErr;
				ssErr << "step statement error(" << nRes << ")";
				throw YSQLiteException(ssErr.str().c_str(), sSQL.c_str(), "GetIntField");
			}
			nLastError = SQLITE_QUERY_SUCCESS;
		}
		catch (YSQLiteException & e) {
			bRet = false;
			LOGERROR(e.what());
			nLastError = SQLITE_QUERY_ERROR;
		}

		if (stmt)		sqlite3_finalize(stmt);
		if (pszErrMsg)		sqlite3_free(pszErrMsg);
		return bRet;
	}

	TString GetStringField(const TString& sSQL) //return "" on error or empty result
	{
		std::string sSQLutf8 = TOUTF8(sSQL);

		YCSLocker locker(m_cs);
		sqlite3_stmt* stmt = NULL;
		char* pszErrMsg = NULL;
		std::string sRet = "";

		try {
			InitConnection();
			if (!pDbconnection)
				throw YSQLiteException("invalid connection!", sSQL.c_str(), "GetIntField");

			int nRes(0);
			if (nRes = sqlite3_prepare_v2(pDbconnection, sSQLutf8.c_str(), -1, &stmt, NULL) != SQLITE_OK)
				throw YSQLiteException("prepare statement error", sSQL.c_str(), "GetIntField");

			if (nRes = sqlite3_step(stmt) == SQLITE_ROW) {
				sRet = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			}
			else if (nRes == SQLITE_DONE || nRes == SQLITE_OK) {
				sRet = "";
			}
			else {
				std::stringstream ssErr;
				ssErr << "step statement error(" << nRes << ")";
				throw YSQLiteException(ssErr.str().c_str(), sSQL.c_str(), "GetIntField");
			}
			nLastError = SQLITE_QUERY_SUCCESS;
		}
		catch (YSQLiteException & e) {
			sRet = "";
			LOGERROR(e.what());
			nLastError = SQLITE_QUERY_ERROR;
		}

		if (stmt)		sqlite3_finalize(stmt);
		if (pszErrMsg)		sqlite3_free(pszErrMsg);
		return NS_Yutils::Utf8ToMB(sRet);
	}

	bool ExecuteSQL(const std::string& sSQL, unsigned int* pAffectedRows = NULL)
	{
		std::string sSQLutf8 = NS_Yutils::MBToUtf8(sSQL);

		YCSLocker locker(m_cs);
		char* pszErrMsg = NULL;
		try {
			InitConnection();
			if (!pDbconnection)
				throw YSQLiteException("invalid connection!", sSQL.c_str(), "ExecuteSQL");

			int nRes(0);
			if (nRes = sqlite3_exec(pDbconnection, sSQLutf8.c_str(), NULL, NULL, &pszErrMsg) != SQLITE_OK)
				throw YSQLiteException(pszErrMsg, sSQL.c_str(), "ExecuteSQL");

			if (pAffectedRows)
				*pAffectedRows = sqlite3_changes(pDbconnection);

			nLastError = SQLITE_QUERY_SUCCESS;
		}
		catch (YSQLiteException & e) {
			LOGERROR(e.what());
			sqlite3_free(pszErrMsg);
			nLastError = SQLITE_QUERY_ERROR;
			return false;
		}

		if (pszErrMsg)		sqlite3_free(pszErrMsg);
		return true;
	}

	using TransactSQLs = std::vector<TString>;
	bool ExecuteTransac(const TransactSQLs& vecSQL)
	{

	}

	bool GetIsTableExist(const std::string& sTable)
	{

	}

	bool GetIsColumnExist(const std::string& sTable, const std::string& sCol)//note: column name is sensitive
	{

	}

	int GetLastError();//0(SQLITE_QUERY_SUCCESS) or 1(SQLITE_QUERY_ERROR)

private:
	void InitConnection();

private:	
	YSQLite::YSQLite()
		:nLastError(0)
	{
		::InitializeCriticalSection(&m_cs);
	}
	~YSQLite()
	{
		sqlite3_close(pDbconnection);
		::DeleteCriticalSection(&m_cs);
	}

private:
	static sqlite3 *pDbconnection;
	static const char *pDbfilename;
	CRITICAL_SECTION m_cs;  

	int nLastError; //0 - success    other-error
};