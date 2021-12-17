// Symbolizer_Point.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "Symbolizer_Point.h"
#include "afxdialogex.h"
#include <vector>
#include <sstream>
#include <tinyxml2.h>


// Symbolizer_Point

IMPLEMENT_DYNCREATE(Symbolizer_Point, CBCGPFormView)

Symbolizer_Point::Symbolizer_Point()
	: CBCGPFormView(IDD_FORMVIEW_POINTSYMBOLIZER)
    , m_Opacity(_T("1"))
    , m_File(_T(""))
    , m_Ignoreplacement(0)
    , m_Allowoverlap(0)
    , m_Transform(_T(""))
{

}

Symbolizer_Point::~Symbolizer_Point()
{
}

void Symbolizer_Point::DoDataExchange(CDataExchange* pDX)
{
    CBCGPFormView::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_DEFAULT_POINT, m_Default);
    DDX_Control(pDX, IDC_STATIC_RESET_POINT, m_Ctrl_Reset);
    DDX_Text(pDX, IDC_EDIT_FILE_POINT, m_File);
    DDX_Check(pDX, IDC_CHECK_IGNORE_POINT, m_Ignoreplacement);
    DDX_Check(pDX, IDC_CHECK_ALLOWOVERLAP_POINT, m_Allowoverlap);
    DDX_Text(pDX, IDC_EDIT_OPACITY_POINT, m_Opacity);
    DDX_Control(pDX, IDC_STATIC_FILE_POINT, m_Ctrl_File);
    DDX_Control(pDX, IDC_COMBO_PLACEMENT_POINT, m_Ctrl_Placement);
    DDX_Text(pDX, IDC_EDIT_TRANSFORM_POINT, m_Transform);
    DDX_Control(pDX, IDC_COMBO_COMP_OP_POINT, m_Ctrl_CompOp);
    DDX_Text(pDX, IDC_EDIT_XML_POINT, m_Script);
}

BEGIN_MESSAGE_MAP(Symbolizer_Point, CBCGPFormView)
    ON_BN_CLICKED(IDC_CHECK_DEFAULT_POINT, &Symbolizer_Point::OnBnClickedCheckDefault)

    ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_FILE_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_BN_KILLFOCUS(IDC_CHECK_IGNORE_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_BN_KILLFOCUS(IDC_CHECK_ALLOWOVERLAP_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_OPACITY_POINT, &Symbolizer_Point::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_STATIC_FILE_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_PLACEMENT_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_TRANSFORM_POINT, &Symbolizer_Point::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_COMP_OP_POINT, &Symbolizer_Point::OnEnKillfocus)


    ON_STN_CLICKED(IDC_STATIC_FILE_POINT, &Symbolizer_Point::OnBnClickedButtonFile)
    ON_BN_CLICKED(IDC_CHECK_IGNORE_POINT, &Symbolizer_Point::OnBnClickedCheckIgnorePoint)
    ON_BN_CLICKED(IDC_CHECK_ALLOWOVERLAP_POINT, &Symbolizer_Point::OnBnClickedCheckAllowoverlapPoint)
    ON_STN_CLICKED(IDC_STATIC_RESET_POINT, &Symbolizer_Point::OnStnClickedStaticResetPoint)
END_MESSAGE_MAP()



// Symbolizer_Point message handlers


BOOL Symbolizer_Point::CreateView(CWnd* pParent, CCreateContext* pContext)
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

void Symbolizer_Point::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();
    {
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

        // Placement
        m_Ctrl_Placement.AddString(_T("centroid"));
        m_Ctrl_Placement.AddString(_T("interior"));
        m_Ctrl_Placement.SetCurSel(0);

        // Transform
       /* m_Ctrl_Transform.AddString(_T("matrix(v00, v01, v10, v11, v20, v21)"));
        m_Ctrl_Transform.AddString(_T("translate(x, y)"));
        m_Ctrl_Transform.AddString(_T("scale(x, y)"));
        m_Ctrl_Transform.AddString(_T("rotate(x,y,z)"));
        m_Ctrl_Transform.AddString(_T("skewX(x)"));
        m_Ctrl_Transform.AddString(_T("skewY(y)"));*/

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
    }

    // Create the ToolTip control.
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);


    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_ToolTip.SetParams(&params);
    
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.default"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.file"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_STATIC_FILE_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.file"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_ALLOWOVERLAP_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.allow-overlap"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_IGNORE_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.ignore-placement"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.opacity"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_PLACEMENT_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.placement"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_TRANSFORM_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.transform"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_POINT), CString(m_ToolTip.m_MapTooltip_Doc["pointsymbolizer.comp-op"].c_str()));

    //// TODO: Use one of the following forms to add controls:
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_POINT), _T("Allows omitting a line symbolizer rule or emitting it with default values."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_POINT), _T("Image file to represent a point. Accepted formats: svg, jpg, png, tiff, and webp."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_BUTTON_FILE_POINT), _T("Image file to represent a point. Accepted formats: svg, jpg, png, tiff, and webp."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_IGNORE_POINT), _T("Control whether the placement of the feature will prevent the placement of other features."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_ALLOWOVERLAP_POINT), _T("Control whether overlapping points are shown or hidden."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_POINT), _T("A value from 0 to 1 to control the opacity of the point."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_PLACEMENT_POINT), _T("Control how this point should be placed. Centroid calculates the geometric center of a polygon, "
    //                                                            "\nwhich can be outside of it, while interior always places inside of a polygon."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_TRANSFORM_POINT), _T("Transform point instance with specified function. Ignores map scale factor."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_POINT), _T("Composite operation. This defines how this symbolizer "
    //                                                         "\nshould behave relative to symbolizers atop or below it."));


    OnEnKillfocus();
}

