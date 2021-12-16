// MainFrm.h : interface of the CMainFrame class
//


#pragma once
// Symbolizer
#include "WorkSpaceBar_Line.h"
#include "WorkSpaceBar_Linepattern.h"
#include "WorkSpaceBar_Raster.h"
#include "WorkSpaceBar_Point.h"
#include "WorkSpaceBar_Dot.h"

// Datasource
#include "WorkSpaceBar_Ogr.h"
#include "WorkSpaceBar_Osm.h"
#include "WorkSpaceBar_Postgis.h"
#include "WorkSpaceBar_Python.h"

#include "OutputBar.h"
#include "PropertiesViewBar.h"
#include "ToolBox.h"

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	void EnkillFocus_Datasources_Postgis();

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPStatusBar						m_wndStatusBar;
	CBCGPMenuBar						m_wndMenuBar;
	CBCGPToolBar						m_wndToolBar;
	
	// Symbolizer
	CWorkSpaceBar_Line					m_wndWorkSpace_Line;
	CWorkSpaceBar_Linepattern			m_wndWorkSpace_Linepattern;
	CWorkSpaceBar_Raster				m_wndWorkSpace_Raster;
	CWorkSpaceBar_Point					m_wndWorkSpace_Point;
	CWorkSpaceBar_Dot					m_wndWorkSpace_Dot;

	// Datasources
	CWorkSpaceBar_Ogr					m_wndWorkSpace_Ogr;
	CWorkSpaceBar_Osm					m_wndWorkSpace_Osm;
	CWorkSpaceBar_Postgis				m_wndWorkSpace_Postgis;
	CWorkSpaceBar_Python				m_wndWorkSpace_Python;

	COutputBar							m_wndOutput;
	CBCGPPropBar						m_wndPropGrid;
	CToolBoxBarEx						m_wndToolBox;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnToolBox();
	afx_msg void OnWindowManager();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual CBCGPMDIChildWnd* CreateDocumentWindow(LPCTSTR lpcszDocName, CObject* /*pObj*/);
};
