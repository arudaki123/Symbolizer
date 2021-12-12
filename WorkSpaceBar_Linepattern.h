// workspacebar.h : interface of the CWorkSpaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Symbolizer_Linepattern.h"

class CWorkSpaceBar_Linepattern : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Linepattern();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Symbolizer_Linepattern* m_pSymbolizerLinepattern;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Linepattern();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
