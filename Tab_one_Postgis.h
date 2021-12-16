#pragma once
#include "BCGPDialog.h"
#include "CustomToolTipCtrl.h"

// CTab_one_Postgis dialog

class CTab_one_Postgis : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTab_one_Postgis)

public:
	CTab_one_Postgis(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab_one_Postgis();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_1_POSTGIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString			m_Table;
	BOOL			m_Check_Key_Field;
	BOOL			m_Check_KeyFieldAsAttribute;
	CString			m_Encoding;
	CString			m_Dbname;
	CString			m_Host;
	CString			m_Port;
	CString			m_User;
	CString			m_Password;
	CString			m_ConnectTimeout;

	BOOL			m_activeEnKill;
	afx_msg void OnEnKillfocusPostgis();
};
