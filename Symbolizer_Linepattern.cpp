// Symbolizer_Linepattern.cpp : implementation file
//

#include "stdafx.h"
//#include "pch.h"
#include "BCGPSymbolizer.h"
#include "Symbolizer_Linepattern.h"
#include "afxdialogex.h"
#include <vector>
#include <sstream>
#include <tinyxml2.h>

static std::vector<std::string> split(const std::string& s, char delim);
static constexpr unsigned int str2int(const char* str, int h = 0);


// Symbolizer_Linepattern

IMPLEMENT_DYNCREATE(Symbolizer_Linepattern, CBCGPFormView)

Symbolizer_Linepattern::Symbolizer_Linepattern()
	: CBCGPFormView(IDD_FORMVIEW_LINEPATTERNSYMPOLIZER)
    , m_File(_T(""))
    , m_Width(_T("1"))
    , m_Opacity(_T("1"))
    , m_Dasharray(_T(""))
    , m_MiterLimit(_T("4"))
    , m_Clip(FALSE)
    , m_Simplify(_T("0"))
    , m_Smooth(_T("0"))
    , m_Offset(_T("0"))
    , m_Default(FALSE)
    , m_GeometryTransform(_T(""))
    , m_Transform(_T(""))
    , m_Script(_T(""))
{

}

Symbolizer_Linepattern::~Symbolizer_Linepattern()
{
}

void Symbolizer_Linepattern::DoDataExchange(CDataExchange* pDX)
{
    CBCGPFormView::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_DEFAULT_LINEPATTERN, m_Default);
    DDX_Control(pDX, IDC_STATIC_RESET_LINEPATTERN, m_Ctrl_Reset);
    DDX_Control(pDX, IDC_COMBO_LINEPATTERN_TYPE, m_Ctrl_Type);
    DDX_Text(pDX, IDC_EDIT_WIDTH_LINEPATTERN, m_Width);
    DDX_Text(pDX, IDC_EDIT_OPACITY_LINEPATTERN, m_Opacity);
    DDX_Control(pDX, IDC_COMBO_JOIN_LINEPATTERN, m_Ctrl_Linejoin);
    DDX_Control(pDX, IDC_COMBO_CAP_LINEPATTERN, m_Ctrl_Linecap);
    DDX_Text(pDX, IDC_EDIT_FILE_LINEPATTERN, m_File);
    DDX_Text(pDX, IDC_EDIT_DASHARRAY_LINEPATTERN, m_Dasharray);
    DDX_Text(pDX, IDC_EDIT_MITERLIMIT_LINEPATTERN, m_MiterLimit);
    DDX_Check(pDX, IDC_CHECK_CLIP_LINEPATTERN, m_Clip);
    DDX_Text(pDX, IDC_EDIT_SIMPLIFY_LINEPATTERN, m_Simplify);
    DDX_Control(pDX, IDC_COMBO_SIMPLIFY_LINEPATTERN, m_Ctrl_SimplifyAlgorithm);
    DDX_Text(pDX, IDC_EDIT_SMOOTH_LINEPATTERN, m_Smooth);
    DDX_Text(pDX, IDC_EDIT_OFFSET_LINEPATTERN, m_Offset);
    DDX_Control(pDX, IDC_ALIGNMENT_LINEPATTERN, m_Ctrl_Alignment);
    DDX_Text(pDX, IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN, m_GeometryTransform);
    DDX_Text(pDX, IDC_EDIT_TRANSFORM_LINEPATTERN, m_Transform);
    DDX_Control(pDX, IDC_COMBO_COMP_OP_LINEPATTERN, m_Ctrl_CompOp);
    DDX_Text(pDX, IDC_EDIT_XML_LINEPATTERN, m_Script);

    DDX_Control(pDX, IDC_STATIC_FILE_LINEPATTERN, m_Ctrl_File);
}

