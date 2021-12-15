#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPColorButton.h"
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"


// Datasources_Osm form view

class Datasources_Osm : public CBCGPFormView
{
	DECLARE_DYNCREATE(Datasources_Osm)

public:
	Datasources_Osm();           // protected constructor used by dynamic creation
	virtual ~Datasources_Osm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_OSM_DATASOURCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CCustomToolTipCtrl	m_ToolTip;
public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CString				m_File;
	CStatic				m_Ctrl_File;
	CString				m_Base;
	CString				m_Encoding;
	CString				m_Script;

	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	afx_msg void OnEnKillfocus();
	afx_msg void OnStnClickedStaticFileOsm();
	afx_msg void OnStnClickedStaticResetOsm();
};


