
#if !defined(AFX_CUSTOMTOOLTIPCTRL_H__4D5FA97F_3329_4381_BFCD_746E960CF044__INCLUDED_)
#define AFX_CUSTOMTOOLTIPCTRL_H__4D5FA97F_3329_4381_BFCD_746E960CF044__INCLUDED_

#include "resource.h"		// main symbols
#include <sqlite3.h>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <tinyxml2.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomToolTipCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomToolTipCtrl window

class CCustomToolTipCtrl : public CBCGPToolTipCtrl
{
	// Construction
public:
	CCustomToolTipCtrl();
	BOOL ReadTooltipSqlite(CString path);
	BOOL WriteTooltipSqlite(CString path);
	//int callback(void* data, int argc, char** argv, char** azColName);
	// Attributes
public:
	int						m_nCurrID;
	std::map<std::string, std::string>	m_MapTooltip_Doc;
	std::map<std::string, std::string>	m_MapTooltip_Default;
	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CCustomToolTipCtrl)
		//}}AFX_VIRTUAL

	virtual CSize GetIconSize();

	virtual BOOL OnDrawIcon(CDC* pDC, CRect rectImage);
	bool isFloat(CString myString);

	// Implementation
public:
	virtual ~CCustomToolTipCtrl();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomToolTipCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	CBCGPToolBarImages m_imageOK;
	CBCGPToolBarImages m_imageCancel;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTOOLTIPCTRL_H__4D5FA97F_3329_4381_BFCD_746E960CF044__INCLUDED_)
