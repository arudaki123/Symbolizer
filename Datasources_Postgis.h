#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"
#include "Tabctrl_Postgis.h"


// Datasources_Postgis form view

class Datasources_Postgis : public CBCGPFormView
{
	DECLARE_DYNCREATE(Datasources_Postgis)

public:
	Datasources_Postgis();           // protected constructor used by dynamic creation
	virtual ~Datasources_Postgis();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_POSTGIS_DATASOURCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;
public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CString				m_Script;
	CTabctrl_Postgis	m_MytabCtrl;

	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	afx_msg void OnEnKillfocus();
	afx_msg void OnStnClickedStaticResetPostgis();
};


