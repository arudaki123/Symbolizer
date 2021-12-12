// Symbolizer_Line.cpp : implementation file
//
#include "stdafx.h"
//#include "pch.h"
#include "BCGPSymbolizer.h"
#include "Symbolizer_Line.h"
#include "afxdialogex.h"
#include <vector>
#include <tinyxml2.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static std::vector<std::string> split(const std::string& s, char delim);
static constexpr unsigned int str2int(const char* str, int h = 0);


// Symbolizer_Line dialog

IMPLEMENT_DYNAMIC(Symbolizer_Line, CBCGPFormView)

Symbolizer_Line::Symbolizer_Line(CWnd* pParent /*=nullptr*/)
    : CBCGPFormView(IDD_FORMVIEW_LINESYMPOLIZER)
    , m_Line_Width(_T("1"))
    , m_Opacity(_T("1"))
    , m_Gamma(_T("1"))
    , m_Dasharray(_T(""))
    , m_Dashoffset(_T(""))
    , m_MiterLimit(_T("4"))
    , m_Clip(FALSE)
    , m_Simplify(_T("0"))
    , m_Smooth(_T("0"))
    , m_Offset(_T("0"))
    , m_Default(FALSE)
    , m_GeometryTransform(_T(""))
    , m_Script(_T(""))
{

}

Symbolizer_Line::~Symbolizer_Line()
{
}

void Symbolizer_Line::DoDataExchange(CDataExchange* pDX)
{
    CBCGPFormView::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_DEFAULT_LINE, m_Default);
    DDX_Control(pDX, IDC_STATIC_RESET_LINE, m_Ctrl_Reset);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON_LINE, m_Ctrl_Color);
    DDX_Text(pDX, IDC_EDIT_WIDTH_LINE, m_Line_Width);
    DDX_Text(pDX, IDC_EDIT_OPACITY_LINE, m_Opacity);
    DDX_Control(pDX, IDC_COMBO_JOIN_LINE, m_Ctrl_Linejoin);
    DDX_Control(pDX, IDC_COMBO_CAP_LINE, m_Ctrl_Linecap);
    DDX_Text(pDX, IDC_EDIT_GAMMA_LINE, m_Gamma);
    DDX_Control(pDX, IDC_COMBO_GAMMA_METHOD_LINE, m_Ctrl_GammaMethod);
    DDX_Text(pDX, IDC_EDIT_DASHARRAY_LINE, m_Dasharray);
    DDX_Text(pDX, IDC_EDIT_DASHOFFSET_LINE, m_Dashoffset);
    DDX_Text(pDX, IDC_EDIT_MITERLIMIT_LINE, m_MiterLimit);
    DDX_Check(pDX, IDC_CHECK_CLIP_LINE, m_Clip);
    DDX_Text(pDX, IDC_EDIT_SIMPLIFY_LINE, m_Simplify);
    DDX_Control(pDX, IDC_COMBO_SIMPLIFY_LINE, m_Ctrl_SimplifyAlgorithm);
    DDX_Text(pDX, IDC_EDIT_SMOOTH_LINE, m_Smooth);
    DDX_Text(pDX, IDC_EDIT_OFFSET_LINE, m_Offset);
    DDX_Control(pDX, IDC_RASTERIZER_LINE, m_Ctrl_Rasterizer);
    DDX_Text(pDX, IDC_EDIT_GEOMETRY_TRANSFORM_LINE, m_GeometryTransform);
    DDX_Control(pDX, IDC_COMBO_COMP_OP_LINE, m_Ctrl_CompOp);
    DDX_Text(pDX, IDC_EDIT_XML_LINE, m_Script);

}


BEGIN_MESSAGE_MAP(Symbolizer_Line, CBCGPFormView)
    ON_BN_CLICKED(IDC_CHECK_DEFAULT_LINE, &Symbolizer_Line::OnBnClickedCheckDefaultLine)
    ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_WIDTH_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_EDIT_OPACITY_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_JOIN_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_CAP_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_GAMMA_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_GAMMA_METHOD_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_DASHARRAY_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_DASHOFFSET_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_MITERLIMIT_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_CHECK_CLIP_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_SIMPLIFY_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_SIMPLIFY_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_SMOOTH_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_EDIT_OFFSET_LINE, &Symbolizer_Line::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_RASTERIZER_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOMETRY_TRANSFORM_LINE, &Symbolizer_Line::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_COMP_OP_LINE, &Symbolizer_Line::OnEnKillfocus)

    ON_BN_CLICKED(IDC_CHECK_CLIP_LINE, &Symbolizer_Line::OnBnClickedCheckClipLine)
    ON_STN_CLICKED(IDC_STATIC_RESET_LINE, &Symbolizer_Line::OnStnClickedStaticResetLine)
