// Symbolizer_Raster.cpp : implementation file
//
#include "stdafx.h"
//#include "pch.h"
#include "BCGPSymbolizer.h"
#include "Symbolizer_Raster.h"
#include "afxdialogex.h"
#include <vector>
#include <sstream>
#include <tinyxml2.h>

static std::vector<std::string> split(const std::string& s, char delim);
static constexpr unsigned int str2int(const char* str, int h = 0);

static std::vector<std::string> split(const std::string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

static constexpr unsigned int str2int(const char* str, int h)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


// Symbolizer_Raster

IMPLEMENT_DYNCREATE(Symbolizer_Raster, CBCGPFormView)

Symbolizer_Raster::Symbolizer_Raster()
	: CBCGPFormView(IDD_FORMVIEW_RASTERSYMBOLIZER)
    , m_Opacity(_T("1"))
    , m_Filterfactor(_T("-1"))
    , m_Meshsize(_T("16"))
    , m_Epsilon(_T("1.1920928955078125e-07"))
    , m_Stop(_T(""))
{

}

Symbolizer_Raster::~Symbolizer_Raster()
{
}

void Symbolizer_Raster::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_DEFAULT_RASTER, m_Default);
    DDX_Control(pDX, IDC_STATIC_RESET_RASTER, m_Ctrl_Reset);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON_RASTER, m_Ctrl_Color);
    DDX_Text(pDX, IDC_EDIT_OPACITY_RASTER, m_Opacity);
    DDX_Text(pDX, IDC_EDIT_FILTERFACTOR_RASTER, m_Filterfactor);
    DDX_Control(pDX, IDC_COMBO_SCALING_RASTER, m_Ctrl_Scaling);
    DDX_Text(pDX, IDC_EDIT_MESHSIZE_RASTER, m_Meshsize);
    DDX_Control(pDX, IDC_COMBO_COMP_OP_RASTER, m_Ctrl_CompOp);
    DDX_Control(pDX, IDC_COMBO_DEFAULTMODE_RASTER, m_Ctrl_Mode);
    DDX_Text(pDX, IDC_EDIT_EPSILON_RASTER, m_Epsilon);
    DDX_Text(pDX, IDC_EDIT_STOP_RASTER, m_Stop);
    DDX_Text(pDX, IDC_EDIT_XML_RASTER, m_Script);

}

BEGIN_MESSAGE_MAP(Symbolizer_Raster, CBCGPFormView)
    ON_BN_CLICKED(IDC_CHECK_DEFAULT_RASTER, &Symbolizer_Raster::OnBnClickedCheckDefault)

    ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_OPACITY_RASTER, &Symbolizer_Raster::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_EDIT_FILTERFACTOR_RASTER, &Symbolizer_Raster::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_SCALING_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_MESHSIZE_RASTER, &Symbolizer_Raster::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_COMP_OP_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_DEFAULTMODE_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_EPSILON_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_STOP_RASTER, &Symbolizer_Raster::OnEnKillfocus)
    ON_STN_CLICKED(IDC_STATIC_RESET_RASTER, &Symbolizer_Raster::OnStnClickedStaticResetRaster)
END_MESSAGE_MAP()


// Symbolizer_Raster message handlers

BOOL Symbolizer_Raster::CreateView(CWnd* pParent, CCreateContext* pContext)
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

