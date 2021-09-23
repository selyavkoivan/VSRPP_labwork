
// MiniDrawView.cpp: реализация класса CMiniDrawView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MiniDraw.h"
#endif

#include "MiniDrawDoc.h"
#include "MiniDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniDrawView

IMPLEMENT_DYNCREATE(CMiniDrawView, CView)

BEGIN_MESSAGE_MAP(CMiniDrawView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMiniDrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CMiniDrawView::OnDrawRectangle)
//	ON_COMMAND(ID_DUMMY_COMPILE, &CMiniDrawView::OnDummyCompile)
	ON_COMMAND(ID_DRAW_LINE, &CMiniDrawView::OnDrawLine)
	ON_COMMAND(ID_COLOR, &CMiniDrawView::OnColor)
END_MESSAGE_MAP()

// Создание или уничтожение CMiniDrawView



CMiniDrawView::~CMiniDrawView()
{
}



// Рисование CMiniDrawView

void CMiniDrawView::OnDraw(CDC* pDC)
{
	CMiniDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	int top = pDoc->top;
	for (int i = 0; i < top; i++)
	{
		pDoc->GetLine(i)->Draw(pDC);
	}
}


// Печать CMiniDrawView


void CMiniDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMiniDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMiniDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMiniDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CMiniDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMiniDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CMiniDrawView

#ifdef _DEBUG
void CMiniDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMiniDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMiniDrawDoc* CMiniDrawView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniDrawDoc)));
	return (CMiniDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMiniDrawView

CMiniDrawView::CMiniDrawView() noexcept
{
	m_Dragging = 0;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}


void CMiniDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_PointOld = point;
	m_PointOrigin = point;
	SetCapture();
	m_Dragging = 1;
	RECT Rect;
	GetClientRect(&Rect);
	ClientToScreen(&Rect);
	::ClipCursor(&Rect);
	CView::OnLButtonDown(nFlags, point);

}
void CMiniDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	::SetCursor(m_HCross);
	if (m_Dragging)
	{
		CClientDC ClientDC(this);
	
		CBrush* brush;
		brush = new CBrush(m_color);
		ClientDC.SelectObject(brush);
		
		CPen aPen;
		aPen.CreatePen(PS_SOLID, 2, m_color);
		ClientDC.SelectObject(&aPen);
		

		ClientDC.SetROP2(R2_NOT);

		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(m_PointOld);

		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(point);

		m_PointOld = point;
	}
	CView::OnMouseMove(nFlags, point);
}
void CMiniDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Dragging)
	{
		m_Dragging = 0;
		::ReleaseCapture();
		::ClipCursor(NULL);
		CClientDC ClientDC(this);
		
		
	
		CBrush* brush;
		brush = new CBrush(m_color);
		ClientDC.SelectObject(brush);
		
		CPen aPen;
		aPen.CreatePen(PS_SOLID, 2, m_color);
		ClientDC.SelectObject(&aPen);

		ClientDC.SetROP2(R2_NOT);
		ClientDC.SetROP2(R2_COPYPEN);

		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(m_PointOld);

		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(point);


		CMiniDrawDoc* pDoc = GetDocument();
		pDoc->AddLine(m_PointOrigin.x, m_PointOrigin.y, point.x, point.y, m_color, figureType);
	}
	CView::OnLButtonUp(nFlags, point);
}


BOOL CMiniDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_ClassName = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW, // стили окна
		0,					  // без указателя;
		(HBRUSH)::GetStockObject(WHITE_BRUSH), // задать чисто белый фон;
		0);					  // без значка
	cs.lpszClass = m_ClassName;
	return CView::PreCreateWindow(cs);
}


void CMiniDrawView::OnOptionsColor()
{
	CColorDialog dlg;
	dlg.m_cc.rgbResult = m_color;
	dlg.DoModal();
	m_color = dlg.m_cc.rgbResult;
	Invalidate();
}

void CMiniDrawView::OnDrawRectangle()
{
	figureType = true;
}





void CMiniDrawView::OnDrawLine()
{
	figureType = false;
}


void CMiniDrawView::OnColor()
{
	CColorDialog cc;
	if (cc.DoModal() == IDOK) 
		m_color = cc.GetColor();
}


