
// selyavko-viiView.cpp : implementation of the CselyavkoviiView class
//
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "selyavko-vii.h"
#endif
#include "AboutDLG.h"
#include "selyavko-viiDoc.h"
#include "selyavko-viiView.h"
#include "SomeResource.h"
#include "afxmt.h"
#include "CountArray.h"
#include "selyavko-vii.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996)

CSomeResource someResource;
volatile bool keeprunning;
CCountArray сountArray;
CEvent threadStart;
CEvent threadEnd;

// CselyavkoviiView

IMPLEMENT_DYNCREATE(CselyavkoviiView, CView)

BEGIN_MESSAGE_MAP(CselyavkoviiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CselyavkoviiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_STARTTHREAD, &CselyavkoviiView::OnStartthread)
	ON_COMMAND(ID_THREAD_STARTTHREAD1, &CselyavkoviiView::OnThreadStartthread1)
	ON_COMMAND(ID_THREAD_SEMAPHORE, &CselyavkoviiView::OnThreadSemaphore)
	ON_COMMAND(ID_THREAD_STARTTHREAD2, &CselyavkoviiView::OnThreadStartthread2)
	ON_COMMAND(ID_THREAD_STOPTHREAD2, &CselyavkoviiView::OnThreadStopthread2)
	ON_COMMAND(ID_CRITICALSECTION, &CselyavkoviiView::OnCriticalsection)
	ON_COMMAND(ID_LABWORK_START, &CselyavkoviiView::OnLabworkStart)
END_MESSAGE_MAP()

// CselyavkoviiView construction/destruction

CselyavkoviiView::CselyavkoviiView()
{
	// TODO: add construction code here

}

CselyavkoviiView::~CselyavkoviiView()
{
}

BOOL CselyavkoviiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CselyavkoviiView drawing

void CselyavkoviiView::OnDraw(CDC* /*pDC*/)
{
	CselyavkoviiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CselyavkoviiView printing


void CselyavkoviiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CselyavkoviiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CselyavkoviiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CselyavkoviiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CselyavkoviiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CselyavkoviiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CselyavkoviiView diagnostics

#ifdef _DEBUG
void CselyavkoviiView::AssertValid() const
{
	CView::AssertValid();
}

void CselyavkoviiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CselyavkoviiDoc* CselyavkoviiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CselyavkoviiDoc)));
	return (CselyavkoviiDoc*)m_pDocument;
}
#endif //_DEBUG


// CselyavkoviiView message handlers


UINT MyThread1(LPVOID pParam);
UINT MyThread2(LPVOID pParam);
UINT MyThread3(LPVOID pParam);

void CselyavkoviiView::OnStartthread()
{
	
	// Создать два новых потока. Функция потока 1 имеет имя 
	// MyThread1, Функция потока 2 имеет имя MyThread2.
	// в качестве параметра функциям потоков передается указатель
	// на текущее окно просмотра для вывода в него изображения
	AfxBeginThread(MyThread1, this);
	AfxBeginThread(MyThread2, this);

}

void CselyavkoviiView::OnThreadStartthread1()
{
	AfxBeginThread(MyThread3, this);
}

UINT MyThread1(LPVOID pParam)
{
	// через параметр передается указатель на окно просмотра
	CselyavkoviiView *ptrView = (CselyavkoviiView *)pParam;
	for (int i = 0; i<100; i++)
	{
		CDC *dc = ptrView->GetDC(); // получить контекст отображения
		Sleep(650); // Задержка на 650 мс
		CRect r;
		ptrView->GetClientRect(&r); // получить клиентскую область
		dc->SetTextColor(RGB(255, 0, 0)); // задание цвета окна
		dc->TextOut(rand() % r.Width() + rand() % 100, rand() % r.Height(),
			CString("R"), 1);
	}
	return 0;
}
// определение функции потока 2
UINT MyThread2(LPVOID pParam)
{
	CSingleLock syncObjStart(&threadStart);
	syncObjStart.Lock();

	for (int i = 0; i<50; i++)
	{
		Sleep(2000); // Задержка на 2000 мс
		//AfxMessageBox(CString("MyThread")); // Вывод сообщения
		//MessageBeep(0); // Подача звукового сигнала
		if (keeprunning == FALSE)
		{
			AfxMessageBox(CString("MyThread2 ended"));
			break;
		}

	}
	return 0;
}
UINT MyThread3(LPVOID pParam)
{
	// через параметр передается указатель на окно просмотра
	CselyavkoviiView *ptrView = (CselyavkoviiView *)pParam;
	for (int i = 0; i<100; i++)
	{
		CDC *dc = ptrView->GetDC(); // получить контекст отображения
		Sleep(650); // Задержка на 650 мс
		CRect r;
		ptrView->GetClientRect(&r); // получить клиентскую область окна
		dc->SetTextColor(RGB(0, 255, 0));
		dc->TextOut(rand() % r.Width() + rand() % 100, rand() % r.Height(), CString("G"), 1); // вывод текста
	}
	return 0;
}




UINT ThreadProc1(LPVOID pParam)
{
	someResource.UseResource();
	AfxMessageBox(CString("Thread1 had access."));
	return 0;
}
UINT ThreadProc2(LPVOID pParam)
{
	someResource.UseResource();
	AfxMessageBox(CString("Thread2 had access."));
	return 0;
}
UINT ThreadProc3(LPVOID pParam)
{
	someResource.UseResource();
	AfxMessageBox(CString("Thread3 had access."));
	return 0;
}

void CselyavkoviiView::OnThreadSemaphore()
{
	AfxBeginThread(ThreadProc1, this);
	AfxBeginThread(ThreadProc2, this);
	AfxBeginThread(ThreadProc3, this);

}


void CselyavkoviiView::OnThreadStartthread2()
{
	keeprunning = TRUE;
	threadStart.SetEvent();

}


void CselyavkoviiView::OnThreadStopthread2()
{
	keeprunning = FALSE;
}

UINT WriteThreadProc(LPVOID param)
{
	for (int x = 0; x<10; ++x)
	{
		сountArray.SetArray(x);
		Sleep(1000);
	}
	return 0;
}
UINT ReadThreadProc(LPVOID param)
{
	int array[10];
	for (int x = 0; x<20; ++x)
	{
		сountArray.GetArray(array);
		char str[50];
		str[0] = 0;
		for (int i = 0; i<10; ++i)
		{
			int len = strlen(str);
			sprintf(&str[len], "%d ", array[i]);
		}
		AfxMessageBox(CString(str));
	}
	return 0;
}

void CselyavkoviiView::OnCriticalsection()
{
	AfxBeginThread(WriteThreadProc, this);
	AfxBeginThread(ReadThreadProc, this);

}


void CselyavkoviiView::OnLabworkStart()
{
	CAboutDlg* dlg = new CAboutDlg();
	dlg->DoModal();

}