BOOL Symbolizer_Point::PreTranslateMessage(MSG* pMsg)
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

void Symbolizer_Point::OnEnKillfocus()
{

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Point::OnBnClickedCheckDefault()
{
    UpdateData();

    GetDlgItem(IDC_EDIT_FILE_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_STATIC_FILE_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_CHECK_IGNORE_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_CHECK_ALLOWOVERLAP_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_CHECK_ALLOWOVERLAP_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OPACITY_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_PLACEMENT_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_TRANSFORM_POINT)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_COMP_OP_POINT)->EnableWindow(!m_Default);

    OnEnKillfocus();
}

std::string Symbolizer_Point::SettingsXml()
{
    UpdateData();

    int idx = 0;
    tinyxml2::XMLDocument doc;
    auto Element = doc.NewElement("PointSympolizer");

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

    // allow-overlap
    if (m_Allowoverlap)
        Element->SetAttribute("allow-overlap", true);

    // ignore-placement
    if (m_Ignoreplacement)
        Element->SetAttribute("ignore-placement", true);

    // opacity
    if (m_Opacity != _T("1"))
        Element->SetAttribute("opacity", (CT2CA)m_Opacity);

    // placement
    CString Placement;
    idx = m_Ctrl_Placement.GetCurSel();
    m_Ctrl_Placement.GetLBText(idx, Placement);
    if (Placement != _T("centroid"))
        Element->SetAttribute("placement", (CT2CA)Placement);
    
    // geometry-transform
    //m_Ctrl_Transform.GetLBText(idx, Transform);
    if (m_Transform != _T(""))
        Element->SetAttribute("transform", (CT2CA)m_Transform);

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

void Symbolizer_Point::SettingsXml(std::string str)
{
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*)str.c_str());
    tinyxml2::XMLElement* titleElement = doc.FirstChildElement("LinepatternSympolizer");
    if (titleElement == NULL)
        return;

    if (titleElement->FindAttribute("allow-overlap"))
        m_Allowoverlap = CString(titleElement->Attribute("allow-overlap")) == _T("true") ? TRUE:FALSE;

    if (titleElement->FindAttribute("ignore-placement"))
        m_Ignoreplacement = CString(titleElement->Attribute("ignore-placement")) == _T("true") ? TRUE : FALSE;

    if (titleElement->FindAttribute("file"))
        m_File.SetString(CString(titleElement->Attribute("file")));

    if (titleElement->FindAttribute("opacity"))
        m_Opacity = CString(titleElement->Attribute("opacity"));

    if (titleElement->FindAttribute("placement"))
        m_Ctrl_Placement.SetCurSel(m_Ctrl_Placement.FindStringExact(0, CString(titleElement->Attribute("placement"))));

    if (titleElement->FindAttribute("transform"))
        m_Transform.SetString(CString(titleElement->Attribute("transform")));

    if (titleElement->FindAttribute("comp-op"))
        m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, CString(titleElement->Attribute("comp-op"))));


    UpdateData(false);
}

void Symbolizer_Point::OnBnClickedButtonFile()
{
    CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files (*)|*.*||"));
    int iRet = l_fDlg.DoModal();
    m_File = l_fDlg.GetPathName();
    UpdateData(FALSE);
}


void Symbolizer_Point::OnBnClickedCheckIgnorePoint()
{
    OnEnKillfocus();
}


void Symbolizer_Point::OnBnClickedCheckAllowoverlapPoint()
{
    OnEnKillfocus();
}

void Symbolizer_Point::OnEnKillfocusFloat()
{
    UpdateData();
    if (!m_ToolTip.isFloat(m_Opacity))
    {
        m_Opacity.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OPACITY_POINT)->SetFocus();
    }

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Point::OnStnClickedStaticResetPoint()
{
    // file
    m_File = _T("");
      
    // allow-overlap
    m_Allowoverlap = FALSE;

    // ignore-placement
    m_Ignoreplacement = FALSE;

    // opacity
    m_Opacity = _T("1");

    // placement
    m_Ctrl_Placement.SetCurSel(m_Ctrl_Placement.FindStringExact(0, _T("centroid")));


    // geometry-transform
    //m_Ctrl_Transform.GetLBText(idx, Transform);
    m_Transform = _T("");
        
    // comp-op
    m_Ctrl_CompOp.SetCurSel(m_Ctrl_Placement.FindStringExact(0, _T("src-over")));

    UpdateData(FALSE);
    OnEnKillfocus();
}
