// Tab_two_Postgis.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Tab_two_Postgis.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTab_two_Postgis dialog

IMPLEMENT_DYNAMIC(CTab_two_Postgis, CBCGPDialog)

CTab_two_Postgis::CTab_two_Postgis(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_TAB_2_POSTGIS, pParent)
	, m_Schema(_T(""))
	, m_Extent(_T(""))
	, m_GeometryTable(_T(""))
	, m_GeometryField(_T(""))
	, m_CursorSize(_T("0"))
	, m_RowLimit(_T("0"))
	, m_Srid(_T("0"))
	, m_InitialSize(_T("1"))
	, m_MaxSize(_T("10"))
	, m_Check_EstimateExtent(FALSE)
	, m_Check_SimplityGeometries(FALSE)
	, m_Check_AutodetectKeyField(FALSE)
	, m_Check_PersistConnection(TRUE)
	, m_Check_ExtentFromSubquery(FALSE)
	, m_activeEnKill(FALSE)
{

}

CTab_two_Postgis::~CTab_two_Postgis()
{
}

void CTab_two_Postgis::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCHEMA_POSTGIS, m_Schema);
	DDX_Text(pDX, IDC_EDIT_EXTENT_POSTGIS, m_Extent);
	DDX_Check(pDX, IDC_CHECK_ESTIMATE_EXTENT_POSTGIS, m_Check_EstimateExtent);
	DDX_Text(pDX, IDC_EDIT_GEOMETRY_TABLE_POSTGIS, m_GeometryTable);
	DDX_Text(pDX, IDC_EDIT_GEOMETRY_FIELD_POSTGIS, m_GeometryField);
	DDX_Text(pDX, IDC_EDIT_CURSOR_SIZE_POSTGIS, m_CursorSize);
	DDX_Text(pDX, IDC_EDIT_ROW_LIMIT_POSTGIS, m_RowLimit);
	DDX_Text(pDX, IDC_EDIT_SRID_POSTGIS, m_Srid);
	DDX_Text(pDX, IDC_EDIT_INITIAL_SIZE_POSTGIS, m_InitialSize);
	DDX_Text(pDX, IDC_EDIT_MAX_SIZE_POSTGIS, m_MaxSize);
	DDX_Check(pDX, IDC_CHECK_SIMPLIFY_GEOMETRIES_POSTGIS, m_Check_SimplityGeometries);
	DDX_Check(pDX, IDC_CHECK_AUTODETECT_POSTGIS, m_Check_AutodetectKeyField);
	DDX_Check(pDX, IDC_CHECK_PERSIST_POSTGIS, m_Check_PersistConnection);
	DDX_Check(pDX, IDC_CHECK_EXTENT_FR_SUB_POSTGIS, m_Check_ExtentFromSubquery);
}


BEGIN_MESSAGE_MAP(CTab_two_Postgis, CBCGPDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_SCHEMA_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_EXTENT_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_ESTIMATE_EXTENT_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_GEOMETRY_TABLE_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_GEOMETRY_FIELD_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_CURSOR_SIZE_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_ROW_LIMIT_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_SRID_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_INITIAL_SIZE_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_MAX_SIZE_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_SIMPLIFY_GEOMETRIES_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_AUTODETECT_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_PERSIST_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_EXTENT_FR_SUB_POSTGIS, &CTab_two_Postgis::OnEnKillfocusPostgis)
END_MESSAGE_MAP()


// CTab_two_Postgis message handlers

void CTab_two_Postgis::OnEnKillfocusPostgis()
{
	if (m_activeEnKill)
	{
		UpdateData();
		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pMainFrm->EnkillFocus_Datasources_Postgis();
	}
}

