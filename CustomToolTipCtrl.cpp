

#include "stdafx.h"
#include <string>
#include "CustomToolTipCtrl.h"
#include <bitset>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomToolTipCtrl

CCustomToolTipCtrl::CCustomToolTipCtrl()

{
	m_nCurrID = 0;
	WriteTooltipSqlite(_T("Tooltip.db"));
	ReadTooltipSqlite(_T("Tooltip.db"));
	
}

CCustomToolTipCtrl::~CCustomToolTipCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomToolTipCtrl, CBCGPToolTipCtrl)
	//{{AFX_MSG_MAP(CCustomToolTipCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TTN_SHOW, OnShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomToolTipCtrl message handlers

void CCustomToolTipCtrl::OnShow(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_nCurrID = CWnd::FromHandle((HWND)pNMHDR->idFrom)->GetDlgCtrlID();

	switch (m_nCurrID)
	{
	case IDC_CHECK_DEFAULT_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.default"].c_str()); //_T("");
		break;
	case IDC_MFCCOLORBUTTON_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke"].c_str()); //_T("Default-meaning: black and fully opaque (alpha = 1), same as rgb(0,0,0) or rgba(0,0,0,1).");
		break;
	case IDC_EDIT_WIDTH_LINEPATTERN:
	case IDC_EDIT_WIDTH_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-width"].c_str()); //_T("Default-meaning: The line will be rendered 1 pixel wide.");
		break;
	case IDC_EDIT_OPACITY_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-opacity"].c_str()); //_T("Default-meaning: Color is fully opaque.");
		break;
	case IDC_COMBO_JOIN_LINEPATTERN:
	case IDC_COMBO_JOIN_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-linejoin"].c_str()); //_T("Default-meaning: The line joins will be rendered using a miter look.");
		break;
	case IDC_COMBO_CAP_LINEPATTERN:
	case IDC_COMBO_CAP_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-linecap"].c_str()); //_T("Default-meaning: The line endings will be rendered using a butt look.");
		break;
	case IDC_EDIT_GAMMA_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-gamma"].c_str()); //_T("Default-meaning: Fully antialiased.");
		break;
	case IDC_COMBO_GAMMA_METHOD_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-gamma-method"].c_str()); //_T("Default-meaning: pow(x,gamma) is used to calculate pixel gamma, which produces slightly smoother line and polygon antialiasing than the 'linear' method, while other methods are usually only used to disable AA.");
		break;
	case IDC_EDIT_DASHARRAY_LINEPATTERN:
	case IDC_EDIT_DASHARRAY_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-dasharray"].c_str()); //_T("Default-meaning: The line will be drawn without dashes.");
	case IDC_EDIT_DASHOFFSET_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-dashoffset"].c_str()); //_T("Default-meaning: The line will be drawn without dashes.");
		break;
	case IDC_EDIT_MITERLIMIT_LINEPATTERN:
	case IDC_EDIT_MITERLIMIT_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.stroke-miterlimit"].c_str()); //_T("Default-meaning: Will auto-convert miters to bevel line joins when theta is less than 29 degrees as per the SVG spec: 'miterLength / stroke-width = 1 / sin ( theta / 2 )'");
		break;
	case IDC_CHECK_CLIP_LINEPATTERN:
	case IDC_CHECK_CLIP_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.clip"].c_str()); //_T("Default-meaning: The geometry will not be clipped to map bounds before rendering.");
		break;
	case IDC_EDIT_SIMPLIFY_LINEPATTERN:
	case IDC_EDIT_SIMPLIFY_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.simplify"].c_str()); //_T("Default-meaning: geometry will not be simplified.");
		break;
	case IDC_COMBO_SIMPLIFY_LINEPATTERN:
	case IDC_COMBO_SIMPLIFY_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.simplify-algorithm"].c_str()); //_T("Default-meaning: The geometry will be simplified using the radial distance algorithm.");
		break;
	case IDC_EDIT_SMOOTH_LINEPATTERN:
	case IDC_EDIT_SMOOTH_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.smooth"].c_str()); //_T("Default-meaning: No smoothing.");
		break;
	case IDC_EDIT_OFFSET_LINEPATTERN:
	case IDC_EDIT_OFFSET_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.offset"].c_str()); //_T("Default-meaning: Will not be offset.");
		break;
	case IDC_RASTERIZER_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.rasterizer"].c_str()); //_T("Default-meaning: The line will be rendered using the highest quality method rather than the fastest.");
		break;
	case IDC_EDIT_GEOMETRY_TRANSFORM_LINEPATTERN:
	case IDC_EDIT_GEOMETRY_TRANSFORM_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.geometry-transform"].c_str()) +CString(  //_T("Default-meaning: The geometry will not be transformed."
							 "\nFuntions:"	
							 "\n\u2022\t		matrix(v00, v01, v10, v11, v20, v21)"
							 "\n\u2022\t		translate(x, y)"
							 "\n\u2022\t		scale(x, y)"
							 "\n\u2022\t		rotate(x,y,z)"
							 "\n\u2022\t		skewX(x)"
							 "\n\u2022\t		skewY(y)");
		break;
	case IDC_COMBO_COMP_OP_POINT:
	case IDC_COMBO_COMP_OP_RASTER:
	case IDC_COMBO_COMP_OP_LINEPATTERN:
	case IDC_COMBO_COMP_OP_LINE:
		m_strDescription = CString(m_MapTooltip_Default["linesymbolizer.comp-op"].c_str()); //_T("Default-meaning: Add the current symbolizer on top of other symbolizer.");
		break;

	// Line Pattern
	case IDC_COMBO_LINEPATTERN_TYPE:
		m_strDescription = CString(m_MapTooltip_Default["line-patternsymbolizer.line-pattern"].c_str()); //_T("default-meaning: The pattern will be warped along a linear geometry.");
		break;
	case IDC_EDIT_FILE_LINEPATTERN:
		m_strDescription = CString(m_MapTooltip_Default["line-patternsymbolizer.file"].c_str()); //_T("");
		break;
	case IDC_EDIT_OPACITY_LINEPATTERN:
		m_strDescription = CString(m_MapTooltip_Default["line-patternsymbolizer.opacity"].c_str()); //_T("default-meaning: The image is rendered without modifications.");
		break;
	case IDC_EDIT_TRANSFORM_POINT:
	case IDC_EDIT_TRANSFORM_LINEPATTERN:
		m_strDescription = CString(m_MapTooltip_Default["line-patternsymbolizer.transform"].c_str()) + CString(//_T("default-meaning: No transformation."
							 "\nFuntions:"
							 "\n\u2022\t		matrix(v00, v01, v10, v11, v20, v21)"
							 "\n\u2022\t		translate(x, y)"
							 "\n\u2022\t		scale(x, y)"
							 "\n\u2022\t		rotate(x,y,z)"
							 "\n\u2022\t		skewX(x)"
							 "\n\u2022\t		skewY(y)");
		break;
	case IDC_ALIGNMENT_LINEPATTERN:
		m_strDescription = CString(m_MapTooltip_Default["line-patternsymbolizer.alignment"].c_str());
			//_T("default-meaning: Patterns will be aligned to the map when being repeated. This is ideal for seamless patterns in tiled rendering.");
		break;

	// Raster
	case IDC_EDIT_OPACITY_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.opacity"].c_str()); //_T("default-meaning: Color is fully opaque.");
		break;
	case IDC_EDIT_FILTERFACTOR_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.filter-factor"].c_str()); //_T("default-meaning: Allow the datasource to choose appropriate downscaling.");
		break;
	case IDC_COMBO_SCALING_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.scaling"].c_str()); //_T("default-meaning: Nearest neighboor resampling will be used to scale the image to the target size of the map.");
		break;
	case IDC_EDIT_MESHSIZE_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.mesh-size"].c_str()); //_T("default-meaning: Reprojection mesh will be 1/16 of the resolution of the source image.");
		break;
	case IDC_COMBO_DEFAULTMODE_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.default-mode"].c_str()); //_T("default-meaning: A linear interpolation is used to generate colors between the two nearest stops.");
		break;
	case IDC_MFCCOLORBUTTON_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.default-color"].c_str()); //_T("default-meaning: Pixels that are not colored by the colorizer stops will be transparent.");
		break;
	case IDC_EDIT_EPSILON_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.epsilon"].c_str()); //_T("default-meaning: Pixels must very closely match the stop filter otherwise they will not be colored.");
		break;
	case IDC_EDIT_STOP_RASTER:
		m_strDescription = CString(m_MapTooltip_Default["rastersymbolizer.stop"].c_str()); //_T("default-meaning: No colorization will happen without supplying stops.");
		break;

	// Point
	case IDC_EDIT_FILE_POINT:
	case IDC_STATIC_FILE_POINT:
		m_strDescription = CString(m_MapTooltip_Default["pointsysmbolizer.file"].c_str()); //_T("default-meaning: A 4x4 black square will be rendered.");
		break;
	case IDC_CHECK_ALLOWOVERLAP_POINT:
		m_strDescription = CString(m_MapTooltip_Default["pointsysmbolizer.allow-overlap"].c_str()); //_T("default-meaning: Do not allow points to overlap with each other - overlapping markers will not be shown.");
		break;
	case IDC_CHECK_IGNORE_POINT:
		m_strDescription = CString(m_MapTooltip_Default["pointsysmbolizer.ignore-placement"].c_str()); //_T("default-meaning: do not store the bbox of this geometry in the collision detector cache.");
		break;
	case IDC_EDIT_OPACITY_POINT:
		m_strDescription = CString(m_MapTooltip_Default["pointsysmbolizer.opacity"].c_str()); //_T("default-meaning: Fully opaque.");
		break;
	case IDC_COMBO_PLACEMENT_POINT:
		m_strDescription = CString(m_MapTooltip_Default["pointsysmbolizer.placement"].c_str()); //_T("default-meaning: The centroid of the geometry will be used to place the point.");
		break;

	// Dot
	case IDC_MFCCOLORBUTTON_DOT:
		m_strDescription = CString(m_MapTooltip_Default["dotsymbolizer.fill"].c_str()); //_T("default-meaning: The dot fill color is gray.");
		break;
	case IDC_EDIT_OPACITY_DOT:
		m_strDescription = CString(m_MapTooltip_Default["dotsymbolizer.opacity"].c_str()); //_T("default-meaning: The opacity of the dot.");
		break;
	case IDC_EDIT_WIDTH_DOT:
		m_strDescription = CString(m_MapTooltip_Default["dotsymbolizer.width"].c_str()); //_T("default-meaning: The marker width is 1 pixel.");
		break;
	case IDC_EDIT_HEIGHT_DOT:
		m_strDescription = CString(m_MapTooltip_Default["dotsymbolizer.height"].c_str()); //_T("default-meaning: The marker height is 1 pixels.");
		break;
	case IDC_COMBO_COMP_OP_DOT:
		m_strDescription = CString(m_MapTooltip_Default["dotsymbolizer.comp-op"].c_str()); //_T("default-meaning: Add the current layer on top of other layers.");
		break;

	default:
		m_strDescription.Empty();
	}

	CBCGPToolTipCtrl::OnShow(pNMHDR, pResult);
}

