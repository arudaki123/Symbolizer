// BCGPSymbolizerView.cpp : implementation of the CBCGPSymbolizerView class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"

#include "BCGPSymbolizerDoc.h"
#include "BCGPSymbolizerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBCGPSymbolizerView

IMPLEMENT_DYNCREATE(CBCGPSymbolizerView, CView)

BEGIN_MESSAGE_MAP(CBCGPSymbolizerView, CView)
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBCGPSymbolizerView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_MESSAGE(WM_PRINTCLIENT, &CBCGPSymbolizerView::OnPrintClient)
END_MESSAGE_MAP()

// CBCGPSymbolizerView construction/destruction

CBCGPSymbolizerView::CBCGPSymbolizerView()
{
	// TODO: add construction code here

}

CBCGPSymbolizerView::~CBCGPSymbolizerView()
{
}

BOOL CBCGPSymbolizerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBCGPSymbolizerView drawing

void CBCGPSymbolizerView::OnDraw(CDC* /*pDC*/)
{
	CBCGPSymbolizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CBCGPSymbolizerView printing

void CBCGPSymbolizerView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CBCGPSymbolizerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPSymbolizerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGPSymbolizerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBCGPSymbolizerView diagnostics

#ifdef _DEBUG
void CBCGPSymbolizerView::AssertValid() const
{
	CView::AssertValid();
}

void CBCGPSymbolizerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBCGPSymbolizerDoc* CBCGPSymbolizerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPSymbolizerDoc)));
	return (CBCGPSymbolizerDoc*)m_pDocument;
}
#endif //_DEBUG


// CBCGPSymbolizerView message handlers

LRESULT CBCGPSymbolizerView::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if ((lp & PRF_CLIENT) == PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC)wp);
		ASSERT_VALID(pDC);

		OnDraw(pDC);
	}

	return 0;
}


void CBCGPSymbolizerView::OnContextMenu(CWnd*, CPoint point)
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}

	theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}
