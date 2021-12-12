// workspacebar.h : interface of the CWorkSpaceBar_Line class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Symbolizer_Line.h"

class CWorkSpaceBar_Line : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Line();

// Attributes
protected:
	CCreateContext* m_pContext;
	Symbolizer_Line* m_pSymbolizerLine;

// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
// Overrides

// Implementation
public:
	virtual ~CWorkSpaceBar_Line();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
