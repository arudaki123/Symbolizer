#pragma once

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include<string>
#include "BCGPFormView.h"
#include "CustomToolTipCtrl.h"


// Simpolizer_Linepattern form view

class Symbolizer_Linepattern : public CBCGPFormView
{
	DECLARE_DYNCREATE(Symbolizer_Linepattern)

public:
	Symbolizer_Linepattern();           // protected constructor used by dynamic creation
	virtual ~Symbolizer_Linepattern();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_LINEPATTERNSYMPOLIZER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;
public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CComboBox			m_Ctrl_Type;
	CString				m_File;
	CStatic				m_Ctrl_File;
	CComboBox			m_Ctrl_Alignment;
	CString				m_Width;
	CString				m_Opacity;
	CComboBox			m_Ctrl_Linecap;
	CComboBox			m_Ctrl_Linejoin;
	CString				m_Dasharray;
	CString				m_MiterLimit;
	BOOL				m_Clip;
	CString				m_Simplify;
	CComboBox			m_Ctrl_SimplifyAlgorithm;
	CString				m_Smooth;
	CString				m_Offset;
	CString				m_GeometryTransform;
	CString				m_Transform;
	CComboBox			m_Ctrl_CompOp;
	
	CString				m_Script;
public:
	std::string SettingsXml();
	void SettingsXml(std::string);

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefault();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnKillfocusFloat();

	afx_msg void OnBnClickedCheckClipLine();
	
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnStnClickedStaticResetLinepattern();
};


