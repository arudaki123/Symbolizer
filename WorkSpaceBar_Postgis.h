#pragma once
#include "Datasources_Postgis.h"

class CWorkSpaceBar_Postgis : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Postgis();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Datasources_Postgis* m_pDatasourcesPostgis;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides
	void EnkillFocus_Datasources_Postgis();
	// Implementation
public:
	virtual ~CWorkSpaceBar_Postgis();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

