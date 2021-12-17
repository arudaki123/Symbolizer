// CTab_one_Postgis.cpp : implementation file
//
#include "stdafx.h"
#include "Tab_one_Postgis.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CTab_one_Postgis dialog

IMPLEMENT_DYNAMIC(CTab_one_Postgis, CBCGPDialog)

CTab_one_Postgis::CTab_one_Postgis(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_TAB_1_POSTGIS, pParent)
	, m_Table(_T(""))
	, m_Encoding(_T("utf-8"))
	, m_Dbname(_T("username"))
	, m_Host(_T(""))
	, m_Port(_T(""))
	, m_User(_T(""))
	, m_Password(_T(""))
	, m_ConnectTimeout(_T("4"))
	, m_Check_Key_Field(FALSE)
	, m_Check_KeyFieldAsAttribute(TRUE)
	, m_activeEnKill(FALSE)
{

}

CTab_one_Postgis::~CTab_one_Postgis()
{
}

void CTab_one_Postgis::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TABLE_POSTGIS, m_Table);
	DDX_Check(pDX, IDC_CHECK_FIELD_POSTGIS, m_Check_Key_Field);
	DDX_Check(pDX, IDC_CHECK_FIELDASATTRIBUTE_POSTGIS, m_Check_KeyFieldAsAttribute);
	DDX_Text(pDX, IDC_EDIT_ENCODING_POSTGIS, m_Encoding);
	DDX_Text(pDX, IDC_EDIT_DBNAME_POSTGIS, m_Dbname);
	DDX_Text(pDX, IDC_EDIT_HOST_POSTGIS, m_Host);
	DDX_Text(pDX, IDC_EDIT_PORT_POSTGIS, m_Port);
	DDX_Text(pDX, IDC_EDIT_USER_POSTGIS, m_User);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_POSTGIS, m_Password);
	DDX_Text(pDX, IDC_EDIT_CONNECTTIMEOUT_POSTGIS, m_ConnectTimeout);
}


BEGIN_MESSAGE_MAP(CTab_one_Postgis, CBCGPDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_TABLE_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_FIELD_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_BN_KILLFOCUS(IDC_CHECK_FIELDASATTRIBUTE_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_ENCODING_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_DBNAME_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_HOST_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_USER_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
	ON_EN_KILLFOCUS(IDC_EDIT_CONNECTTIMEOUT_POSTGIS, &CTab_one_Postgis::OnEnKillfocusPostgis)
END_MESSAGE_MAP()

// CTab_one_Postgis message handlers



void CTab_one_Postgis::OnEnKillfocusPostgis()
{
	if (m_activeEnKill)
	{
		UpdateData();
		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pMainFrm->EnkillFocus_Datasources_Postgis();
	}
}

void CTab_one_Postgis::Reset_Value()
{
	m_Table = _T("");
	m_Encoding = _T("utf-8");
	m_Dbname = _T("username");
	m_Host = _T("");
	m_Port = _T("");
	m_Password = _T("");
	m_User = _T("");
	m_ConnectTimeout = _T("4");
	m_Check_Key_Field = FALSE;
	m_Check_KeyFieldAsAttribute = TRUE;
	UpdateData(FALSE);
}