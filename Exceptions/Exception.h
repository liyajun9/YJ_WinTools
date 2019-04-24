#pragma once
/*
Exception���࣬����msg��where
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
		void MessageBox(HWND hWnd = NULL); //������ʾ�쳣��Ϣ
		virtual _tstring GetReason();	
		virtual _tstring GetClass(); 
		virtual _tstring GetMethod(); 

	protected:
		_tstring m_sReason;    //�쳣ԭ����ʲô
		_tstring m_sClassName;		//�쳣����������
		_tstring m_sMethodName;//�쳣�����ķ�����
		_tstring m_sMsg; //��ӡ��ʽ
	};
}