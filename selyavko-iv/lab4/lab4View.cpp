
// lab4View.cpp: реализация класса Clab4View
//

#include "pch.h"
#include "framework.h"
#include "MainDlg.h"
#include "UserControllDLG.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "lab4.h"
#endif

#include "lab4Doc.h"
#include "lab4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab4View

IMPLEMENT_DYNCREATE(Clab4View, CView)

BEGIN_MESSAGE_MAP(Clab4View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ADD_USER, &Clab4View::OnAddUser)
	ON_COMMAND(ID_SELECT_USERS, &Clab4View::OnSelectUsers)
END_MESSAGE_MAP()

// Создание или уничтожение Clab4View

Clab4View::Clab4View() noexcept
{
	// TODO: добавьте код создания

}

Clab4View::~Clab4View()
{
}

BOOL Clab4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование Clab4View

void Clab4View::OnDraw(CDC* /*pDC*/)
{
	Clab4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать Clab4View

BOOL Clab4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Clab4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Clab4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика Clab4View

#ifdef _DEBUG
void Clab4View::AssertValid() const
{
	CView::AssertValid();
}

void Clab4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab4Doc* Clab4View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab4Doc)));
	return (Clab4Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений Clab4View


void Clab4View::OnAddUser()
{
	auto pDoc = GetDocument();
	AddDlg test(pDoc->GetCommand());
	test.DoModal();
}


void Clab4View::OnSelectUsers()
{
	auto pDoc = GetDocument();
	UserControllDLG selectDLG(pDoc->GetCommand());
	selectDLG.DoModal();
}