BEGIN_MESSAGE_MAP(Symbolizer_Linepattern, CBCGPFormView)
    ON_BN_CLICKED(IDC_CHECK_DEFAULT_LINEPATTERN, &Symbolizer_Linepattern::OnBnClickedCheckDefault)
    ON_BN_KILLFOCUS(IDC_CHECK_DEFAULT_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_LINEPATTERN_TYPE, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_WIDTH_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_EDIT_OPACITY_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_JOIN_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_CAP_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_FILE_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_DASHARRAY_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_MITERLIMIT_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_CHECK_CLIP_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_SIMPLIFY_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_COMBO_SIMPLIFY_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_SMOOTH_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_EDIT_OFFSET_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocusFloat)
    ON_EN_KILLFOCUS(IDC_ALIGNMENT_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_TRANSFORM_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_COMBO_COMP_OP_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)
    ON_EN_KILLFOCUS(IDC_EDIT_XML_LINEPATTERN, &Symbolizer_Linepattern::OnEnKillfocus)

    ON_BN_CLICKED(IDC_CHECK_CLIP_LINEPATTERN, &Symbolizer_Linepattern::OnBnClickedCheckClipLine)
    ON_STN_CLICKED(IDC_STATIC_FILE_LINEPATTERN, &Symbolizer_Linepattern::OnBnClickedButtonFile)
    ON_STN_CLICKED(IDC_STATIC_RESET_LINEPATTERN, &Symbolizer_Linepattern::OnStnClickedStaticResetLinepattern)
END_MESSAGE_MAP()


// Symbolizer_Linepattern message handlers

BOOL Symbolizer_Linepattern::CreateView(CWnd* pParent, CCreateContext* pContext)
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

void Symbolizer_Linepattern::OnInitialUpdate()
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

        // Type
        m_Ctrl_Type.AddString(_T("warp"));
        m_Ctrl_Type.AddString(_T("repeat"));
        m_Ctrl_Type.SetCurSel(1);

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

        // Simplify
        m_Ctrl_SimplifyAlgorithm.AddString(_T("radial-distance"));
        m_Ctrl_SimplifyAlgorithm.AddString(_T("zhao-saalfeld"));
        m_Ctrl_SimplifyAlgorithm.AddString(_T("visvalingam-whyatt"));
        m_Ctrl_SimplifyAlgorithm.AddString(_T("douglas-peucker"));
        m_Ctrl_SimplifyAlgorithm.SetCurSel(1);

        // Alignment
        m_Ctrl_Alignment.AddString(_T("global"));
        m_Ctrl_Alignment.AddString(_T("local"));
        m_Ctrl_Alignment.SetCurSel(0);

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
    
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.default"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_LINEPATTERN_TYPE), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.line-pattern"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.file"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_CLIP_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.clip"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.opacity"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMPLIFY_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.simplify"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SIMPLIFY_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.simplify-algorithm"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SMOOTH_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.smooth"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OFFSET_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.offset"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.geometry-transform"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_TRANSFORM_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.transform"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.comp-op"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_ALIGNMENT_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.alignment"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.stroke-width"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_CAP_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.stroke-linecap"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_JOIN_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.stroke-linejoin"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MITERLIMIT_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.stroke-miterlimit"].c_str()));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHARRAY_LINEPATTERN), CString(m_ToolTip.m_MapTooltip_Doc["LinePatternSymbolizer.stroke-dasharray"].c_str()));

    //// TODO: Use one of the following forms to add controls:
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_DEFAULT_LINEPATTERN), _T("Allows omitting a line symbolizer rule or emitting it with default values."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_LINEPATTERN_TYPE), _T("Sets the way how pattern is rendered. The `warp` options warps the pattern in "
    //                                                            "\ndirection of the geometry. The `repeat` option can be used to repeat pattern "
    //                                                            "\nin an area given by options `stroke-pattern-width`, `stroke-pattern-linecap`, "
    //                                                            "\n`line-pattern-join`, `line-pattern-miterlimit`, `line-pattern-dasharray`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_WIDTH_LINEPATTERN), _T("The width of a line in pixels. Used for rendering line pattern of type `repeat`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OPACITY_LINEPATTERN), _T("Apply an opacity level to the image used for the pattern."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_JOIN_LINEPATTERN), _T("The behavior of lines when joining. Used for rendering line pattern of type `repeat`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_CAP_LINEPATTERN), _T("The display of line endings. Used for rendering line pattern of type `repeat`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_FILE_LINEPATTERN), _T("An image file to be repeated and warped along a line. Accepted formats: svg, jpg, png, tiff, and webp."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_ALIGNMENT_LINEPATTERN), _T("Specify whether to align pattern fills to the feature's geometry (local) or to the map (global)."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DASHARRAY_LINEPATTERN), _T("A pair of length values [a,b], where (a) is the dash length and (b) is the "
    //                                                                "\ngap length respectively. More than two values are supported for more complex "
    //                                                                "\npatterns. Used for rendering line pattern of type `repeat`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_TRANSFORM_LINEPATTERN), _T("Transform line pattern instance with specified function."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MITERLIMIT_LINEPATTERN), _T("The limit on the ratio of the miter length to the stroke-width. "
    //                                                                "\nUsed to automatically convert miter joins to bevel joins for "
    //                                                                "\nsharp angles to avoid the miter extending beyond the thickness "
    //                                                                "\nof the stroking path. Normally will not need to be set, but a "
    //                                                                "\nlarger value can sometimes help avoid jaggy artifacts. Used for "
    //                                                                "\nrendering line pattern of type `repeat`."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_CLIP_LINEPATTERN), _T("Turning on clipping can help performance in the case that the boundaries "
    //                                                            "\nof the geometry extent outside of tile extents. But clipping can result "
    //                                                            "\nin undesirable rendering artifacts in rare cases."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMPLIFY_LINEPATTERN), _T("geometries are simplified by the given tolerance."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_SIMPLIFY_LINEPATTERN), _T("geometries are simplified by the given algorithm."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SMOOTH_LINEPATTERN), _T("Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. "
    //                                                            "\nValues greater than 1 will produce wild, looping geometries."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_OFFSET_LINEPATTERN), _T("Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, "
    //                                                            "\nnegative values move it right (relative to the directionality of the line)."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN), _T("Transform line geometry with specified function."));
    //m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_COMP_OP_LINEPATTERN), _T("Composite operation. This defines how this symbolizer should "
    //                                                                "\nbehave relative to symbolizers atop or below it."));

    // Script
    OnEnKillfocus();
}


