#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPColorButton.h"
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"

// Datasources_Python form view

class Datasources_Python : public CBCGPFormView
{
	DECLARE_DYNCREATE(Datasources_Python)

public:
	Datasources_Python();           // protected constructor used by dynamic creation
	virtual ~Datasources_Python();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_PYTHON_DATASOURCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;
public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CString				m_Encoding;
	CString				m_Script;

	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	afx_msg void OnEnKillfocus();
	afx_msg void OnStnClickedStaticResetPython();
};


