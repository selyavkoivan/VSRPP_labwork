
// selyavko-ex2-aView.h: интерфейс класса Cselyavkoex2aView
//

#pragma once


class Cselyavkoex2aView : public CView
{
protected: // создать только из сериализации
	Cselyavkoex2aView() noexcept;
	DECLARE_DYNCREATE(Cselyavkoex2aView)

// Атрибуты
public:
	Cselyavkoex2aDoc* GetDocument() const;

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
	virtual ~Cselyavkoex2aView();
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
};

#ifndef _DEBUG  // версия отладки в selyavko-ex2-aView.cpp
inline Cselyavkoex2aDoc* Cselyavkoex2aView::GetDocument() const
   { return reinterpret_cast<Cselyavkoex2aDoc*>(m_pDocument); }
#endif

