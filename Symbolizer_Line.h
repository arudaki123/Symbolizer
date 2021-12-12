#pragma once

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include<string>
#include "BCGPFormView.h"
#include "BCGPColorButton.h"
#include "CustomToolTipCtrl.h"

// Symbolizer_Line dialog

class Symbolizer_Line : public CBCGPFormView
{
	DECLARE_DYNAMIC(Symbolizer_Line)
	//DECLARE_DYNCREATE(Symbolizer_Line)
public:
	Symbolizer_Line(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Symbolizer_Line();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_LINESYMPOLIZER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CCustomToolTipCtrl	m_ToolTip;
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	COLORREF GetColor(std::string value);

public:
	BOOL				m_Default;
	CStatic				m_Ctrl_Reset;
	CBCGPColorButton	m_Ctrl_Color;
	
	CString				m_Line_Width;
	CString				m_Opacity;
	CComboBox			m_Ctrl_Linecap;
	CComboBox			m_Ctrl_Linejoin;
	CString				m_Gamma;
	CComboBox			m_Ctrl_GammaMethod;
	CString				m_Dasharray;
	
	CString				m_Dashoffset;
	CString				m_MiterLimit;
	BOOL				m_Clip;
	CString				m_Simplify;
	CComboBox			m_Ctrl_SimplifyAlgorithm;
	CString				m_Smooth;
	CString				m_Offset;
	CComboBox			m_Ctrl_Rasterizer;
	CString				m_GeometryTransform;
	CString				m_Script;
	
	CComboBox			m_Ctrl_CompOp;

	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCheckDefaultLine();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnKillfocusFloat();
	afx_msg void OnBnClickedCheckClipLine();
	afx_msg void OnStnClickedStaticResetLine();
};
