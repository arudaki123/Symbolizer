// Symbolizer_Dot.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Symbolizer_Dot.h"
#include "afxdialogex.h"
#include <vector>
#include <sstream>
#include <tinyxml2.h>


// Symbolizer_Dot

IMPLEMENT_DYNCREATE(Symbolizer_Dot, CBCGPFormView)

Symbolizer_Dot::Symbolizer_Dot()
	: CBCGPFormView(IDD_FORMVIEW_DOTSYMBOLIZER)
    , m_Default(0)
	, m_Opacity(_T("1"))
	, m_Width(_T("1"))
	, m_Height(_T("1"))
{

}

Symbolizer_Dot::~Symbolizer_Dot()
{
}

void Symbolizer_Dot::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_DOT, m_Default);
    DDX_Control(pDX, IDC_STATIC_RESET_DOT, m_Ctrl_Reset);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_DOT, m_Ctrl_Color);
	DDX_Text(pDX, IDC_EDIT_WIDTH_DOT, m_Width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_DOT, m_Height);
	DDX_Text(pDX, IDC_EDIT_OPACITY_DOT, m_Opacity);
	DDX_Control(pDX, IDC_COMBO_COMP_OP_DOT, m_Ctrl_CompOp);
	DDX_Text(pDX, IDC_EDIT_XML_DOT, m_Script);
}

BEGIN_MESSAGE_MAP(Symbolizer_Dot, CBCGPFormView)
	ON_BN_CLICKED(IDC_CHECK_DEFAULT_DOT, &Symbolizer_Dot::OnBnClickedCheckDefault)

	ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_DOT, &Symbolizer_Dot::OnEnKillfocus)
	ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_DOT, &Symbolizer_Dot::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_OPACITY_DOT, &Symbolizer_Dot::OnEnKillfocusFloat)
	ON_EN_KILLFOCUS(IDC_EDIT_WIDTH_DOT, &Symbolizer_Dot::OnEnKillfocusFloat)
	ON_EN_KILLFOCUS(IDC_EDIT_HEIGHT_DOT, &Symbolizer_Dot::OnEnKillfocusFloat)
	ON_EN_KILLFOCUS(IDC_COMBO_COMP_OP_DOT, &Symbolizer_Dot::OnEnKillfocus)
	//ON_BN_KILLFOCUS(IDC_EDIT_XML_DOT, &Symbolizer_Dot::OnEnKillfocus)

    ON_STN_CLICKED(IDC_STATIC_RESET_DOT, &Symbolizer_Dot::OnStnClickedStaticResetDot)
END_MESSAGE_MAP()

// Symbolizer_Dot message handlers


BOOL Symbolizer_Dot::CreateView(CWnd* pParent, CCreateContext* pContext)
{
	CRect rect(0, 0, 300, 300);

	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		rect, pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create Dot FormView!\n");
		return FALSE;
	}

	return TRUE;
}

void Symbolizer_Dot::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();

    HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
    m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
    // Set the icon of the button to be the system question mark icon.
    m_Ctrl_Reset.SetIcon(h_Ico);

    // FILL
    m_Ctrl_Color.SetColor(RGB(128, 128, 128));

    // Comp op
    m_Ctrl_CompOp.AddString(_T("clear"));
    m_Ctrl_CompOp.AddString(_T("src"));
    m_Ctrl_CompOp.AddString(_T("dst"));
    m_Ctrl_CompOp.AddString(_T("src-over"));
    m_Ctrl_CompOp.AddString(_T("dst-over"));
    m_Ctrl_CompOp.AddString(_T("src-in"));
    m_Ctrl_CompOp.AddString(_T("dst-in"));
    m_Ctrl_CompOp.AddString(_T("src-out"));
    m_Ctrl_CompOp.AddString(_T("dst-out"));
    m_Ctrl_CompOp.AddString(_T("src-atop"));
    m_Ctrl_CompOp.AddString(_T("dst-atop"));
    m_Ctrl_CompOp.AddString(_T("xor"));
    m_Ctrl_CompOp.AddString(_T("plus"));
    m_Ctrl_CompOp.AddString(_T("minus"));
    m_Ctrl_CompOp.AddString(_T("multiply"));
    m_Ctrl_CompOp.AddString(_T("divide"));
    m_Ctrl_CompOp.AddString(_T("screen"));
    m_Ctrl_CompOp.AddString(_T("overlay"));
    m_Ctrl_CompOp.AddString(_T("darken"));
    m_Ctrl_CompOp.AddString(_T("lighten"));
    m_Ctrl_CompOp.AddString(_T("color-dodge"));
    m_Ctrl_CompOp.AddString(_T("color-burn"));
    m_Ctrl_CompOp.AddString(_T("linear-dodge"));
    m_Ctrl_CompOp.AddString(_T("linear-burn"));
    m_Ctrl_CompOp.AddString(_T("hard-light"));
    m_Ctrl_CompOp.AddString(_T("soft-light"));
    m_Ctrl_CompOp.AddString(_T("difference"));
    m_Ctrl_CompOp.AddString(_T("exclusion"));
    m_Ctrl_CompOp.AddString(_T("contrast"));
    m_Ctrl_CompOp.AddString(_T("invert"));
    m_Ctrl_CompOp.AddString(_T("invert-rgb"));
    m_Ctrl_CompOp.AddString(_T("grain-merge"));
    m_Ctrl_CompOp.AddString(_T("grain-extract"));
    m_Ctrl_CompOp.AddString(_T("hue"));
    m_Ctrl_CompOp.AddString(_T("saturation"));
    m_Ctrl_CompOp.AddString(_T("color"));
    m_Ctrl_CompOp.AddString(_T("value"));
    m_Ctrl_CompOp.SetCurSel(34);


    // Create the ToolTip control.
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_ToolTip.SetParams(&params);
    //m_ToolTip.initDot();

    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.default"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.fill"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.opacity"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.width"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_HEIGHT_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.height"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_DOT), CString(m_ToolTip.m_MapTooltip_Doc["dotsymbolizer.comp-op"].c_str()));

    // TODO: Use one of the following forms to add controls:
   /* m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_DOT), _T("Allows omitting a dot symbolizer rule or emitting it with default values."));
    m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_DOT), _T("The color of the area of the dot."));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_DOT), _T("The overall opacity of the dot."));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_DOT), _T("The width of the dot in pixels."));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_HEIGHT_DOT), _T("The height of the dot in pixels."));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_DOT), _T("Composite operation. This defines how this layer "
                                                        "\nshould behave relative to layers atop or below it."));*/

    // Script
    //m_Script.SetString(CString(SettingsXml().c_str()));
    OnEnKillfocus();
}


