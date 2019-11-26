#include "StdAfx.h"
#include ".\sqliteob.h"
#include <shlwapi.h>
#include "IBADAL.h"
#include "..\IBA.h"

using namespace NS_DAL;

SqliteOb::SqliteOb()
:m_bIsOpened(FALSE),m_pDB(NULL)
{
	TCHAR lpFilePath[MAX_PATH];
	RtlZeroMemory(lpFilePath,MAX_PATH);
	::GetModuleFileName(theApp.m_hInstance,lpFilePath,MAX_PATH);
	::PathRemoveFileSpec(lpFilePath);//移除文件路径后面的文件名以及可能的反斜杠
	::PathAppend(lpFilePath, _T("netbar.db"));//在文件路径后面加上\文件名
	CString strPath(lpFilePath);
	OpenDB(strPath);		
}

SqliteOb::~SqliteOb(void)
{
	CloseDB();
}

BOOL SqliteOb::ExecDB(const CString& strSQL, int* pnAffectedRows, CString& strErrMsg)
{
	*pnAffectedRows = 0;
	strErrMsg.Empty();
	if(FALSE == m_bIsOpened){
		strErrMsg = _T("Database hasn't been opened");
		return FALSE;
	}
	char* error = NULL;
	std::string sSQL = CStringToUtf8(strSQL);
	if (sqlite3_exec(m_pDB, sSQL.c_str(), 0, 0, &error) == 0) {
		*pnAffectedRows = sqlite3_changes(m_pDB);
		return TRUE;
	}
	else{
		strErrMsg = Utf8ToCString(error);
		sqlite3_free(error);
		return FALSE;
	}
}

BOOL SqliteOb::CopyLocalReportToMySQL(CString& strErrMsg)
{
	strErrMsg.Empty();
	if(FALSE == m_bIsOpened){
		strErrMsg = _T("Database hasn't been opened");
		return FALSE;
	}
	BOOL bRet(FALSE);

	CString strSQL,strInsertSQL;
	strSQL.Format(_T("select * from LocalReport"));
	std::string sSQL = CStringToUtf8(strSQL);

	sqlite3_stmt *stmt;
	int nMemberId;
	CString strNetId,strPwd,strReportTime;
	//std::string sTmp;
	bRet = sqlite3_prepare_v2(m_pDB,sSQL.c_str(),-1,&stmt,0);
	if(SQLITE_OK == bRet){
		while(SQLITE_ROW ==sqlite3_step(stmt)){
			nMemberId = sqlite3_column_int(stmt,0);
			strNetId = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,1)))));
			strPwd = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,2)))));
			strReportTime = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,3)))));

			strInsertSQL.Format(_T("insert into localreport(memberId,netId,password,reporttime,localregister) \
								   values(%d,'%s','%s','%s',0)"),nMemberId,strNetId,strPwd,strReportTime);
			//sTmp = CStringToUtf8(strInsertSQL);
			if(FALSE == InsertToMySQLTable(strInsertSQL)) {
				strErrMsg = _T("InsertIntoMySQL error");
				return FALSE;
			}
		}
		sqlite3_finalize(stmt);
		return TRUE;
	}
	strErrMsg = _T("sqlite3_prepare_v2 error");
	return FALSE;
}