CSize CCustomToolTipCtrl::GetIconSize()
{
	if (m_imageOK.GetCount() == 0)
	{
		//m_imageOK.Load(IDB_OK);
		m_imageOK.SetSingleImage();

		globalUtils.ScaleByDPI(m_imageOK);
	}

	if (m_imageCancel.GetCount() == 0)
	{
		//m_imageCancel.Load(IDB_CANCEL);
		m_imageCancel.SetSingleImage();

		globalUtils.ScaleByDPI(m_imageCancel);
	}

	return m_imageOK.GetImageSize();	// Both icons have the same size
}

BOOL CCustomToolTipCtrl::OnDrawIcon(CDC* pDC, CRect rectImage)
{
	switch (m_nCurrID)
	{
	case IDOK:
		m_imageOK.DrawEx(pDC, rectImage, 0);
		return TRUE;

	case IDCANCEL:
		m_imageCancel.DrawEx(pDC, rectImage, 0);
		return TRUE;
	}

	return FALSE;
}

bool CCustomToolTipCtrl::isFloat(CString myString) {
	std::string str((CT2CA)myString);
	if (str == "")
		return true;
	size_t count = std::count_if(str.begin(), str.end(), [](char c) {return c == '.'; });
	if (count > 1)
		return false;
	std::istringstream iss(str);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}