void Symbolizer_Dot::OnBnClickedCheckDefault()
{
    UpdateData();

    GetDlgItem(IDC_MFCCOLORBUTTON_DOT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OPACITY_DOT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_WIDTH_DOT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_HEIGHT_DOT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_COMP_OP_DOT)->EnableWindow(!m_Default);
    
    
    OnEnKillfocus();
}

std::string Symbolizer_Dot::SettingsXml()
{
    UpdateData();

    int idx = 0;
    tinyxml2::XMLDocument doc;
    auto Element = doc.NewElement("DotSympolizer");

    if (m_Default)
    {
        doc.LinkEndChild(Element);
        tinyxml2::XMLPrinter printer;
        doc.Accept(&printer);

        return std::string(printer.CStr());
    }

    //  fill
    COLORREF dColor = m_Ctrl_Color.GetColor();
    if (dColor != RGB(128, 128, 128))
    {
        CString sColor;
        sColor.Format(_T("#%02X%02X%02X"), GetRValue(dColor), GetGValue(dColor), GetBValue(dColor));
        Element->SetAttribute("fill", (CT2CA)sColor);
    }

    // width
    if (m_Width != _T("1"))
        Element->SetAttribute("width", (CT2CA)m_Width);

    // height
    if (m_Height != _T("1"))
        Element->SetAttribute("height", (CT2CA)m_Height);

    // stroke-opacity
    if (m_Opacity != _T("1"))
        Element->SetAttribute("opacity", (CT2CA)m_Opacity);

    // comp-op
    CString CompOp;
    idx = m_Ctrl_CompOp.GetCurSel();
    m_Ctrl_CompOp.GetLBText(idx, CompOp);
    if (CompOp != _T("src-over"))
        Element->SetAttribute("comp-op", (CT2CA)CompOp);

    doc.LinkEndChild(Element);
    tinyxml2::XMLPrinter printer;
    doc.Accept(&printer);

    return std::string(printer.CStr());
}

void Symbolizer_Dot::SettingsXml(std::string str)
{
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*)str.c_str());
    tinyxml2::XMLElement* titleElement = doc.FirstChildElement("DotSympolizer");
    if (titleElement == NULL)
        return;

    if (titleElement->FindAttribute("fill"))
        m_Ctrl_Color.SetColor(GetColor(titleElement->Attribute("fill")));

    if (titleElement->FindAttribute("width"))
        m_Width.SetString(CString(titleElement->Attribute("width")));

    if (titleElement->FindAttribute("height"))
        m_Height.SetString(CString(titleElement->Attribute("height")));

    if (titleElement->FindAttribute("opacity"))
        m_Opacity = CString(titleElement->Attribute("opacity"));

    if (titleElement->FindAttribute("comp-op"))
        m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, CString(titleElement->Attribute("comp-op"))));


    UpdateData(false);
}

COLORREF Symbolizer_Dot::GetColor(std::string value)
{
    LPCSTR pszTmp = value.c_str();
    pszTmp++;
    COLORREF crefColor = strtol(pszTmp, NULL, 16);
    INT nR = GetRValue(crefColor);
    INT nG = GetGValue(crefColor);
    INT nB = GetBValue(crefColor);
    return RGB(nB, nG, nR);
}

BOOL Symbolizer_Dot::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
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

void Symbolizer_Dot::OnEnKillfocus()
{
    UpdateData();
    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Dot::OnEnKillfocusFloat()
{
    UpdateData();
    if (!m_ToolTip.isFloat(m_Opacity))
    {
        m_Opacity = _T("1");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OPACITY_DOT)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Width))
    {
        m_Width = _T("1");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_WIDTH_DOT)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Height))
    {
        m_Height.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_HEIGHT_DOT)->SetFocus();
    }

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Dot::OnStnClickedStaticResetDot()
{
    //  fill
    m_Ctrl_Color.SetColor(RGB(128, 128, 128));
   
    // width
    m_Width = _T("1");

    // height
    m_Height = _T("1");

    // stroke-opacity
    m_Opacity = _T("1");

    // comp-op
    m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, _T("src-over")));

    UpdateData(FALSE);
    OnEnKillfocus();
}
