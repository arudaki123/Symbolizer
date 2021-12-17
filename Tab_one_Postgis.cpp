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

BOOL CTab_one_Postgis::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Create the ToolTip control.
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_TABLE_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.table"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_FIELD_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.key_field"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_FIELDASATTRIBUTE_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.key_field_as_attribute"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ENCODING_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.encoding"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DBNAME_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.dbname"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_HOST_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.host"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_PORT_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.port"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_USER_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.port"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_PASSWORD_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.password"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CONNECTTIMEOUT_POSTGIS), CString(m_ToolTip.m_MapTooltip_Doc["postgisdatasources.connect_timeout"].c_str()));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTab_one_Postgis::PreTranslateMessage(MSG* pMsg)
{
	//TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		m_ToolTip.RelayEvent(pMsg);
		break;
	}
	return CBCGPDialog::PreTranslateMessage(pMsg);
}