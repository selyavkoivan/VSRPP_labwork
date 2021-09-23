
// lab4View.h: интерфейс класса Clab4View
//

#pragma once


class Clab4View : public CView
{
protected: // создать только из сериализации
	Clab4View() noexcept;
	DECLARE_DYNCREATE(Clab4View)

// Атрибуты
public:
	Clab4Doc* GetDocument() const;

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
	virtual ~Clab4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddUser();
	afx_msg void OnSelectUsers();
};

#ifndef _DEBUG  // версия отладки в lab4View.cpp
inline Clab4Doc* Clab4View::GetDocument() const
   { return reinterpret_cast<Clab4Doc*>(m_pDocument); }
#endif

