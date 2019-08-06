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

class CYexception
{
public:
	CYexception(wchar_t *pszMethod = L"unknownMethod", wchar_t *pszClass = L"unknownClass", wchar_t *pszReason = L"unknownReason");
	virtual ~CYexception() {};

public:
	std::wstring GetMsg();
	std::wstring GetReason();	
	std::wstring GetClass(); 
	std::wstring GetMethod(); 

protected:
	std::wstring m_sReason;			
	std::wstring m_sClass;		
	std::wstring m_sMethod;		
	std::wstring m_sMsg;				
};

