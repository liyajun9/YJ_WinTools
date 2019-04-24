#include "stdafx.h"
#include "WSAException.h"

namespace YJ_WinTools{


	CWSAException::CWSAException(PCTSTR pszClass/* = _T("unknownClass")*/, PCTSTR pszMethod/* = _T("unknownMethod")*/, PCTSTR pszAPIName/* = _T("unknownAPI")*/)
	{
		m_sClassName = pszClass;
		m_sMethodName = pszMethod;
		m_sAPIName = pszAPIName;
		m_errorcode = WSAGetLastError();
		m_sReason = GetLastErrorMsg(m_errorcode);

		TCHAR pszErrCode[MAX_LINE_LEN];
		memset(pszErrCode, 0, MAX_LINE_LEN);
		_itot_s(m_errorcode, pszErrCode, 10);

#ifdef _UNICODE
		m_sMsg = _T("Exception: Reason(");
		m_sMsg += pszErrCode;
		m_sMsg += _T(") : ") + m_sReason + _T(" at ") + m_sClassName + _T("::") + m_sMethodName + _T("   api = ") + m_sAPIName;
#else
		m_sMsg = "Exception: Reason(";
		m_sMsg += pszErrCode;
		m_sMsg += ") : " + m_sReason + " at " + m_sClassName + "::" + m_sMethodName  + "   api = " + m_sAPIName;
#endif
	}

	_tstring CWSAException::GetMsg()
	{
		return m_sMsg;
	}

	DWORD CWSAException::GetErrorCode()
	{
		return m_errorcode;
	}

	_tstring CWSAException::GetLastErrorMsg(DWORD errcode)
	{
		LPVOID lpMsgBuf; 
		if(!FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, 
			errcode, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf, 
			0, 
			NULL 
			)){
				return GetLastErrorMsg(GetLastError());
		}
		_tstring sRet = (LPTSTR) lpMsgBuf;
		LocalFree(lpMsgBuf);
		return sRet;
	}

}