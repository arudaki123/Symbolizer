#pragma once
#include "Datasources_Ogr.h"

class CWorkSpaceBar_Ogr : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Ogr();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Datasources_Ogr* m_pDatasourcesOgr;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Ogr();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

