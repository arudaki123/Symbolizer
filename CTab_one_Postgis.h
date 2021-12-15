#pragma once
#include "BCGPDialog.h"
#include "CustomToolTipCtrl.h"

// CTab_one_Postgis dialog

class CTab_one_Postgis : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTab_one_Postgis)

public:
	CTab_one_Postgis(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab_one_Postgis();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_1_POSTGIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