void Symbolizer_Linepattern::OnBnClickedCheckDefault()
{
    UpdateData();

    GetDlgItem(IDC_COMBO_LINEPATTERN_TYPE)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_WIDTH_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OPACITY_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_JOIN_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_CAP_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_FILE_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_STATIC_FILE_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_ALIGNMENT_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_DASHARRAY_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_TRANSFORM_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_MITERLIMIT_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_CHECK_CLIP_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_SIMPLIFY_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_SIMPLIFY_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_SMOOTH_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_OFFSET_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN)->EnableWindow(!m_Default);
    GetDlgItem(IDC_COMBO_COMP_OP_LINEPATTERN)->EnableWindow(!m_Default);

    OnEnKillfocus();
}

std::string Symbolizer_Linepattern::SettingsXml()
{
    UpdateData();
    //std::string result = "LineSympolizer";

    int idx = 0;
    tinyxml2::XMLDocument doc;
    auto Element = doc.NewElement("LinepatternSympolizer");

    if (m_Default)
    {
        doc.LinkEndChild(Element);
        tinyxml2::XMLPrinter printer;
        doc.Accept(&printer);

        return std::string(printer.CStr());
    }

    // line-pattern
    CString Type;
    idx = m_Ctrl_Type.GetCurSel();
    m_Ctrl_Type.GetLBText(idx, Type);
    if (Type != _T("warp"))
        Element->SetAttribute("line-pattern", (CT2CA)Type);

    // file
    if (m_File != _T(""))
        Element->SetAttribute("file", (CT2CA)m_File);

    // stroke-width
    if (m_Width != _T("1"))
        Element->SetAttribute("stroke-width", (CT2CA)m_Width);

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

    // stroke-dasharray
    if (m_Dasharray != _T(""))
        Element->SetAttribute("stroke-dasharray", (CT2CA)m_Dasharray);

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

    // alignment
    CString Alignment;
    idx = m_Ctrl_Alignment.GetCurSel();
    m_Ctrl_Alignment.GetLBText(idx, Alignment);
    if (Alignment != _T("global"))
        Element->SetAttribute("alignment", (CT2CA)Alignment);
    
    // geometry-transform
    if (m_GeometryTransform != _T(""))
        Element->SetAttribute("geometry-transform", (CT2CA)m_GeometryTransform);

    // comp-op
    CString CompOp;
    idx = m_Ctrl_CompOp.GetCurSel();
    m_Ctrl_CompOp.GetLBText(idx, CompOp);
    if (CompOp != _T("src-over"))
    {
        //result += " comp-op=" + std::string((CT2CA)CompOp);
        Element->SetAttribute("comp-op", (CT2CA)CompOp);
    }

    doc.LinkEndChild(Element);
    tinyxml2::XMLPrinter printer;
    doc.Accept(&printer);

    return std::string(printer.CStr());
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

void Symbolizer_Linepattern::SettingsXml(std::string str)
{
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*)str.c_str());
    tinyxml2::XMLElement* titleElement = doc.FirstChildElement("LinepatternSympolizer");
    if (titleElement == NULL)
        return;

    if (titleElement->FindAttribute("line-pattern"))
        m_Ctrl_Type.SetCurSel(m_Ctrl_Type.FindStringExact(0, CString(titleElement->Attribute("line-pattern"))));

    if (titleElement->FindAttribute("file"))
        m_File.SetString(CString(titleElement->Attribute("file")));

    if (titleElement->FindAttribute("stroke-width"))
        m_Width.SetString(CString(titleElement->Attribute("stroke-width")));

    if (titleElement->FindAttribute("stroke-opacity"))
        m_Opacity = CString(titleElement->Attribute("stroke-opacity"));

    if (titleElement->FindAttribute("stroke-linejoin"))
        m_Ctrl_Linejoin.SetCurSel(m_Ctrl_Linejoin.FindStringExact(0, CString(titleElement->Attribute("stroke-linejoin"))));

    if (titleElement->FindAttribute("stroke-linecap"))
        m_Ctrl_Linecap.SetCurSel(m_Ctrl_Linecap.FindStringExact(0, CString(titleElement->Attribute("stroke-linecap"))));

    if (titleElement->FindAttribute("stroke-dasharray"))
        m_Dasharray = titleElement->Attribute("stroke-dasharray");

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

    if (titleElement->FindAttribute("geometry-transform"))
        m_GeometryTransform = titleElement->Attribute("geometry-transform");

    if (titleElement->FindAttribute("transform"))
        m_Transform = titleElement->Attribute("transform");

    if (titleElement->FindAttribute("comp-op"))
        m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, CString(titleElement->Attribute("comp-op"))));

    
    UpdateData(false);
}

