
// MiniDrawView.h: интерфейс класса CMiniDrawView
//
#include <vector>
using namespace std;
#pragma once


class CMiniDrawView : public CView
{
protected:

	
	CString m_ClassName;
	int m_Dragging;
	HCURSOR m_HCross;
	CPoint m_PointOld;
	CPoint m_PointOrigin;
	bool figureType;
	CLine* nextStep;

public:
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected: // создать только из сериализации
	CMiniDrawView() noexcept;
	DECLARE_DYNCREATE(CMiniDrawView)

// Атрибуты
public:
	CMiniDrawDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMiniDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnOptionsColor();
public:
	COLORREF m_color;



	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawLine();
	afx_msg void OnColor();
};

#ifndef _DEBUG  // версия отладки в MiniDrawView.cpp
inline CMiniDrawDoc* CMiniDrawView::GetDocument() const
   { return reinterpret_cast<CMiniDrawDoc*>(m_pDocument); }
#endif

