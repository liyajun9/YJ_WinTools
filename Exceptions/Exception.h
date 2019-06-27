#pragma once
/*
Exception基类，包含msg和where
*/
#define MAX_LINE_LEN 16

namespace YJ_WinTools
{
	class CException
	{
	public:
		CException(PCTSTR pszReason = _T("unknownReason"), PCTSTR pszClass = _T("unknownClass"), PCTSTR pszMethod = _T("unknownMethod"));
		virtual ~CException() {};

	public:
		virtual _tstring GetMsg();
		void MessageBox(HWND hWnd = NULL); //弹窗显示异常信息
		virtual _tstring GetReason();	
		virtual _tstring GetClass(); 
		virtual _tstring GetMethod(); 

	protected:
		_tstring m_sReason;    //异常原因是什么
		_tstring m_sClassName;		//异常发生的类名
		_tstring m_sMethodName;//异常发生的方法名
		_tstring m_sMsg; //打印格式
	};
}
