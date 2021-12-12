#pragma once
#include <BCGPDockingControlBar.h>
#include "Symbolizer_Raster.h"

class CWorkSpaceBar_Raster : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar_Raster();

	// Attributes
protected:
	CCreateContext*			m_pContext;
	Symbolizer_Raster*		m_pSymbolizerRaster;

	// Operations
public:
	std::string SettingsXml();
	void SettingsXml(std::string);
	// Overrides

	// Implementation
public:
	virtual ~CWorkSpaceBar_Raster();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