BOOL SqliteOb::CopyLocalMemberToMySQL(CString& strErrMsg)
{
	strErrMsg.Empty();
	if(FALSE == m_bIsOpened){
		strErrMsg = _T("Database hasn't been opened");
		return FALSE;
	}
	BOOL bRet(FALSE);

	CString strSQL,strInsertSQL;
	strSQL.Format(_T("select * from LocalMember"));
	std::string sSQL = CStringToUtf8(strSQL);

	sqlite3_stmt *stmt;
	int nMemberId,nBalance,nBeforeUser,nIsLocalCheckin,nLastUpdateTime,nTotalMoney,nPcClass,nClassId,nPayType,nNextCheckinTime,nIsReturned;
	CString strMemberName,strNetId,strIdNumber,strCheckinTime,strLocalCheckinTime,strTermId,strRate,strCheckoutTime;
	//std::string sTmp;
	bRet = sqlite3_prepare_v2(m_pDB,sSQL.c_str(),-1,&stmt,0);
	if(SQLITE_OK == bRet){
		while(SQLITE_ROW ==sqlite3_step(stmt)){
			nMemberId = sqlite3_column_int(stmt,0);
			nBalance = sqlite3_column_int(stmt,1);
			nBeforeUser = sqlite3_column_int(stmt,2);
			strMemberName = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,3)))));
			strNetId = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,4)))));
			strIdNumber = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,5)))));
			strCheckinTime = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,6)))));
			strLocalCheckinTime = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,7)))));
			nIsLocalCheckin = sqlite3_column_int(stmt,8);
			nLastUpdateTime = sqlite3_column_int(stmt,9);
			nTotalMoney = sqlite3_column_int(stmt,10);
			nPcClass = sqlite3_column_int(stmt,11);
			nClassId = sqlite3_column_int(stmt,12);
			strTermId = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,13)))));
			strRate = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,14)))));
			nPayType = sqlite3_column_int(stmt,15);
			nNextCheckinTime = sqlite3_column_int(stmt,16);
			strCheckoutTime = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,17)))));
			nIsReturned = sqlite3_column_int(stmt,18);

			strInsertSQL.Format(_T("insert into LocalMember(memberId,balance,beforeUsed,memberName,netId,idNumber,checkinTime,localCheckinTime,\
								   isLocalCheckin,lastUpdateTime,totalMoney,pcClass,classId,termId,rate,payType,nextCheckinTime,CheckoutTime,isReturned) \
								   values(%d,%d,%d,'%s','%s','%s','%s','%s',%d,%d,%d,%d,%d,'%s','%s',%d,%d,'%s',%d)"),\
								   nMemberId,nBalance,nBeforeUser,strMemberName,strNetId,strIdNumber,strCheckinTime,strLocalCheckinTime,\
								   nIsLocalCheckin,nLastUpdateTime,nTotalMoney,nPcClass,nClassId,strTermId,strRate,nPayType,nNextCheckinTime,\
								   strCheckoutTime,nIsReturned);
			//sTmp = CStringToUtf8(strInsertSQL);
			if(FALSE == InsertToMySQLTable(strInsertSQL)) {
				strErrMsg = _T("InsertIntoMySQL error");
				return FALSE;
			}
		}
		sqlite3_finalize(stmt);
		return TRUE;
	}
	strErrMsg = _T("sqlite3_prepare_v2 error");
	return FALSE;
}
BOOL SqliteOb::CopyLocalCreditToMySQL(CString& strErrMsg)
{
	strErrMsg.Empty();
	if(FALSE == m_bIsOpened){
		strErrMsg = _T("Database hasn't been opened");
		return FALSE;
	}
	BOOL bRet(FALSE);

	CString strSQL,strInsertSQL;
	strSQL.Format(_T("select * from LocalCredit"));
	std::string sSQL = CStringToUtf8(strSQL);

	sqlite3_stmt *stmt;
	int nMemberId,nAmount;
	CString strCreditTime,strCheckCode;
	//std::string sTmp;
	bRet = sqlite3_prepare_v2(m_pDB,sSQL.c_str(),-1,&stmt,0);
	if(SQLITE_OK == bRet){
		while(SQLITE_ROW ==sqlite3_step(stmt)){
			nMemberId = sqlite3_column_int(stmt,0);
			nAmount = sqlite3_column_int(stmt,1);
			strCreditTime = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,2)))));
			strCheckCode = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,3)))));
			strInsertSQL.Format(_T("insert into LocalCredit(memberId,amount,creditTime,checkcode) \
								   values(%d,%d,'%s','%s')"),nMemberId,nAmount,strCreditTime,strCheckCode);
			//sTmp = CStringToUtf8(strInsertSQL);
			if(FALSE == InsertToMySQLTable(strInsertSQL)) {
				strErrMsg = _T("InsertIntoMySQL error");
				return FALSE;
			}
		}
		sqlite3_finalize(stmt);
		return TRUE;
	}
	strErrMsg = _T("sqlite3_prepare_v2 error");
	return FALSE;
}
BOOL SqliteOb::CopyCostRateToMySQL(CString& strErrMsg)
{
	strErrMsg.Empty();
	if(FALSE == m_bIsOpened){
		strErrMsg = _T("Database hasn't been opened");
		return FALSE;
	}
	BOOL bRet(FALSE);

	CString strSQL,strInsertSQL;
	strSQL.Format(_T("select * from CostRate"));
	std::string sSQL = CStringToUtf8(strSQL);

	sqlite3_stmt *stmt;
	int nPcClass,nClassId;
	CString strRate;
	//std::string sTmp;
	bRet = sqlite3_prepare_v2(m_pDB,sSQL.c_str(),-1,&stmt,0);
	if(SQLITE_OK == bRet){
		while(SQLITE_ROW ==sqlite3_step(stmt)){
			nPcClass = sqlite3_column_int(stmt,0);
			nClassId = sqlite3_column_int(stmt,1);
			strRate = Utf8ToCString(static_cast<const char*>( static_cast<void*>( const_cast<unsigned char*>(sqlite3_column_text(stmt,2)))));
			strInsertSQL.Format(_T("insert into CostRate(pcClass,classId,rate) \
								   values(%d,%d,'%s')"),nPcClass,nClassId,strRate);
			//sTmp = CStringToUtf8(strInsertSQL);
			if(FALSE == InsertToMySQLTable(strInsertSQL)) {
				strErrMsg = _T("InsertIntoMySQL error");
				return FALSE;
			}
		}
		sqlite3_finalize(stmt);
		return TRUE;
	}
	strErrMsg = _T("sqlite3_prepare_v2 error");
	return FALSE;
}

