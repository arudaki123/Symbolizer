#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPColorButton.h"
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"

// Symbolizer_Dot form view

class Symbolizer_Dot : public CBCGPFormView
{
	DECLARE_DYNCREATE(Symbolizer_Dot)

public:
	Symbolizer_Dot();           // protected constructor used by dynamic creation
	virtual ~Symbolizer_Dot();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_DOTSYMBOLIZER };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;

public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CString				m_Opacity;
	CBCGPColorButton	m_Ctrl_Color;
	CString				m_Width;
	CString				m_Height;
	CComboBox			m_Ctrl_CompOp;

	CString				m_Script;

	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	COLORREF GetColor(std::string value);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnKillfocusFloat();
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnStnClickedStaticResetDot();
};


