#pragma once
#include "BCGPDialog.h"
#include "CustomToolTipCtrl.h"

// CTab_two_Postgis dialog

class CTab_two_Postgis : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTab_two_Postgis)

public:
	CTab_two_Postgis(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab_two_Postgis();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_2_POSTGIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString			m_Schema;
	CString			m_Extent;
	BOOL			m_Check_EstimateExtent;
	CString			m_GeometryTable;
	CString			m_GeometryField;
	CString			m_CursorSize;
	CString			m_RowLimit;
	CString			m_Srid;
	CString			m_InitialSize;
	CString			m_MaxSize;
	BOOL			m_Check_SimplityGeometries;
	BOOL			m_Check_AutodetectKeyField;
	BOOL			m_Check_PersistConnection;
	BOOL			m_Check_ExtentFromSubquery;
	BOOL			m_activeEnKill;
	//void SetDefault();
	afx_msg void OnEnKillfocusPostgis();
	void Reset_Value();
};