void Symbolizer_Raster::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();
   
    HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
    m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
    // Set the icon of the button to be the system question mark icon.
    m_Ctrl_Reset.SetIcon(h_Ico);

    // 
    m_Ctrl_Color.SetColor(RGB(0, 0, 0));

    // scaling
    m_Ctrl_Scaling.AddString(_T("near"));
    m_Ctrl_Scaling.AddString(_T("fast"));
    m_Ctrl_Scaling.AddString(_T("bilinear"));
    m_Ctrl_Scaling.AddString(_T("bicubic"));
    m_Ctrl_Scaling.AddString(_T("spline16"));
    m_Ctrl_Scaling.AddString(_T("spline36"));
    m_Ctrl_Scaling.AddString(_T("hanning"));
    m_Ctrl_Scaling.AddString(_T("hamming"));
    m_Ctrl_Scaling.AddString(_T("hermite"));
    m_Ctrl_Scaling.AddString(_T("kaiser"));
    m_Ctrl_Scaling.AddString(_T("quadric"));
    m_Ctrl_Scaling.AddString(_T("catrom"));
    m_Ctrl_Scaling.AddString(_T("gaussian"));
    m_Ctrl_Scaling.AddString(_T("bessel"));
    m_Ctrl_Scaling.AddString(_T("mitchell"));
    m_Ctrl_Scaling.AddString(_T("sinc"));
    m_Ctrl_Scaling.AddString(_T("lanczos"));
    m_Ctrl_Scaling.AddString(_T("blackman"));
    m_Ctrl_Scaling.SetCurSel(13);

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

    // default mode
    m_Ctrl_Mode.AddString(_T("discrete"));
    m_Ctrl_Mode.AddString(_T("linear"));
    m_Ctrl_Mode.AddString(_T("exact"));
    m_Ctrl_Mode.SetCurSel(2);

    // Create the ToolTip control.
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_ToolTip.SetParams(&params);
   
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.default"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.opacity"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILTERFACTOR_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.filter-factor"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SCALING_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.scaling"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MESHSIZE_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.mesh-size"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.comp-op"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_DEFAULTMODE_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.default-mode"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.default-color"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_EPSILON_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.epsilon"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_STOP_RASTER), CString(m_ToolTip.m_MapTooltip_Doc["RasterSymbolizer.stop"].c_str()));

    //// TODO: Use one of the following forms to add controls:
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_RASTER), _T("Allows omitting a line symbolizer rule or emitting it with default values."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_RASTER), _T("This can be any color. Sets the color that is applied to "
    //                                                          "\nall values outside of the range of the colorizer-stops. "
    //                                                            "\nIf not supplied pixels will be fully transparent."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_RASTER), _T("The opacity of the raster symbolizer on top of other symbolizers."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILTERFACTOR_RASTER), _T("This is used by the Raster or Gdal datasources to pre-downscale "
    //                                                             "\nimages using overviews. Higher numbers can sometimes cause much "
    //                                                             "\nbetter scaled image output, at the cost of speed."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SCALING_RASTER), _T("The scaling algorithm used to making different resolution versions of this "
    //                                                         "\nraster layer. Bilinear is a good compromise between speed and accuracy, "
    //                                                            "\nwhile lanczos gives the highest quality."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MESHSIZE_RASTER), _T("A reduced resolution mesh is used for raster reprojection, and the total "
    //                                                         "\nimage size is divided by the mesh-size to determine the quality of that "
    //                                                         "\nmesh. Values for mesh-size larger than the default will result in faster "
    //                                                            "\nreprojection but might lead to distortion."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_RASTER), _T("Composite operation. This defines how this symbolizer should behave "
    //                                                            "\nrelative to symbolizers atop or below it."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_DEFAULTMODE_RASTER), _T("This can be either `discrete`, `linear` or `exact`. "
    //                                                               "\nIf it is not specified then the default is `linear`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_EPSILON_RASTER), _T("This can be any positive floating point value and will be used as "
    //                                                        "\na tolerance in floating point comparisions. The higher the value "
    //                                                        "\nthe more likely a stop will match and color data."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_STOP_RASTER), _T("Assigns raster data values to colors. Stops must be listed in ascending order, "
    //                                                     "\nand contain at a minimum the value and the associated color. You can also "
    //                                                      "\ninclude the color-mode as a third argument, like `stop(100,#fff,exact)`."));


    // Script
    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}


COLORREF Symbolizer_Raster::GetColor(std::string value)
{
    LPCSTR pszTmp = value.c_str();
    pszTmp++;
    COLORREF crefColor;
    //sscanf_s(pszTmp, "%x", &crefColor);
    crefColor = strtol(pszTmp, NULL, 16);
    INT nR = GetRValue(crefColor);
    INT nG = GetGValue(crefColor);
    INT nB = GetBValue(crefColor);
    return RGB(nB, nG, nR);
}

BOOL Symbolizer_Raster::PreTranslateMessage(MSG* pMsg)
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

void Symbolizer_Raster::OnEnKillfocus()
{

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Raster::OnBnClickedCheckDefault()
{
    UpdateData();

    GetDlgItem(IDC_MFCCOLORBUTTON_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OPACITY_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_FILTERFACTOR_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_SCALING_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_MESHSIZE_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_COMP_OP_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_DEFAULTMODE_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_EPSILON_RASTER)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_STOP_RASTER)->EnableWindow(!m_Default);
    

    OnEnKillfocus();
}

