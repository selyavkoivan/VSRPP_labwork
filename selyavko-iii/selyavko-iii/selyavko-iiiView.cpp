
// selyavko-iiiView.cpp: реализация класса CselyavkoiiiView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "selyavko-iii.h"
#endif

#include "selyavko-iiiDoc.h"
#include "selyavko-iiiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CselyavkoiiiView

IMPLEMENT_DYNCREATE(CselyavkoiiiView, CView)

BEGIN_MESSAGE_MAP(CselyavkoiiiView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CselyavkoiiiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CselyavkoiiiView

CselyavkoiiiView::CselyavkoiiiView() noexcept
{
	// TODO: добавьте код создания

}

CselyavkoiiiView::~CselyavkoiiiView()
{
}

BOOL CselyavkoiiiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CselyavkoiiiView

void CselyavkoiiiView::OnDraw(CDC* /*pDC*/)
{
	CselyavkoiiiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CselyavkoiiiView


void CselyavkoiiiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CselyavkoiiiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CselyavkoiiiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CselyavkoiiiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CselyavkoiiiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CselyavkoiiiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CselyavkoiiiView

#ifdef _DEBUG
void CselyavkoiiiView::AssertValid() const
{
	CView::AssertValid();
}

void CselyavkoiiiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CselyavkoiiiDoc* CselyavkoiiiView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CselyavkoiiiDoc)));
	return (CselyavkoiiiDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CselyavkoiiiView
