// Exception
// Example:
//	try{
//			...
//			throw CYException(L"method",L"class",L"reason");
//		}catch(CYException e){
//			...handle
//		}
// author:liyajun

#pragma once
#include <string>
#include "..\Log\tstring.h"

class CYException
{
public:
	CYException(TCHAR *pszReason, TCHAR *pszMethod = _T("unknownMethod"), TCHAR *pszClass = _T("unknownClass"));
	virtual ~CYException() {};

public:
	tstring GetMsg();
	tstring GetReason();	
	tstring GetClass(); 
	tstring GetMethod(); 

protected:
	CYException();
	tstring m_sReason;			
	tstring m_sClass;		
	tstring m_sMethod;		
	tstring m_sMsg;				
};