std::string Symbolizer_Raster::SettingsXml()
{
    UpdateData();

    int idx = 0;
    tinyxml2::XMLDocument doc;
    auto Element = doc.NewElement("RasterSympolizer");

    if (m_Default)
    {
        doc.LinkEndChild(Element);
        tinyxml2::XMLPrinter printer;
        doc.Accept(&printer);

        return std::string(printer.CStr());
    }

    // default-color
    COLORREF dColor = m_Ctrl_Color.GetColor();
    if (dColor != RGB(0, 0, 0))
    {
        CString sColor;
        sColor.Format(_T("#%02X%02X%02X"), GetRValue(dColor), GetGValue(dColor), GetBValue(dColor));
        //result += " stroke=" + std::string((CT2CA)sColor);
        Element->SetAttribute("default-color", (CT2CA)sColor);
    }

    // Opacity
    if (m_Opacity != _T("1"))
        Element->SetAttribute("opacity", (CT2CA)m_Opacity);

    // filter-facter
    if (m_Filterfactor != _T("-1"))
        Element->SetAttribute("filter-facter", (CT2CA)m_Filterfactor);
    
    // scaling
    CString Scaling;
    idx = m_Ctrl_Scaling.GetCurSel();
    m_Ctrl_Scaling.GetLBText(idx, Scaling);
    if (Scaling != _T("near"))
        Element->SetAttribute("scaling", (CT2CA)Scaling);

    // mesh-size
    if (m_Meshsize != _T("16"))
        Element->SetAttribute("mesh-size", (CT2CA)m_Meshsize);

    // comp-op
    CString CompOp;
    idx = m_Ctrl_CompOp.GetCurSel();
    m_Ctrl_CompOp.GetLBText(idx, CompOp);
    if (CompOp != _T("src-over"))
        Element->SetAttribute("comp-op", (CT2CA)CompOp);
  
    // default-mode
    CString Mode;
    idx = m_Ctrl_Mode.GetCurSel();
    m_Ctrl_Mode.GetLBText(idx, Mode);
    if (Mode != _T("linear"))
        Element->SetAttribute("default-mode", (CT2CA)Mode);

    // epsilon
    if (m_Epsilon != _T("1.1920928955078125e-07"))
        Element->SetAttribute("epsilon", (CT2CA)m_Epsilon);

    // stop
    if (m_Stop != _T(""))
        Element->SetAttribute("epsilon", (CT2CA)m_Stop);

    doc.LinkEndChild(Element);
    tinyxml2::XMLPrinter printer;
    doc.Accept(&printer);

    return std::string(printer.CStr());

}

void Symbolizer_Raster::SettingsXml(std::string str)
{
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*)str.c_str());
    tinyxml2::XMLElement* titleElement = doc.FirstChildElement("RasterSympolizer");
    if (titleElement == NULL)
        return;

    if (titleElement->FindAttribute("default-color"))
        m_Ctrl_Color.SetColor(GetColor(titleElement->Attribute("default-color")));

    if (titleElement->FindAttribute("opacity"))
        m_Opacity.SetString(CString(titleElement->Attribute("opacity")));

    if (titleElement->FindAttribute("filter-factor"))
        m_Filterfactor = CString(titleElement->Attribute("filter-factor"));

    if (titleElement->FindAttribute("scaling"))
        m_Ctrl_Scaling.SetCurSel(m_Ctrl_Scaling.FindStringExact(0, CString(titleElement->Attribute("scaling"))));

    if (titleElement->FindAttribute("mesh-size"))
        m_Meshsize.SetString(CString(titleElement->Attribute("mesh-size")));

    if (titleElement->FindAttribute("comp-op"))
        m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, CString(titleElement->Attribute("comp-op"))));

    if (titleElement->FindAttribute("default-mode"))
        m_Ctrl_Mode.SetCurSel(m_Ctrl_Mode.FindStringExact(0, CString(titleElement->Attribute("default-mode"))));

    if (titleElement->FindAttribute("epsilon"))
        m_Epsilon = CString(titleElement->Attribute("epsilon"));

    if (titleElement->FindAttribute("stop"))
        m_Stop = CString(titleElement->Attribute("stop"));

    UpdateData(false);
}


void Symbolizer_Raster::OnEnKillfocusFloat()
{
    UpdateData();
    if (!m_ToolTip.isFloat(m_Filterfactor))
    {
        m_Filterfactor = _T("-1");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_FILTERFACTOR_RASTER)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Opacity))
    {
        m_Opacity = _T("1");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OPACITY_RASTER)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Meshsize))
    {
        m_Meshsize = _T("16");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_MESHSIZE_RASTER)->SetFocus();
    }

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Raster::OnStnClickedStaticResetRaster()
{
    // default-color
    m_Ctrl_Color.SetColor(RGB(0, 0, 0));
   

    // Opacity
    m_Opacity = _T("1");

    // filter-facter
    m_Filterfactor = _T("-1");

    // scaling
    m_Ctrl_Scaling.SetCurSel(m_Ctrl_Scaling.FindStringExact(0, _T("near")));

    // mesh-size
    m_Meshsize = _T("16");

    // comp-op
    m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, _T("src-over")));

    // default-mode
    m_Ctrl_Mode.SetCurSel(m_Ctrl_Mode.FindStringExact(0, _T("linear")));

    // epsilon
    m_Epsilon = _T("1.1920928955078125e-07");

    // stop
    m_Stop = _T("");

    UpdateData(FALSE);
    OnEnKillfocus();
}
