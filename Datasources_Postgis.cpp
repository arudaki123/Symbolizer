// Datasources_Postgis.cpp : implementation file
//
#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Datasources_Postgis.h"
#include <sstream>
#include <tinyxml2.h>

// Datasources_Postgis

IMPLEMENT_DYNCREATE(Datasources_Postgis, CBCGPFormView)

Datasources_Postgis::Datasources_Postgis()
	: CBCGPFormView(IDD_FORMVIEW_POSTGIS_DATASOURCES)
{

}

Datasources_Postgis::~Datasources_Postgis()
{
}

void Datasources_Postgis::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_POSTGIS, m_MytabCtrl);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_POSTGIS, m_Default);
	DDX_Control(pDX, IDC_STATIC_RESET_POSTGIS, m_Ctrl_Reset);
	DDX_Text(pDX, IDC_EDIT_XML_POSTGIS, m_Script);
}

BEGIN_MESSAGE_MAP(Datasources_Postgis, CBCGPFormView)
	ON_BN_CLICKED(IDC_CHECK_DEFAULT_POSTGIS, &Datasources_Postgis::OnBnClickedCheckDefault)
	ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_POSTGIS, &Datasources_Postgis::OnEnKillfocus)
	ON_STN_CLICKED(IDC_STATIC_RESET_POSTGIS, &Datasources_Postgis::OnStnClickedStaticResetPostgis)
END_MESSAGE_MAP()


// Datasources_Postgis message handlers

BOOL Datasources_Postgis::CreateView(CWnd* pParent, CCreateContext* pContext)
{
	CRect rect(0, 0, 300, 300);

	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		rect, pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create CMyFormView!\n");
		return FALSE;
	}

	return TRUE;
}

void Datasources_Postgis::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();


	HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
	m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
	// Set the icon of the button to be the system question mark icon.
	m_Ctrl_Reset.SetIcon(h_Ico);

	m_MytabCtrl.InsertItem(0, _T("Paramenter"));
	m_MytabCtrl.InsertItem(1, _T("Connect postgis"));
	
	m_MytabCtrl.Init();

	// Create the ToolTip control.
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);

	//m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OsmDatasources.file"].c_str()));
	//m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_BASE_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OsmDatasources.base"].c_str()));
	//m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ENCODING_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OsmDatasources.encoding"].c_str()));


	OnEnKillfocus();
}

void Datasources_Postgis::OnBnClickedCheckDefault()
{
	UpdateData();

	GetDlgItem(IDC_TAB_POSTGIS)->EnableWindow(!m_Default);

	OnEnKillfocus();
}

std::string Datasources_Postgis::SettingsXml()
{
	UpdateData();
	//std::string result = "LineSympolizer";

	int idx = 0;
	tinyxml2::XMLDocument doc;
	auto Element = doc.NewElement("PostgisDatasources");

	if (m_Default)
	{
		doc.LinkEndChild(Element);
		tinyxml2::XMLPrinter printer;
		doc.Accept(&printer);

		return std::string(printer.CStr());
	}

	// file
	//if (m_File != _T(""))
	//	Element->SetAttribute("file", (CT2CA)m_File);

	//// base
	//if (m_Base != _T(""))
	//	Element->SetAttribute("base", (CT2CA)m_Base);

	//// encoding
	//if (m_Encoding != _T("utf-8"))
	//	Element->SetAttribute("encoding", (CT2CA)m_Encoding);

	doc.LinkEndChild(Element);
	tinyxml2::XMLPrinter printer;
	doc.Accept(&printer);

	return std::string(printer.CStr());
}

void Datasources_Postgis::SettingsXml(std::string str)
{
	tinyxml2::XMLDocument doc;
	doc.Parse((const char*)str.c_str());
	tinyxml2::XMLElement* titleElement = doc.FirstChildElement("PostgisDatasources");
	if (titleElement == NULL)
		return;

	/*if (titleElement->FindAttribute("file"))
		m_File.SetString(CString(titleElement->Attribute("file")));

	if (titleElement->FindAttribute("base"))
		m_Base.SetString(CString(titleElement->Attribute("base")));

	if (titleElement->FindAttribute("encoding"))
		m_Encoding.SetString(CString(titleElement->Attribute("encoding")));*/

	UpdateData(false);
}

BOOL Datasources_Postgis::PreTranslateMessage(MSG* pMsg)
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
		m_MytabCtrl.TurnOnEnKill();
		break;
	}
	return CBCGPFormView::PreTranslateMessage(pMsg);
}

void Datasources_Postgis::OnEnKillfocus()
{
	UpdateData();
	m_Script.SetString(CString(SettingsXml().c_str()));
	UpdateData(FALSE);
}

void Datasources_Postgis::EnKillfocus()
{
	UpdateData();
	m_Script.SetString(CString(SettingsXml().c_str()));
	UpdateData(FALSE);
}

void Datasources_Postgis::OnStnClickedStaticResetPostgis()
{
	
}