BOOL CCustomToolTipCtrl::ReadTooltipSqlite(CString path)
{
	sqlite3* db;
	int rc;
	char* zErrMsg = 0;
	char* sql;
	sqlite3_stmt* stmt;

	/* Open database */
	rc = sqlite3_open((CT2A)path, &db);
	if (rc) {
		AfxMessageBox(L"Can't open database tooltip");
		return(0);
	}

	/* Create SQL statement */
	sql = "SELECT * from SYMBOLIZER";

	 // compile sql statement to binary
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		AfxMessageBox(CString("ERROR: while compiling sql: ") + CString(sqlite3_errmsg(db)));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return FALSE;
	}

	// execute sql statement, and while there are rows returned, print ID
	int ret_code = 0;
	while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW) 
	{
		std::string value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		value.replace(value.begin(), value.begin() + 5, "");
		value.replace(value.end() - 6, value.end(), "");
		size_t pos = value.find('|');
		std::string str_Doc = value.substr(0, pos);
		m_MapTooltip_Doc[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = str_Doc;
		if (pos >= value.size())
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = "";
		else
		{
			value.erase(0, pos + 1);
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = value;
		}
		//AfxMessageBox(CString("TEST: ID = ") + CString(sqlite3_column_text(stmt, 0)) + CString(sqlite3_column_text(stmt, 1)));
	}
	if (ret_code != SQLITE_DONE) 
	{
		//this error handling could be done better, but it works
		AfxMessageBox(CString("ERROR: while performing sql: ") + CString(sqlite3_errmsg(db)));
	}

	sqlite3_close(db);
	return 0;

}