END_MESSAGE_MAP()

CString CheckFloat(CString CStr)
{
    return CStr.SpanIncluding(_T("0123456789."));

}


// Symbolizer_Line message handlers

BOOL Symbolizer_Line::CreateView(CWnd* pParent, CCreateContext* pContext)
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

void Symbolizer_Line::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();
    HICON h_Ico = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    m_Ctrl_Reset.ModifyStyle(0, SS_ICON);
    m_Ctrl_Reset.ModifyStyle(0, SS_NOTIFY);
    // Set the icon of the button to be the system question mark icon.
    m_Ctrl_Reset.SetIcon(h_Ico);// LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_RESET)));
    //m_Ctrl_Reset.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET)));
    

    m_Ctrl_Color.SetColor(RGB(0, 0, 0));

    // Line join
    m_Ctrl_Linejoin.AddString(_T("miter"));
    m_Ctrl_Linejoin.AddString(_T("miter-revert"));
    m_Ctrl_Linejoin.AddString(_T("round"));
    m_Ctrl_Linejoin.AddString(_T("bevel"));
    m_Ctrl_Linejoin.SetCurSel(1);

    // Line cap
    m_Ctrl_Linecap.AddString(_T("butt"));
    m_Ctrl_Linecap.AddString(_T("round"));
    m_Ctrl_Linecap.AddString(_T("square"));
    m_Ctrl_Linecap.SetCurSel(0);

    // Gamma method
    m_Ctrl_GammaMethod.AddString(_T("power"));
    m_Ctrl_GammaMethod.AddString(_T("linear"));
    m_Ctrl_GammaMethod.AddString(_T("none"));
    m_Ctrl_GammaMethod.AddString(_T("threshold"));
    m_Ctrl_GammaMethod.AddString(_T("multiply"));
    m_Ctrl_GammaMethod.SetCurSel(3);

    // Simplify
    m_Ctrl_SimplifyAlgorithm.AddString(_T("radial-distance"));
    m_Ctrl_SimplifyAlgorithm.AddString(_T("zhao-saalfeld"));
    m_Ctrl_SimplifyAlgorithm.AddString(_T("visvalingam-whyatt"));
    m_Ctrl_SimplifyAlgorithm.AddString(_T("douglas-peucker"));
    m_Ctrl_SimplifyAlgorithm.SetCurSel(1);

    // Rasterizer
    m_Ctrl_Rasterizer.AddString(_T("full"));
    m_Ctrl_Rasterizer.AddString(_T("fast"));
    m_Ctrl_Rasterizer.SetCurSel(1);

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
    
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.default"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-width"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-opacity"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_JOIN_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-linejoin"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_CAP_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-linecap"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GAMMA_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-gamma"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_GAMMA_METHOD_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-gamma-method"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHARRAY_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-dasharray"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHOFFSET_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-dashoffset"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MITERLIMIT_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.stroke-miterlimit"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_CLIP_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.clip"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMPLIFY_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.simplify"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SIMPLIFY_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.simplify-algorithm"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SMOOTH_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.smooth"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OFFSET_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.offset"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_RASTERIZER_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.rasterizer"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.geometry-transform"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_LINE), CString(m_ToolTip.m_MapTooltip_Doc["LineSymbolizer.comp-op"].c_str()));

    //// TODO: Use one of the following forms to add controls:
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_LINE), _T("Allows omitting a line symbolizer rule or emitting it with default values."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_LINE), _T("The color of a drawn line."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_LINE), _T("The width of a line in pixels."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_LINE), _T("The opacity of a line."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_JOIN_LINE), _T("The behavior of lines when joining."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_CAP_LINE), _T("The display of line endings."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GAMMA_LINE), _T("Level of antialiasing of stroke line."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_GAMMA_METHOD_LINE), _T("An Antigrain Geometry specific rendering hint to control the quality of antialiasing. Under the hood in Mapnik this \nmethod is used in combination with the 'gamma' value (which defaults to 1). The methods are in the AGG source at\n https://github.com/mapnik/mapnik/blob/master/deps/agg/include/agg_gamma_functions."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHARRAY_LINE), _T("A pair of length values [a,b], where (a) is the dash length and (b) is the gap length respectively. \nMore than two values are supported for more complex patterns."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHOFFSET_LINE), _T("Valid parameter but not currently used in renderers (only exists for experimental svg support in Mapnik which is not yet enabled)."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MITERLIMIT_LINE), _T("The limit on the ratio of the miter length to the stroke-width. Used to automatically convert miter joins \nto bevel joins for sharp angles to avoid the miter extending beyond the thickness of the stroking path. \nNormally will not need to be set, but a larger value can sometimes help avoid jaggy artifacts."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_CLIP_LINE), _T("Turning on clipping can help performance in the case that the boundaries of the geometry extent \noutside of tile extents. But clipping can result in undesirable rendering artifacts in rare cases."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMPLIFY_LINE), _T("Simplify geometries by the given tolerance."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SIMPLIFY_LINE), _T("Simplify geometries by the given algorithm."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SMOOTH_LINE), _T("Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. \nValues greater than 1 will produce wild, looping geometries."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OFFSET_LINE), _T("Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, \nnegative values move it right (relative to the directionality of the line)."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_RASTERIZER_LINE), _T("Exposes an alternate AGG rendering method that sacrifices some accuracy for speed."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINE), _T("Transform line geometry with specified function."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_LINE), _T("Composite operation. This defines how this symbolizer should behave relative to symbolizers atop or below it."));

    // Script
    m_Script.SetString(CString(SettingsXml().c_str()));
}