BOOL Symbolizer_Linepattern::PreTranslateMessage(MSG* pMsg)
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

void Symbolizer_Linepattern::OnEnKillfocus()
{
    UpdateData();
    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Linepattern::OnEnKillfocusFloat()
{
    UpdateData();
    if (!m_ToolTip.isFloat(m_Width))
    {
        m_Width = _T("1");
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_WIDTH_LINEPATTERN)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Opacity))
    {
        m_Opacity.SetString(_T("1"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OPACITY_LINEPATTERN)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_MiterLimit))
    {
        m_MiterLimit.SetString(_T("4"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_MITERLIMIT_LINEPATTERN)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Simplify))
    {
        m_Simplify.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_SIMPLIFY_LINEPATTERN)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Smooth))
    {
        m_Smooth.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_SMOOTH_LINEPATTERN)->SetFocus();
    }

    if (!m_ToolTip.isFloat(m_Offset))
    {
        m_Offset.SetString(_T("0"));
        UpdateData(FALSE);
        AfxMessageBox(_T("Error: non-real value!"));
        GetDlgItem(IDC_EDIT_OFFSET_LINEPATTERN)->SetFocus();
    }

    m_Script.SetString(CString(SettingsXml().c_str()));
    UpdateData(FALSE);
}

void Symbolizer_Linepattern::OnBnClickedCheckClipLine()
{
    OnEnKillfocus();
}


void Symbolizer_Linepattern::OnBnClickedButtonFile()
{
    CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files (*)|*.*||"));
    int iRet = l_fDlg.DoModal();
    m_File = l_fDlg.GetPathName();
    UpdateData(FALSE);
}


void Symbolizer_Linepattern::OnStnClickedStaticResetLinepattern()
{
    // type
    m_Ctrl_Type.SetCurSel(m_Ctrl_Type.FindStringExact(0, _T("warp")));

    // file
    m_File = _T("");

    // width
    m_Width = _T("1");

    // opacity
    m_Opacity = _T("1");

    // linejoin
    m_Ctrl_Linejoin.SetCurSel(m_Ctrl_Linejoin.FindStringExact(0, _T("miter")));

    // stroke-linecap
    CString Linecap;
    m_Ctrl_Linecap.SetCurSel(m_Ctrl_Linecap.FindStringExact(0, _T("butt")));

    // stroke-dasharray
    m_Dasharray = _T("");

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

    // alignment
    m_Ctrl_Alignment.SetCurSel(m_Ctrl_Alignment.FindStringExact(0, _T("global")));

    // geometry-transform
    m_GeometryTransform = _T("");

    // transform
    m_Transform = _T("");

    // comp-op
    m_Ctrl_CompOp.SetCurSel(m_Ctrl_CompOp.FindStringExact(0, _T("src-over")));

    UpdateData(FALSE);
    OnEnKillfocus();
}

