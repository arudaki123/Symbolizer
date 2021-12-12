#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include<string>
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"


// Symbolizer_Point form view

class Symbolizer_Point : public CBCGPFormView
{
	DECLARE_DYNCREATE(Symbolizer_Point)

public:
	Symbolizer_Point();           // protected constructor used by dynamic creation
	virtual ~Symbolizer_Point();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_POINTSYMBOLIZER };
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
	CString				m_Opacity;
	BOOL				m_Allowoverlap;
	BOOL				m_Ignoreplacement;
	CComboBox			m_Ctrl_Placement;
	CComboBox			m_Ctrl_CompOp;
	CString				m_Transform;
	CString				m_Script;

	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnKillfocusFloat();
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedCheckIgnorePoint();
	afx_msg void OnBnClickedCheckAllowoverlapPoint();
	afx_msg void OnStnClickedStaticResetPoint();
};