void Symbolizer_Line::OnBnClickedCheckDefaultLine()
{
    UpdateData();

    //test setting xml
    //std::string test_string = SettingsXml();
    //std::string test2("<LineSympolizer stroke="#00FF00" stroke-width="345" stroke-opacity="34" stroke-linejoin="round" stroke-linecap="round" stroke-miterlimit="3" clip="true" simplify="454" simplify-algorithm="visvalingam-whyatt" smooth="44" offset="02" rasterizer="fast" geometry-transform="sdfsdsdfs" comp-op="dst"/>");
    //SettingsXml(test_string);

    GetDlgItem(IDC_MFCCOLORBUTTON_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_WIDTH_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OPACITY_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_CAP_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_JOIN_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_GAMMA_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_GAMMA_METHOD_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_DASHARRAY_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_DASHOFFSET_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_MITERLIMIT_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_CHECK_CLIP_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_SIMPLIFY_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_SIMPLIFY_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_SMOOTH_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OFFSET_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_RASTERIZER_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_COMP_OP_LINE)->EnableWindow(!m_Default);

    OnEnKillfocus();
}

std::string Symbolizer_Line::SettingsXml()
{
    UpdateData();
    
    int idx = 0;
    tinyxml2::XMLDocument doc;
    auto Element = doc.NewElement("LineSympolizer");

    if (m_Default)
    {
        doc.LinkEndChild(Element);
        tinyxml2::XMLPrinter printer;
        doc.Accept(&printer);

        return std::string(printer.CStr());
    }

    // stroke color
    COLORREF dColor = m_Ctrl_Color.GetColor();
    if (dColor != RGB(0, 0, 0))
    {
        CString sColor;
        sColor.Format(_T("#%02X%02X%02X"), GetRValue(dColor), GetGValue(dColor), GetBValue(dColor));
        Element->SetAttribute("stroke", (CT2CA)sColor);
    }
    
    // stroke-width
    if (m_Line_Width != _T("1"))
        Element->SetAttribute("stroke-width", (CT2CA)m_Line_Width);

    // stroke-opacity
    if (m_Opacity != _T("1"))
        Element->SetAttribute("stroke-opacity", (CT2CA)m_Opacity);

    // stroke-linejoin
    CString Linejoin;
    idx = m_Ctrl_Linejoin.GetCurSel();
    m_Ctrl_Linejoin.GetLBText(idx, Linejoin);
    if (Linejoin != _T("miter"))
        Element->SetAttribute("stroke-linejoin", (CT2CA)Linejoin);

    // stroke-linecap
    CString Linecap;
    idx = m_Ctrl_Linecap.GetCurSel();
    m_Ctrl_Linecap.GetLBText(idx, Linecap);
    if (Linecap != _T("butt"))
        Element->SetAttribute("stroke-linecap", (CT2CA)Linecap);

    // stroke-gamma
    if (m_Gamma != _T("1"))
        Element->SetAttribute("stroke-gamma", (CT2CA)m_Gamma);

    // stroke-gamma-method
    CString Gammamethod;
    idx = m_Ctrl_GammaMethod.GetCurSel();
    m_Ctrl_GammaMethod.GetLBText(idx, Gammamethod);
    if (Gammamethod != _T("power"))
        Element->SetAttribute("stroke-gamma-method", (CT2CA)Gammamethod);

    // stroke-dasharray
    if (m_Dasharray != _T(""))
        Element->SetAttribute("stroke-dasharray", (CT2CA)m_Dasharray);

    // stroke-dashoffset
    if (m_Dashoffset != _T(""))
        Element->SetAttribute("stroke-dashoffset", (CT2CA)m_Dashoffset);

    // stroke-miterlimit
    if (m_MiterLimit != _T("4"))
        Element->SetAttribute("stroke-miterlimit", (CT2CA)m_MiterLimit);

    // clip
    if (m_Clip)
        Element->SetAttribute("clip", true);

    // simplify
    if (m_Simplify != _T("0"))
        Element->SetAttribute("simplify", (CT2CA)m_Simplify);

    // simplify-algorithm
    CString SimplifyAlgorithm;
    idx = m_Ctrl_SimplifyAlgorithm.GetCurSel();
    m_Ctrl_SimplifyAlgorithm.GetLBText(idx, SimplifyAlgorithm);
    if (SimplifyAlgorithm != _T("radial-distance"))
        Element->SetAttribute("simplify-algorithm", (CT2CA)SimplifyAlgorithm);

    // smooth
    if (m_Smooth != _T("0"))
        Element->SetAttribute("smooth", (CT2CA)m_Smooth);
    
    // offset
    if (m_Offset != _T("0"))
        Element->SetAttribute("offset", (CT2CA)m_Offset);

    // rasterizer
    CString Rasterizer;
    idx = m_Ctrl_Rasterizer.GetCurSel();
    m_Ctrl_Rasterizer.GetLBText(idx, Rasterizer);
    if (Rasterizer != _T("full"))
        Element->SetAttribute("rasterizer", (CT2CA)Rasterizer);
    
    // geometry-transform
    if (m_GeometryTransform != _T(""))
        Element->SetAttribute("geometry-transform", (CT2CA)m_GeometryTransform);

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
    
    //return result;
}

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

