
// selyavko-ex2-aView.cpp: реализация класса Cselyavkoex2aView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "selyavko-ex2-a.h"
#endif

#include "selyavko-ex2-aDoc.h"
#include "selyavko-ex2-aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cselyavkoex2aView

IMPLEMENT_DYNCREATE(Cselyavkoex2aView, CView)

BEGIN_MESSAGE_MAP(Cselyavkoex2aView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cselyavkoex2aView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение Cselyavkoex2aView

Cselyavkoex2aView::Cselyavkoex2aView() noexcept
{
	// TODO: добавьте код создания

}

Cselyavkoex2aView::~Cselyavkoex2aView()
{
}

BOOL Cselyavkoex2aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование Cselyavkoex2aView

void Cselyavkoex2aView::OnDraw(CDC* /*pDC*/)
{
	Cselyavkoex2aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать Cselyavkoex2aView


void Cselyavkoex2aView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cselyavkoex2aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Cselyavkoex2aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Cselyavkoex2aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void Cselyavkoex2aView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cselyavkoex2aView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика Cselyavkoex2aView

#ifdef _DEBUG
void Cselyavkoex2aView::AssertValid() const
{
	CView::AssertValid();
}

void Cselyavkoex2aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cselyavkoex2aDoc* Cselyavkoex2aView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cselyavkoex2aDoc)));
	return (Cselyavkoex2aDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений Cselyavkoex2aView
