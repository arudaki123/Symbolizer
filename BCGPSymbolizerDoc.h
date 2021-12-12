// BCGPSymbolizerDoc.h : interface of the CBCGPSymbolizerDoc class
//


#pragma once


class CBCGPSymbolizerDoc : public CDocument
{
protected: // create from serialization only
	CBCGPSymbolizerDoc();
	DECLARE_DYNCREATE(CBCGPSymbolizerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CBCGPSymbolizerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


