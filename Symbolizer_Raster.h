#pragma once
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"



// Symbolizer_Raster form view

class Symbolizer_Raster : public CBCGPFormView
{
	DECLARE_DYNCREATE(Symbolizer_Raster)

public:
	Symbolizer_Raster();           // protected constructor used by dynamic creation
	virtual ~Symbolizer_Raster();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_RASTERSYMBOLIZER};
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;
public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CString				m_Opacity;
	CString				m_Filterfactor;
	CComboBox			m_Ctrl_Scaling;
	CString				m_Meshsize;
	CComboBox			m_Ctrl_CompOp;
	CComboBox			m_Ctrl_Mode;
	CBCGPColorButton	m_Ctrl_Color;
	CString				m_Epsilon;
	CString				m_Stop;
	
	CString				m_Script;
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	COLORREF GetColor(std::string value);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnKillfocusFloat();
	afx_msg void OnStnClickedStaticResetRaster();
};


