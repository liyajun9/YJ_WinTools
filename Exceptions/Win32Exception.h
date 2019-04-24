/*
Win32Exception£¨ π”√Windows ErrorCode
*/
#pragma once
#include "Exception.h"

namespace YJ_WinTools
{
	class CWin32Exception : public CException
	{
	public:
		CWin32Exception(PCTSTR pszClass = _T("unknownClass"), PCTSTR pszMethod = _T("unknownMethod"), PCTSTR pszAPIName = _T("unknownAPI"));
		virtual _tstring GetMsg();
		DWORD GetErrorCode();

	public:
		static _tstring GetLastErrorMsg(DWORD errcode);

	protected:
		DWORD m_errorcode;
		_tstring m_sAPIName;
	};
}