void Symbolizer_Line::SettingsXml(std::string str)
{
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*)str.c_str());
    tinyxml2::XMLElement* titleElement = doc.FirstChildElement("LineSympolizer");
    if (titleElement == NULL)
        return;
    
    if (titleElement->FindAttribute("stroke"))
        m_Ctrl_Color.SetColor(GetColor(titleElement->Attribute("stroke")));

    if (titleElement->FindAttribute("stroke-width"))
        m_Line_Width.SetString(CString(titleElement->Attribute("stroke-width")));

    if (titleElement->FindAttribute("stroke-opacity"))
        m_Opacity = CString(titleElement->Attribute("stroke-opacity"));

    if (titleElement->FindAttribute("stroke-linejoin"))
        m_Ctrl_Linejoin.SetCurSel(m_Ctrl_Linejoin.FindStringExact(0, CString(titleElement->Attribute("stroke-linejoin"))));

    if (titleElement->FindAttribute("stroke-linecap"))
        m_Ctrl_Linecap.SetCurSel(m_Ctrl_Linecap.FindStringExact(0, CString(titleElement->Attribute("stroke-linecap"))));

    if (titleElement->FindAttribute("stroke-gamma"))
        m_Gamma = CString(titleElement->Attribute("stroke-gamma"));

    if (titleElement->FindAttribute("stroke-gamma-method"))
        m_Ctrl_GammaMethod.SetCurSel(m_Ctrl_GammaMethod.FindStringExact(0, CString(titleElement->Attribute("stroke-gamma-method"))));

    if (titleElement->FindAttribute("stroke-dasharray"))
        m_Dasharray = titleElement->Attribute("stroke-dasharray");

    if (titleElement->FindAttribute("stroke-dashoffset"))
        m_Dashoffset.SetString(CString(titleElement->Attribute("stroke-dashoffset")));

    if (titleElement->FindAttribute("stroke-miterlimit"))
        m_MiterLimit.SetString(CString(titleElement->Attribute("stroke-miterlimit")));

    if (titleElement->FindAttribute("clip"))
        m_Clip = CString(titleElement->Attribute("clip")) == _T("true");

    if (titleElement->FindAttribute("simplify"))
        m_Simplify.SetString(CString(titleElement->Attribute("simplify")));

    if (titleElement->FindAttribute("simplify-algorithm"))
        m_Ctrl_SimplifyAlgorithm.SetCurSel(m_Ctrl_SimplifyAlgorithm.FindStringExact(0, CString(titleElement->Attribute("simplify-algorithm"))));

    if (titleElement->FindAttribute("smooth"))
        m_Smooth.SetString(CString(titleElement->Attribute("smooth")));

    if (titleElement->FindAttribute("offset"))
        m_Offset.SetString(CString(titleElement->Attribute("offset")));

    if (titleElement->FindAttribute("rasterizer"))
        m_Ctrl_Rasterizer.SetCurSel(m_Ctrl_Rasterizer.FindStringExact(0, CString(titleElement->Attribute("rasterizer"))));

    if (titleElement->FindAttribute("geometry-transform"))
        m_GeometryTransform = titleElement->Attribute("geometry-transform");

    if (titleElement->FindAttribute("comp-op"))
        m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, CString(titleElement->Attribute("comp-op"))));

    
    UpdateData(false);
}

