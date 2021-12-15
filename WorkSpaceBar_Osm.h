#pragma once
#include "Datasources_Osm.h"

class CWorkSpaceBar_Osm : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Osm();

	// Attributes
protected:
	CCreateContext* m_pContext;
	Datasources_Osm* m_pDatasourcesOsm;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Osm();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

};

