#pragma once
#include "Datasources_Python.h"

class CWorkSpaceBar_Python : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Python();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Datasources_Python* m_pDatasourcesPython;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Python();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

