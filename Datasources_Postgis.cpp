// Datasources_Postgis.cpp : implementation file
//
#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Datasources_Postgis.h"
#include <sstream>
#include <tinyxml2.h>
#include "Tab_one_Postgis.h"
#include "Tab_two_Postgis.h"

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
	tinyxml2::XMLDocument doc;
	auto pTop = doc.RootElement();
	auto pDatasources = doc.NewElement("Datasources");
	doc.InsertFirstChild(pDatasources);

	auto Element = doc.NewElement("Paramenter");
	Element->SetAttribute("name", "type");
	tinyxml2::XMLText* text = doc.NewText("postgis");
	text->SetCData(true);
	Element->InsertEndChild(text);
	pDatasources->InsertEndChild(Element);

	if (m_Default)
	{
		tinyxml2::XMLPrinter printer;
		doc.Accept(&printer);

		return std::string(printer.CStr());
	}

	CTab_one_Postgis* Tab = (CTab_one_Postgis*)m_MytabCtrl.m_tabPages[0];

	// table
	if (Tab->m_Table != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "table");
		text = doc.NewText((CT2CA)Tab->m_Table);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// key_field
	if (Tab->m_Check_Key_Field)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "key_field");
		text = doc.NewText(Tab->m_Check_Key_Field ? "TRUE":"FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// key_field_as_attribute
	if (!Tab->m_Check_KeyFieldAsAttribute)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "key_field_as_attribute");
		text = doc.NewText(Tab->m_Check_KeyFieldAsAttribute ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// encoding
	if (Tab->m_Encoding != _T("utf-8"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "key_field_as_attribute");
		text = doc.NewText((CT2CA)Tab->m_Encoding);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// dbname
	if (Tab->m_Dbname != _T("username"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "dbname");
		text = doc.NewText((CT2CA)Tab->m_Dbname);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// host
	if (Tab->m_Host != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "host");
		text = doc.NewText((CT2CA)Tab->m_Host);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// password
	if (Tab->m_Password != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "password");
		text = doc.NewText((CT2CA)Tab->m_Password);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// password
	if (Tab->m_Password != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "password");
		text = doc.NewText((CT2CA)Tab->m_Password);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}
	// password
	if (Tab->m_Password != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "password");
		text = doc.NewText((CT2CA)Tab->m_Password);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// port
	if (Tab->m_Port != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "port");
		text = doc.NewText((CT2CA)Tab->m_Port);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// user
	if (Tab->m_User != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "user");
		text = doc.NewText((CT2CA)Tab->m_User);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// connect_timeout
	if (Tab->m_ConnectTimeout != _T("4"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "connect_timeout");
		text = doc.NewText((CT2CA)Tab->m_ConnectTimeout);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	CTab_two_Postgis* Tab2 = (CTab_two_Postgis*)m_MytabCtrl.m_tabPages[1];

	// schema
	if (Tab2->m_Schema != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "schema");
		text = doc.NewText((CT2CA)Tab2->m_Schema);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// extent
	if (Tab2->m_Extent != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "extent");
		text = doc.NewText((CT2CA)Tab2->m_Extent);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// estimate_extent
	if (Tab2->m_Check_EstimateExtent)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "estimate_extent");
		text = doc.NewText(Tab2->m_Check_EstimateExtent ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// geometry_table
	if (Tab2->m_GeometryTable != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "geometry_table");
		text = doc.NewText((CT2CA)Tab2->m_GeometryTable);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// geometry_field
	if (Tab2->m_GeometryField != _T(""))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "geometry_field");
		text = doc.NewText((CT2CA)Tab2->m_GeometryField);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// cursor_size
	if (Tab2->m_CursorSize != _T("0"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "cursor_size");
		text = doc.NewText((CT2CA)Tab2->m_CursorSize);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// row_limit
	if (Tab2->m_RowLimit != _T("0"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "row_limit");
		text = doc.NewText((CT2CA)Tab2->m_RowLimit);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// srid
	if (Tab2->m_Srid != _T("0"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "srid");
		text = doc.NewText((CT2CA)Tab2->m_Srid);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// initial_size
	if (Tab2->m_InitialSize != _T("1"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "initial_size");
		text = doc.NewText((CT2CA)Tab2->m_InitialSize);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// max_size
	if (Tab2->m_MaxSize != _T("10"))
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "max_size");
		text = doc.NewText((CT2CA)Tab2->m_MaxSize);
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// simplify_geometries
	if (Tab2->m_Check_SimplityGeometries)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "simplify_geometries");
		text = doc.NewText(Tab2->m_Check_SimplityGeometries ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// autodetect_key_field
	if (Tab2->m_Check_AutodetectKeyField)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "autodetect_key_field");
		text = doc.NewText(Tab2->m_Check_AutodetectKeyField ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}

	// persist_connection
	if (!Tab2->m_Check_PersistConnection)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "persist_connection");
		text = doc.NewText(Tab2->m_Check_PersistConnection ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}
	// extent_from_subquery
	if (Tab2->m_Check_ExtentFromSubquery)
	{
		Element = doc.NewElement("Paramenter");
		Element->SetAttribute("name", "extent_from_subquery");
		text = doc.NewText(Tab2->m_Check_ExtentFromSubquery ? "TRUE" : "FALSE");
		text->SetCData(true);
		Element->InsertEndChild(text);
		pDatasources->LinkEndChild(Element);
	}
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