COLORREF Symbolizer_Line::GetColor(std::string value)
/// get color form string
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

BOOL Symbolizer_Line::PreTranslateMessage(MSG* pMsg)
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

void Symbolizer_Line::OnEnKillfocus()
{
    UpdateData();
    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Line::OnEnKillfocusFloat()
{
    UpdateData();
    if (!m_ToolTip.isFloat(m_Line_Width))
    {
        m_Line_Width.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_WIDTH_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Opacity))
    {
        m_Opacity.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OPACITY_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Gamma))
    { 
        m_Gamma.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_GAMMA_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_MiterLimit))
    {
        m_MiterLimit.SetString(_T("4"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_MITERLIMIT_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Simplify))
    {
        m_Simplify.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_SIMPLIFY_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Smooth))
    {
        m_Smooth.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        
        GetDlgItem(IDC_EDIT_SMOOTH_LINE)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Offset))
    {
        m_Offset.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OFFSET_LINE)->SetFocus();
    }

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}


void Symbolizer_Line::OnBnClickedCheckClipLine()
{
    OnEnKillfocus();
}

void Symbolizer_Line::OnStnClickedStaticResetLine()
{
    // stroke color
    m_Ctrl_Color.SetColor(RGB(0, 0, 0));

    // stroke-width
    m_Line_Width = _T("1");

    // stroke-opacity
    m_Opacity = _T("1");

    // stroke-linejoin
    m_Ctrl_Linejoin.SetCurSel(m_Ctrl_Linejoin.FindStringExact(0, _T("miter")));

    // stroke-linecap
    CString Linecap;
    m_Ctrl_Linecap.SetCurSel(m_Ctrl_Linecap.FindStringExact(0, _T("butt")));

    // stroke-gamma
    m_Gamma = _T("1");

    // stroke-gamma-method
    m_Ctrl_GammaMethod.SetCurSel(m_Ctrl_GammaMethod.FindStringExact(0, _T("power")));

    // stroke-dasharray
    m_Dasharray = _T("");

    // stroke-dashoffset
    m_Dashoffset = _T("");

    // stroke-miterlimit
    m_MiterLimit = _T("4");

    // clip
    m_Clip = FALSE;

    // simplify
    m_Simplify = _T("0");

    // simplify-algorithm
    m_Ctrl_SimplifyAlgorithm.SetCurSel(m_Ctrl_SimplifyAlgorithm.FindStringExact(0, _T("radial-distance")));

    // smooth
    m_Smooth = _T("0");

    // offset
    m_Offset = _T("0");

    // rasterizer
    m_Ctrl_Rasterizer.SetCurSel(m_Ctrl_Rasterizer.FindStringExact(0, _T("full")));

    // geometry-transform
    m_GeometryTransform = _T("");

    // comp-op
    m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, _T("src-over")));

    UpdateData(FALSE);
    OnEnKillfocus();
}
