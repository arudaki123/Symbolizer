// BCGPSymbolizerView.h : interface of the CBCGPSymbolizerView class
//


#pragma once


class CBCGPSymbolizerView : public CView
{
protected: // create from serialization only
	CBCGPSymbolizerView();
	DECLARE_DYNCREATE(CBCGPSymbolizerView)

// Attributes
public:
	CBCGPSymbolizerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CBCGPSymbolizerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGPSymbolizerView.cpp
inline CBCGPSymbolizerDoc* CBCGPSymbolizerView::GetDocument() const
	{ return reinterpret_cast<CBCGPSymbolizerDoc*>(m_pDocument); }
#endif

