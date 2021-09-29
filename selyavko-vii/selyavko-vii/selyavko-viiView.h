
// selyavko-viiView.h : interface of the CselyavkoviiView class
//

#pragma once


class CselyavkoviiView : public CView
{
protected: // create from serialization only
	CselyavkoviiView();
	DECLARE_DYNCREATE(CselyavkoviiView)

// Attributes
public:
	CselyavkoviiDoc* GetDocument() const;

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
	virtual ~CselyavkoviiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStartthread();







	afx_msg void OnThreadStartthread1();
	afx_msg void OnThreadSemaphore();
	afx_msg void OnThreadStartthread2();
	afx_msg void OnThreadStopthread2();
	afx_msg void OnCriticalsection();
	afx_msg void OnLabworkStart();
};

#ifndef _DEBUG  // debug version in selyavko-viiView.cpp
inline CselyavkoviiDoc* CselyavkoviiView::GetDocument() const
   { return reinterpret_cast<CselyavkoviiDoc*>(m_pDocument); }
#endif