BOOL SqliteOb::InsertToMySQLTable(const CString& strSQL)
{
	int nRet = CIBADAL::GetInstance()->ExecuteSQLEx(strSQL);
	if(nRet <= 0 ){
		return FALSE;
	}
	return TRUE;
}

BOOL SqliteOb::IsTableExist(const CString& TableName)
{
	if(FALSE == m_bIsOpened){
		return FALSE;
	}

	sqlite3_stmt* stmt=NULL;
	CString strSQL;
	strSQL.Format(_T("select count(*) from sqlite_master where type = 'table' and name = '%s'"), TableName);
	std::string sSQL = CStringToUtf8(strSQL);
	int nRet = sqlite3_prepare_v2(m_pDB,sSQL.c_str(),-1,&stmt,NULL);
	if(SQLITE_OK == nRet){
		nRet = sqlite3_step(stmt);
		//if(SQLITE_OK != nRet && SQLITE_DONE != nRet && SQLITE_ROW != nRet){
		//	return FALSE;
		//}
		int bIsTableExist = sqlite3_column_int(stmt,0);
		sqlite3_finalize(stmt);
		return bIsTableExist;
	}
	return FALSE;
}

BOOL SqliteOb::OpenDB(const CString& strPath)
{
	if(strPath.IsEmpty()) return FALSE;
	std::string sPath = CStringToUtf8(strPath);
	if(0 == sqlite3_open(sPath.c_str(),&m_pDB)){
		m_bIsOpened = TRUE;
		return TRUE;
	}
	return FALSE;
}

void SqliteOb::CloseDB()
{
	if(m_bIsOpened){
		if(m_pDB) sqlite3_close(m_pDB);
		m_pDB = NULL;
		m_bIsOpened = FALSE;
	}
}

CString SqliteOb::Utf8ToCString(const char* utf8)
{
	//Utf8 to Unicode (pass UTF8)
	//Unicode to WideChar(Multi) or nothing
	int  nWideLen = MultiByteToWideChar(CP_UTF8,
		0,
		utf8,
		-1,
		NULL,
		0);  
	wchar_t* lpWide = new  wchar_t[nWideLen+1];  
	memset(lpWide,0,(nWideLen+1)*sizeof(wchar_t));  
	MultiByteToWideChar(CP_UTF8,
		0,
		utf8,
		-1,
		(LPWSTR)lpWide,
		nWideLen); 
	CString strOut;
#ifndef _UNICODE //MultiByte, convert with CP_ACP again
	int  MultiLen = WideCharToMultiByte( CP_ACP,
		0,
		lpWide,
		-1,
		NULL,
		0);  

	char * lpMulti = new  char[MultiLen+1]; 
	memset(lpMulti,0,(MultiLen+1)*sizeof(char));  
	WideCharToMultiByte(CP_ACP,
		0,
		lpWide,
		-1,
		(LPSTR)lpMulti,
		MultiLen); 
	strOut = lpMulti;
	delete lpMulti;
#else
	strOut = lpWide;
#endif
	delete lpWide;

	return strOut;
}


std::string SqliteOb::CStringToUtf8(const CString& str)
{
	//if multibyte,multibyte to unicode first
	//unicode to utf8
	wchar_t* lpwchar = NULL; 
#ifndef _UNICODE
	int nWideLen = MultiByteToWideChar(CP_ACP,
		0,
		str.GetBuffer(),
		-1,
		NULL,
		0);
	lpwchar = new wchar_t[nWideLen+1];
	memset(lpwchar,0,(nWideLen+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP,
		0,
		str.GetBuffer(),
		-1,
		(LPWSTR)lpwchar,
		nWideLen);
#else
	int nLen = str.GetLength();
	lpwchar = new wchar_t[nLen+1];
	memset(lpwchar,0,(nLen+1)*sizeof(wchar_t));
	StrCpyW(lpwchar,(LPCTSTR)str);
#endif
	int  MultiLen = WideCharToMultiByte( CP_UTF8,
		0,
		lpwchar,
		-1,
		NULL,
		0,
		NULL,
		NULL);  
	char * lpMulti = new  char[MultiLen+1]; 
	memset(lpMulti,0,(MultiLen+1)*sizeof(char));  
	WideCharToMultiByte(CP_UTF8,
		0,
		lpwchar,
		-1,
		(LPSTR)lpMulti,
		MultiLen,
		NULL,
		NULL); 
	std::string sOut = lpMulti;
	delete lpMulti;
	delete lpwchar;
	return sOut;
}