// Datasources_Python.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Datasources_Python.h"


// Datasources_Python

IMPLEMENT_DYNCREATE(Datasources_Python, CBCGPFormView)

Datasources_Python::Datasources_Python()
	: CBCGPFormView(IDD_FORMVIEW_PYTHON_DATASOURCES)
	, m_Encoding(_T("utf-8"))
{
}

Datasources_Python::~Datasources_Python()
{
}

void Datasources_Python::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_PYTHON, m_Default);
	DDX_Control(pDX, IDC_STATIC_RESET_PYTHON, m_Ctrl_Reset);
	DDX_Text(pDX, IDC_EDIT_ENCODING_PYTHON, m_Encoding);
	DDX_Text(pDX, IDC_EDIT_XML_PYTHON, m_Script);
}

BEGIN_MESSAGE_MAP(Datasources_Python, CBCGPFormView)
	ON_BN_CLICKED(IDC_CHECK_DEFAULT_PYTHON, &Datasources_Python::OnBnClickedCheckDefault)
	ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_PYTHON, &Datasources_Python::OnEnKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_ENCODING_PYTHON, &Datasources_Python::OnEnKillfocus)
	ON_STN_CLICKED(IDC_STATIC_RESET_PYTHON, &Datasources_Python::OnStnClickedStaticResetPython)
END_MESSAGE_MAP()

// Datasources_Python message handlers

BOOL Datasources_Python::CreateView(CWnd* pParent, CCreateContext* pContext)
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

void Datasources_Python::OnStnClickedStaticResetPython()
{
	m_Encoding = _T("utf-8");

	UpdateData(FALSE);
	OnEnKillfocus();
}

void Datasources_Python::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();


	HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
	m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
	// Set the icon of the button to be the system question mark icon.
	m_Ctrl_Reset.SetIcon(h_Ico);

	// Create the ToolTip control.
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ENCODING_PYTHON), CString(m_ToolTip.m_MapTooltip_Doc["pythondatasources.encoding"].c_str()));


	OnEnKillfocus();
}

void Datasources_Python::OnBnClickedCheckDefault()
{
	UpdateData();

	GetDlgItem(IDC_EDIT_ENCODING_PYTHON)->EnableWindow(!m_Default);

	OnEnKillfocus();
}

std::string Datasources_Python::SettingsXml()
{
	UpdateData();
	tinyxml2::XMLDocument doc;
	auto pTop = doc.RootElement();
	auto pDatasources = doc.NewElement("Datasources");
	doc.InsertFirstChild(pDatasources);

	auto Element = doc.NewElement("Paramenter");
	Element->SetAttribute("name", "type");
	tinyxml2::XMLText* text = doc.NewText("python");
	text->SetCData(true);
	Element->InsertEndChild(text);
	pDatasources->InsertEndChild(Element);

	if (m_Default)
	{
		tinyxml2::XMLPrinter printer;
		doc.Accept(&printer);

		return std::string(printer.CStr());
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

void Datasources_Python::SettingsXml(std::string str)
{
	tinyxml2::XMLDocument doc;
	doc.Parse((const char*)str.c_str());
	auto titleElement = doc.FirstChildElement("Datasource");
	CString name;
	auto Element = titleElement->FirstChildElement("Paramenter");
	name = CString(Element->Attribute("name"));
	if (name == _T("type") && CString(Element->GetText()) == _T("python"))
	{
		Element = Element->NextSiblingElement("Paramenter");
		while (Element)
		{
			if (CString(Element->Attribute("name")) == _T("encoding"))
				m_Encoding.SetString(CString(Element->GetText()));
			Element = Element->NextSiblingElement("Paramenter");
		}
	}

	UpdateData(false);
}

BOOL Datasources_Python::PreTranslateMessage(MSG* pMsg)
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

void Datasources_Python::OnEnKillfocus()
{
	UpdateData();
	m_Script.SetString(CString(SettingsXml().c_str()));
	UpdateData(FALSE);
}