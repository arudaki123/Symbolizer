#pragma once
#include "Symbolizer_Dot.h"

class CWorkSpaceBar_Dot : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Dot();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Symbolizer_Dot* m_pSymbolizerDot;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Dot();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

