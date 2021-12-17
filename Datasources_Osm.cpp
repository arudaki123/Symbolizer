// Datasources_Osm.cpp : implementation file
//
#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Datasources_Osm.h"

// Datasources_Osm

IMPLEMENT_DYNCREATE(Datasources_Osm, CBCGPFormView)

Datasources_Osm::Datasources_Osm()
	: CBCGPFormView(IDD_FORMVIEW_OSM_DATASOURCES)
	, m_File(_T(""))
	, m_Base(_T(""))
	, m_Encoding(_T("utf-8"))
{

}

Datasources_Osm::~Datasources_Osm()
{
}

void Datasources_Osm::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_OSM, m_Default);
	DDX_Control(pDX, IDC_STATIC_RESET_OSM, m_Ctrl_Reset);
	DDX_Control(pDX, IDC_STATIC_FILE_OSM, m_Ctrl_File);
	DDX_Text(pDX, IDC_EDIT_FILE_OSM, m_File);
	DDX_Text(pDX, IDC_EDIT_BASE_OSM, m_Base);
	DDX_Text(pDX, IDC_EDIT_ENCODING_OSM, m_Encoding);
	DDX_Text(pDX, IDC_EDIT_XML_OSM, m_Script);
}

BEGIN_MESSAGE_MAP(Datasources_Osm, CBCGPFormView)
	ON_BN_CLICKED(IDC_CHECK_DEFAULT_OSM, &Datasources_Osm::OnBnClickedCheckDefault)
	ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_OSM, &Datasources_Osm::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_FILE_OSM, &Datasources_Osm::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_BASE_OSM, &Datasources_Osm::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_ENCODING_OSM, &Datasources_Osm::OnEnKillfocus)
	ON_STN_CLICKED(IDC_STATIC_FILE_OSM, &Datasources_Osm::OnStnClickedStaticFileOsm)
	ON_STN_CLICKED(IDC_STATIC_RESET_OSM, &Datasources_Osm::OnStnClickedStaticResetOsm)
END_MESSAGE_MAP()

// Datasources_Osm message handlers


BOOL Datasources_Osm::CreateView(CWnd* pParent, CCreateContext* pContext)
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


void Datasources_Osm::OnStnClickedStaticFileOsm()
{
	CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files (*)|*.*||"));
	int iRet = l_fDlg.DoModal();
	m_File = l_fDlg.GetPathName();
	UpdateData(FALSE);
}

void Datasources_Osm::OnInitialUpdate()
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

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_OSM), CString(m_ToolTip.m_MapTooltip_Doc["osmdatasources.file"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_BASE_OSM), CString(m_ToolTip.m_MapTooltip_Doc["osmdatasources.base"].c_str()));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ENCODING_OSM), CString(m_ToolTip.m_MapTooltip_Doc["osmdatasources.encoding"].c_str()));


	OnEnKillfocus();
}

std::string Datasources_Osm::SettingsXml()
{
	UpdateData();
	tinyxml2::XMLDocument doc;
	auto pTop = doc.RootElement();
	auto pDatasources = doc.NewElement("Datasources");
	doc.InsertFirstChild(pDatasources);

	auto Element = doc.NewElement("Paramenter");
	Element->SetAttribute("name", "type");
	tinyxml2::XMLText* text = doc.NewText("osm");
	text->SetCData(true);
	Element->InsertEndChild(text);
	pDatasources->InsertEndChild(Element);

	if (m_Default)
	{
		tinyxml2::XMLPrinter printer;
		doc.Accept(&printer);

		return std::string(printer.CStr());
	}

	// file
	if (m_File != _T(""))
	{
		auto FileElement = doc.NewElement("Paramenter");
		FileElement->SetAttribute("name", "file");
		text = doc.NewText((CT2CA)m_File);
		text->SetCData(true);
		FileElement->InsertEndChild(text);
		pDatasources->LinkEndChild(FileElement);
	}

	// base
	if (m_Base != _T(""))
	{
		auto BaseElement = doc.NewElement("Paramenter");
		BaseElement->SetAttribute("name", "base");
		text = doc.NewText((CT2CA)m_Base);
		text->SetCData(true);
		BaseElement->InsertEndChild(text);
		pDatasources->LinkEndChild(BaseElement);
	}

	// encoding
	if (m_Encoding != _T("utf-8"))
	{
		auto EncodingElement = doc.NewElement("Paramenter");
		EncodingElement->SetAttribute("name", "encoding");
		text = doc.NewText((CT2CA)m_Encoding);
		text->SetCData(true);
		EncodingElement->InsertEndChild(text);
		pDatasources->LinkEndChild(EncodingElement);
	}

	tinyxml2::XMLPrinter printer;
	doc.Accept(&printer);

	doc.SaveFile("dbscript.txt");
	std::fstream fs;
	fs.open("dbscript.txt", std::fstream::in | std::fstream::binary);
	return std::string(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
	//return std::string(printer.CStr());
}

void Datasources_Osm::OnBnClickedCheckDefault()
{
	UpdateData();

	GetDlgItem(IDC_EDIT_FILE_OGR)->EnableWindow(!m_Default);
	GetDlgItem(IDC_EDIT_BASE_OGR)->EnableWindow(!m_Default);
	GetDlgItem(IDC_EDIT_ENCODING_OGR)->EnableWindow(!m_Default);

	OnEnKillfocus();
}

void Datasources_Osm::SettingsXml(std::string str)
{
	tinyxml2::XMLDocument doc;
	doc.Parse((const char*)str.c_str());
	auto titleElement = doc.FirstChildElement("Datasource");
	CString name;
	auto Element = titleElement->FirstChildElement("Paramenter");
	name = CString(Element->Attribute("name"));
	if (name == _T("type") && CString(Element->GetText()) == _T("osm"))
	{
		Element = Element->NextSiblingElement("Paramenter");
		while (Element)
		{
			if (Element->FindAttribute("name"))
			{
				name = CString(Element->Attribute("name"));
				if (name == _T("file"))
					m_File.SetString(CString(Element->GetText()));
				if (name == _T("base"))
					m_Base.SetString(CString(Element->GetText()));
				if (name == _T("encoding"))
					m_Encoding.SetString(CString(Element->GetText()));
			}
			Element = Element->NextSiblingElement("Paramenter");
		}
	}

	UpdateData(false);
}

BOOL Datasources_Osm::PreTranslateMessage(MSG* pMsg)
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

void Datasources_Osm::OnEnKillfocus()
{
	UpdateData();
	m_Script.SetString(CString(SettingsXml().c_str()));
	UpdateData(FALSE);
}

void Datasources_Osm::OnStnClickedStaticResetOsm()
{
	m_File = _T("");
	m_Base = _T("");
	m_Encoding = _T("utf-8");

	UpdateData(FALSE);
	OnEnKillfocus();
}