BOOL CCustomToolTipCtrl::WriteTooltipSqlite(CString path)
{
	sqlite3* db;
	int rc;
	char* zErrMsg = 0;
	char* sql;
	FILE* fp;

	/* Open database */
	rc = sqlite3_open((CT2A)path, &db);
	if (rc) {
		AfxMessageBox(L"Can't open database tooltip");
		return(0);
	}

	/* Create SQL statement */
	sql = "CREATE TABLE SYMBOLIZER("  \
		"TOOLTIPCode TEXT PRIMARY KEY NOT NULL,"
		"TooltipContent BLOB);";
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		AfxMessageBox(CString(_T("SQL error: ") + CString(zErrMsg)));
		sqlite3_free(zErrMsg);
	}

	fopen_s(&fp, "reference.json", "r");
	
	if (fp != NULL) {
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document res_object;
		res_object.ParseStream(is);
		fclose(fp);
		rapidjson::Value& symbolizers = res_object["symbolizers"];
		assert(symbolizers.IsObject());
		//const rapidjson::Value& shield = symbolizers["shield"];

		//assert(shield.IsObject());
		std::string Name_Symbolizers[] = { "line", "line-pattern", "raster", "point", "dot" };
		for (auto name_sym : Name_Symbolizers)
		{
			const rapidjson::Value& shield = symbolizers[name_sym.c_str()];
			for (rapidjson::Value::ConstMemberIterator itr = shield.MemberBegin(); itr != shield.MemberEnd(); ++itr)
			{   //iterate through object   
				const rapidjson::Value& Attribute = shield[itr->name.GetString()]; //make object value
				assert(Attribute.IsObject());
				std::string str_name = itr->name.GetString();

				const rapidjson::Value& doc = Attribute["doc"];
				assert(doc.IsString());
				std::string str_doc = doc.GetString();

				/*std::string str_default_value;
				const rapidjson::Value& default_value = Attribute["default-value"];
				if (default_value.IsString()) {
					assert(default_value.IsString());
					str_default_value = default_value.GetString();

				}
				else if (default_value.IsFloat()) {
					assert(default_value.IsFloat());
					float f = default_value.GetFloat();
					std::ostringstream ss;
					ss << f;
					str_default_value = std::string(ss.str());

				}
				else if (default_value.IsInt()) {
					assert(default_value.IsInt());
					int  d = default_value.GetInt();
					std::ostringstream ss;
					ss << d;
					str_default_value = std::string(ss.str());

				}
				else if (default_value.IsBool()) {
					assert(default_value.IsBool());
					bool  b = default_value.GetBool();
					const char* str_bool = b ? "true" : "false";
					str_default_value = std::string(str_bool);

				}
				else {
					str_default_value = std::string(" ");
				}*/

				std::string TooltipContent;
				auto it = Attribute.FindMember("default-meaning");
				if (it != Attribute.MemberEnd())
				{


					const rapidjson::Value& default_meaning = Attribute["default-meaning"];
					assert(default_meaning.IsString());
					std::string str_default_meaning = default_meaning.GetString();

					/*std::string str_type;
					const rapidjson::Value& m_type = Attribute["type"];
					if (m_type.IsString()) {
						assert(m_type.IsString());
						str_type = m_type.GetString();
					}
					else {
						str_type = std::string("[select]");
					}*/

					TooltipContent = "<div>" + str_doc + " | Default meaning: " + str_default_meaning + "</div>";
				}
				else 
					TooltipContent = "<div>" + str_doc + "</div>";

				std::string str_TOOLTIPCode = "'" + name_sym + "symbolizer." + str_name + "'";
				//TooltipContent = strToBinary(TooltipContent);
				std::string insertQuery = "INSERT INTO SYMBOLIZER (TOOLTIPCode, TooltipContent) VALUES(" + str_TOOLTIPCode + ", ?);";

				sqlite3_stmt* insertStmt = NULL;
				int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, NULL);
				if (rc != SQLITE_OK) {
					MessageBox(CString(sqlite3_errmsg(db)));
				}
				else {
					rc = sqlite3_bind_blob(insertStmt, 1, TooltipContent.c_str(), TooltipContent.size(), SQLITE_STATIC);
					if (rc != SQLITE_OK) {
						MessageBox(CString(sqlite3_errmsg(db)));
					}
					else {
						if (sqlite3_step(insertStmt) != SQLITE_DONE) {
							MessageBox(CString(sqlite3_errmsg(db)));
						}
					}
				}

			}
		}
	}

	/* Create SQL statement */
	sql = "CREATE TABLE DATASOURCES("  \
		"TOOLTIPCode TEXT PRIMARY KEY NOT NULL,"
		"TooltipContent BLOB);";
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		AfxMessageBox(CString(_T("SQL error: ") + CString(zErrMsg)));
		sqlite3_free(zErrMsg);
	}

	fopen_s(&fp, "datasources.json", "r");

	
	if (fp != NULL) {
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document res_object;
		res_object.ParseStream(is);
		fclose(fp);
		rapidjson::Value& symbolizers = res_object["datasources"];
		assert(symbolizers.IsObject());
		//const rapidjson::Value& shield = symbolizers["shield"];

		//assert(shield.IsObject());
		std::string Name_Symbolizers[] = { "ogr", "osm", "postgis", "python" };
		for (auto name_sym : Name_Symbolizers)
		{
			const rapidjson::Value& shield = symbolizers[name_sym.c_str()];
			for (rapidjson::Value::ConstMemberIterator itr = shield.MemberBegin(); itr != shield.MemberEnd(); ++itr)
			{   //iterate through object   
				const rapidjson::Value& Attribute = shield[itr->name.GetString()]; //make object value
				assert(Attribute.IsObject());
				std::string str_name = itr->name.GetString();

				const rapidjson::Value& doc = Attribute["doc"];
				assert(doc.IsString());
				std::string str_doc = doc.GetString();

				const rapidjson::Value& default_meaning = Attribute["default-meaning"];
				assert(default_meaning.IsString());
				std::string str_default_meaning = default_meaning.GetString();

				std::string TooltipContent = "<div>" + str_doc + " | Default meaning: " + str_default_meaning + "</div>";

				std::string str_TOOLTIPCode = "'" + name_sym + "datasources." + str_name + "'";
				//TooltipContent = strToBinary(TooltipContent);
				std::string insertQuery = "INSERT INTO DATASOURCES (TOOLTIPCode, TooltipContent) VALUES(" + str_TOOLTIPCode + ", ?);";

				sqlite3_stmt* insertStmt = NULL;
				int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, NULL);
				if (rc != SQLITE_OK) {
					MessageBox(CString(sqlite3_errmsg(db)));
				}
				else {
					rc = sqlite3_bind_blob(insertStmt, 1, TooltipContent.c_str(), TooltipContent.size(), SQLITE_STATIC);
					if (rc != SQLITE_OK) {
						MessageBox(CString(sqlite3_errmsg(db)));
					}
					else {
						if (sqlite3_step(insertStmt) != SQLITE_DONE) {
							MessageBox(CString(sqlite3_errmsg(db)));
						}
					}
				}

			}
		}
	}

	//"TooltipDefault BLOB);";

	/* Execute SQL statement */



	/*sqlite3_stmt* stmt = NULL;

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.default', ?)", -1, &stmt, NULL);
	std::string buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke', ?)", -1, &stmt, NULL);
	buffer = "<div>The color of a drawn line.| default-meaning: black and fully opaque (alpha = 1), same as rgb(0,0,0) or rgba(0,0,0,1).<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-width', ?)", -1, &stmt, NULL);
	buffer = "<div>The width of a line in pixels.| default-meaning: The line will be rendered 1 pixel wide.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The opacity of a line.| default-meaning: Color is fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-linejoin',  ?)", -1, &stmt, NULL);
	buffer = "<div>The behavior of lines when joining.| default-meaning: The line joins will be rendered using a miter look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-linecap',  ?)", -1, &stmt, NULL);
	buffer = "<div>The display of line endings.| default-meaning: The line endings will be rendered using a butt look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-gamma',  ?)", -1, &stmt, NULL);
	buffer = "<div>Level of antialiasing of stroke line.| default-meaning: Fully antialiased.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-gamma-method',  ?)", -1, &stmt, NULL);
	buffer = "<div>An Antigrain Geometry specific rendering hint to control the quality of antialiasing. Under the hood in Mapnik this "
		"\nmethod is used in combination with the `gamma` value (which defaults to 1). The methods are in the AGG source at"
		"\n https://github.com/mapnik/mapnik/blob/master/deps/agg/include/agg_gamma_functions."
		"| default-meaning: pow(x,gamma) is used to calculate pixel gamma, which produces slightly smoother line and polygon antialiasing than the `linear` method, while other methods are usually only used to disable AA.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-dasharray',  ?)", -1, &stmt, NULL);
	buffer = "<div>A pair of length values [a,b], where (a) is the dash length and (b) is the gap length respectively. "
		"\nMore than two values are supported for more complex patterns.| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-dashoffset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Valid parameter but not currently used in renderers (only exists for experimental svg support in Mapnik which is not yet enabled)."
		"| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-miterlimit',  ?)", -1, &stmt, NULL);
	buffer = "<div>The limit on the ratio of the miter length to the stroke-width. Used to automatically convert miter joins "
		"\nto bevel joins for sharp angles to avoid the miter extending beyond the thickness of the stroking path. "
		"\nNormally will not need to be set, but a larger value can sometimes help avoid jaggy artifacts."
		"| default-meaning: Will auto-convert miters to bevel line joins when theta is less than 29 degrees as per the SVG spec: `miterLength / stroke-width = 1 / sin ( theta / 2 )`.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.clip',  ?)", -1, &stmt, NULL);
	buffer = "<div>Turning on clipping can help performance in the case that the boundaries of the geometry extent "
		"\noutside of tile extents. But clipping can result in undesirable rendering artifacts in rare cases."
		"| default-meaning: The geometry will not be clipped to map bounds before rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.simplify',  ?)", -1, &stmt, NULL);
	buffer = "<div>Simplify geometries by the given tolerance.| default-meaning: geometry will not be simplified.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.simplify-algorithm',  ?)", -1, &stmt, NULL);
	buffer = "<div>Simplify geometries by the given algorithm.| default-meaning: The geometry will be simplified using the radial distance algorithm.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.smooth',  ?)", -1, &stmt, NULL);
	buffer = "<div>Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. "
		"\nValues greater than 1 will produce wild, looping geometries.| default-meaning: No smoothing.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.offset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, "
		"\nnegative values move it right (relative to the directionality of the line).| default-meaning: Will not be offset.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.rasterizer',  ?)", -1, &stmt, NULL);
	buffer = "<div>Exposes an alternate AGG rendering method that sacrifices some accuracy for speed."
		"| default-meaning: The line will be rendered using the highest quality method rather than the fastest.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.geometry-transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line geometry with specified function.| default-meaning: The geometry will not be transformed.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should behave relative to symbolizers atop or below it."
		"| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.line-pattern',  ?)", -1, &stmt, NULL);
	buffer = "<div>Sets the way how pattern is rendered. The `warp` options warps the pattern in "
		"\ndirection of the geometry. The `repeat` option can be used to repeat pattern "
		"\nin an area given by options `stroke-pattern-width`, `stroke-pattern-linecap`, "
		"\n`line-pattern-join`, `line-pattern-miterlimit`, `line-pattern-dasharray`.| default-meaning: The pattern will be warped along a linear geometry.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.file',  ?)", -1, &stmt, NULL);
	buffer = "<div>An image file to be repeated and warped along a line. Accepted formats: svg, jpg, png, tiff, and webp.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.clip',  ?)", -1, &stmt, NULL);
	buffer = "<div>Turning on clipping can help performance in the case that the boundaries "
		"\nof the geometry extent outside of tile extents. But clipping can result "
		"\nin undesirable rendering artifacts in rare cases.| default-meaning: The geometry will not be clipped to map bounds before rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>Apply an opacity level to the image used for the pattern.| default-meaning: The image is rendered without modifications.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.simplify',  ?)", -1, &stmt, NULL);
	buffer = "<div>geometries are simplified by the given tolerance.| default-meaning: geometry will not be simplified.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.simplify-algorithm',  ?)", -1, &stmt, NULL);
	buffer = "<div>geometries are simplified by the given algorithm.| default-meaning: The geometry will be simplified using the radial distance algorithm.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.smooth',  ?)", -1, &stmt, NULL);
	buffer = "<div>Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. "
		"\nValues greater than 1 will produce wild, looping geometries.| default-meaning: No smoothing.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.offset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, "
		"\nnegative values move it right (relative to the directionality of the line).| default-meaning: The line will not be offset.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.geometry-transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line geometry with specified function.| default-meaning: The geometry will not be transformed.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line pattern instance with specified function.| default-meaning: No transformation.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should "
		"\nbehave relative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.alignment',  ?)", -1, &stmt, NULL);
	buffer = "<div>Specify whether to align pattern fills to the feature`s geometry (local) or to the map (global)."
		"| default-meaning: Patterns will be aligned to the map when being repeated. This is ideal for seamless patterns in tiled rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-width',  ?)", -1, &stmt, NULL);
	buffer = "<div>The width of a line in pixels. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line will be rendered 1 pixel wide.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-linecap',  ?)", -1, &stmt, NULL);
	buffer = "<div>The display of line endings. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line endings will be rendered using a butt look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-linejoin',  ?)", -1, &stmt, NULL);
	buffer = "<div>The behavior of lines when joining. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line joins will be rendered using a miter look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-miterlimit',  ?)", -1, &stmt, NULL);
	buffer = "<div>The limit on the ratio of the miter length to the stroke-width. "
		"\nUsed to automatically convert miter joins to bevel joins for "
		"\nsharp angles to avoid the miter extending beyond the thickness "
		"\nof the stroking path. Normally will not need to be set, but a "
		"\nlarger value can sometimes help avoid jaggy artifacts. Used for "
		"\nrendering line pattern of type `repeat`.| default-meaning: Will auto-convert miters to bevel line joins when theta is less than 29 degrees as per the SVG spec: `miterLength / stroke-width = 1 / sin ( theta / 2 )`.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-dasharray',  ?)", -1, &stmt, NULL);
	buffer = "<div>A pair of length values [a,b], where (a) is the dash length and (b) is the "
		"\ngap length respectively. More than two values are supported for more complex "
		"\npatterns. Used for rendering line pattern of type `repeat`.| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The opacity of the raster symbolizer on top of other symbolizers.| default-meaning: Color is fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.filter-factor',  ?)", -1, &stmt, NULL);
	buffer = "<div>This is used by the Raster or Gdal datasources to pre-downscale "
		"\nimages using overviews. Higher numbers can sometimes cause much "
		"\nbetter scaled image output, at the cost of speed.| default-meaning: Allow the datasource to choose appropriate downscaling.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.scaling',  ?)", -1, &stmt, NULL);
	buffer = "<div>The scaling algorithm used to making different resolution versions of this "
		"\nraster layer. Bilinear is a good compromise between speed and accuracy, "
		"\nwhile lanczos gives the highest quality.| default-meaning: Nearest neighboor resampling will be used to scale the image to the target size of the map.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.mesh-size',  ?)", -1, &stmt, NULL);
	buffer = "<div>A reduced resolution mesh is used for raster reprojection, and the total "
		"\nimage size is divided by the mesh-size to determine the quality of that "
		"\nmesh. Values for mesh-size larger than the default will result in faster "
		"\nreprojection but might lead to distortion.| default-meaning: Reprojection mesh will be 1/16 of the resolution of the source image.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should behave "
		"\nrelative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default-mode',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be either `discrete`, `linear` or `exact`. "
		"\nIf it is not specified then the default is `linear`.| default-meaning: A linear interpolation is used to generate colors between the two nearest stops.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default-color',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be any color. Sets the color that is applied to "
		"\nall values outside of the range of the colorizer-stops. "
		"\nIf not supplied pixels will be fully transparent.| default-meaning: Pixels that are not colored by the colorizer stops will be transparent.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.epsilon',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be any positive floating point value and will be used as "
		"\na tolerance in floating point comparisions. The higher the value "
		"\nthe more likely a stop will match and color data.| default-meaning: Pixels must very closely match the stop filter otherwise they will not be colored.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.stop',  ?)", -1, &stmt, NULL);
	buffer = "<div>Assigns raster data values to colors. Stops must be listed in ascending order, "
		"\nand contain at a minimum the value and the associated color. You can also "
		"\ninclude the color-mode as a third argument, like `stop(100,#fff,exact)`.| default-meaning: No colorization will happen without supplying stops.<div>";;
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.file',  ?)", -1, &stmt, NULL);
	buffer = "<div>Image file to represent a point. Accepted formats: svg, jpg, png, tiff, and webp."
		"| default-meaning: A 4x4 black square will be rendered.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.allow-overlap',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control whether overlapping points are shown or hidden.| default-meaning: Do not allow points to overlap with each other - overlapping markers will not be shown.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.ignore-placement',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control whether the placement of the feature will prevent the placement of other features."
		"| default-meaning: do not store the bbox of this geometry in the collision detector cache.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>A value from 0 to 1 to control the opacity of the point.| default-meaning: Fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.placement',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control how this point should be placed. Centroid calculates the geometric center of a polygon, "
		"\nwhich can be outside of it, while interior always places inside of a polygon."
		"| default-meaning: The centroid of the geometry will be used to place the point.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform point instance with specified function. Ignores map scale factor.| default-meaning: No transformation.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.comp_op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer "
		"\nshould behave relative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a dot symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.fill',  ?)", -1, &stmt, NULL);
	buffer = "<div>The color of the area of the dot.| default-meaning: The dot fill color is gray.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The overall opacity of the dot.| default-meaning: The opacity of the dot.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.width',  ?)", -1, &stmt, NULL);
	buffer = "<div>The width of the dot in pixels.| default-meaning: The marker width is 1 pixel.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.height',  ?)", -1, &stmt, NULL);
	buffer = "<div>The height of the dot in pixels.| default-meaning: The marker height is 1 pixels.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this layer should behave relative to layers atop or below it."
		"| default-meaning: Add the current layer on top of other layers.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);


	
	if (rc != SQLITE_DONE)
		AfxMessageBox(CString(sqlite3_errmsg(db)));*/

	sqlite3_close(db);
	return 0;
}