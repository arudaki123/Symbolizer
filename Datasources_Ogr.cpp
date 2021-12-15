// Datasources_Ogr.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Datasources_Ogr.h"
#include <sstream>
#include <tinyxml2.h>

// Datasources_Ogr

IMPLEMENT_DYNCREATE(Datasources_Ogr, CBCGPFormView)

Datasources_Ogr::Datasources_Ogr()
	: CBCGPFormView(IDD_FORMVIEW_OGR_DATASOURCES)
	, m_File(_T(""))
	, m_Base(_T(""))
	, m_Encoding(_T("utf-8"))
{

}

Datasources_Ogr::~Datasources_Ogr()
{
}

void Datasources_Ogr::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_OGR, m_Default);
	DDX_Control(pDX, IDC_STATIC_RESET_OGR, m_Ctrl_Reset);
	DDX_Control(pDX, IDC_STATIC_FILE_OGR, m_Ctrl_File);
	DDX_Text(pDX, IDC_EDIT_FILE_OGR, m_File);
	DDX_Text(pDX, IDC_EDIT_BASE_OGR, m_Base);
	DDX_Text(pDX, IDC_EDIT_ENCODING_OGR, m_Encoding);
	DDX_Text(pDX, IDC_EDIT_XML_OGR, m_Script);

}

BEGIN_MESSAGE_MAP(Datasources_Ogr, CBCGPFormView)
	ON_BN_CLICKED(IDC_CHECK_DEFAULT_OGR, &Datasources_Ogr::OnBnClickedCheckDefault)
	ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_OGR, &Datasources_Ogr::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_FILE_OGR, &Datasources_Ogr::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_BASE_OGR, &Datasources_Ogr::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_ENCODING_OGR, &Datasources_Ogr::OnEnKillfocus)
	ON_STN_CLICKED(IDC_STATIC_FILE_OGR, &Datasources_Ogr::OnStnClickedStaticFileOgr)
	ON_STN_CLICKED(IDC_STATIC_RESET_OGR, &Datasources_Ogr::OnStnClickedStaticResetOgr)
END_MESSAGE_MAP()

// Datasources_Ogr message handlers

BOOL Datasources_Ogr::CreateView(CWnd* pParent, CCreateContext* pContext)
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


void Datasources_Ogr::OnStnClickedStaticFileOgr()
{
	CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files (*)|*.*||"));
	int iRet = l_fDlg.DoModal();
	m_File = l_fDlg.GetPathName();
	UpdateData(FALSE);
}

void Datasources_Ogr::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	
	HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
	m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
	// Set the icon of the button to be the system question mark icon.
	m_Ctrl_Reset.SetIcon(h_Ico);

	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize(CSize(16, 16));
	imagesWorkspace.Load(IDB_WORKSPACE);
	m_Ctrl_File.ModifyStyle(0, SS_ICON);
	m_Ctrl_File.ModifyStyle(0, SS_NOTIFY);
	m_Ctrl_File.SetIcon(imagesWorkspace.ExtractIcon(5));

	// Create the ToolTip control.
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OgrDatasources.file"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_BASE_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OgrDatasources.base"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ENCODING_OGR), CString(m_ToolTip.m_MapTooltip_Doc["OgrDatasources.encoding"].c_str()));
	
	
	OnEnKillfocus();
}

void Datasources_Ogr::OnBnClickedCheckDefault()
{
	UpdateData();

	GetDlgItem(IDC_EDIT_FILE_OGR)->EnableWindow(!m_Default);
	GetDlgItem(IDC_EDIT_BASE_OGR)->EnableWindow(!m_Default);
	GetDlgItem(IDC_EDIT_ENCODING_OGR)->EnableWindow(!m_Default);

	OnEnKillfocus();
}

std::string Datasources_Ogr::SettingsXml()
{
	UpdateData();
	//std::string result = "LineSympolizer";

	int idx = 0;
	tinyxml2::XMLDocument doc;
	auto Element = doc.NewElement("OgrDatasources");

	if (m_Default)
	{
		doc.LinkEndChild(Element);
		tinyxml2::XMLPrinter printer;
		doc.Accept(&printer);

		return std::string(printer.CStr());
	}

	// file
	if (m_File != _T(""))
		Element->SetAttribute("file", (CT2CA)m_File);

	// base
	if (m_Base != _T(""))
		Element->SetAttribute("base", (CT2CA)m_Base);

	// encoding
	if (m_Encoding != _T("utf-8"))
		Element->SetAttribute("encoding", (CT2CA)m_Encoding);

	doc.LinkEndChild(Element);
	tinyxml2::XMLPrinter printer;
	doc.Accept(&printer);

	return std::string(printer.CStr());
}

void Datasources_Ogr::SettingsXml(std::string str)
{
	tinyxml2::XMLDocument doc;
	doc.Parse((const char*)str.c_str());
	tinyxml2::XMLElement* titleElement = doc.FirstChildElement("OgrDatasources");
	if (titleElement == NULL)
		return;

	if (titleElement->FindAttribute("file"))
		m_File.SetString(CString(titleElement->Attribute("file")));

	if (titleElement->FindAttribute("base"))
		m_Base.SetString(CString(titleElement->Attribute("base")));

	if (titleElement->FindAttribute("encoding"))
		m_Encoding.SetString(CString(titleElement->Attribute("encoding")));

	UpdateData(false);
}

BOOL Datasources_Ogr::PreTranslateMessage(MSG* pMsg)
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
	return CBCGPFormView::PreTranslateMessage(pMsg);
}

void Datasources_Ogr::OnEnKillfocus()
{
	UpdateData();
	m_Script.SetString(CString(SettingsXml().c_str()));
	UpdateData(FALSE);
}

void Datasources_Ogr::OnStnClickedStaticResetOgr()
{
	m_File = _T("");
	m_Base = _T("");
	m_Encoding = _T("utf-8");

	UpdateData(FALSE);
	OnEnKillfocus();
}
