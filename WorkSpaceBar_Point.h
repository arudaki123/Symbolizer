#pragma once
#include "Symbolizer_Point.h"


class CWorkSpaceBar_Point : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Point();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Symbolizer_Point* m_pSymbolizerPoint;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Point();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

