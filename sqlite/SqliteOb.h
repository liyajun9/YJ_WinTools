#pragma once
#include "..\..\L2ADOKit\sqlite3.h"
#include <iomanip>
#pragma comment (lib,"..\\Lib\\sqlite3.lib")


namespace NS_DAL
{
class SqliteOb
{
public:
	SqliteOb(void);
	virtual ~SqliteOb(void);

public:
	BOOL IsTableExist(const CString& TableName);//TableName is case sensitive
	BOOL ExecDB(const CString& strSQL, int* pnAffectedRows, CString& strErrMsg);
	BOOL CopyLocalReportToMySQL(CString& strErrMsg);
	BOOL CopyLocalMemberToMySQL(CString& strErrMsg);
	BOOL CopyLocalCreditToMySQL(CString& strErrMsg);
	BOOL CopyCostRateToMySQL(CString& strErrMsg);
private:
	BOOL OpenDB(const CString& strPath);
	void CloseDB();
	BOOL InsertToMySQLTable(const CString& strSQL);

public:
	static CString Utf8ToCString(const char* utf8);
	static std::string CStringToUtf8(const CString& str);

private:
	BOOL m_bIsOpened;
	sqlite3* m_pDB;
	CString m_strDBPath;
};
}
