// BCGPSymbolizerDoc.cpp : implementation of the CBCGPSymbolizerDoc class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"

#include "BCGPSymbolizerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBCGPSymbolizerDoc

IMPLEMENT_DYNCREATE(CBCGPSymbolizerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPSymbolizerDoc, CDocument)
END_MESSAGE_MAP()


// CBCGPSymbolizerDoc construction/destruction

CBCGPSymbolizerDoc::CBCGPSymbolizerDoc()
{
	// TODO: add one-time construction code here

}

CBCGPSymbolizerDoc::~CBCGPSymbolizerDoc()
{
}

BOOL CBCGPSymbolizerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CBCGPSymbolizerDoc serialization

void CBCGPSymbolizerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CBCGPSymbolizerDoc diagnostics

#ifdef _DEBUG
void CBCGPSymbolizerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPSymbolizerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBCGPSymbolizerDoc commands
