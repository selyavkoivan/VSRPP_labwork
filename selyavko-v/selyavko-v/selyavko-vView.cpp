
// selyavko-vView.cpp : implementation of the CselyavkovView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "selyavko-v.h"
#endif

#include "selyavko-vSet.h"
#include "selyavko-vDoc.h"
#include "selyavko-vView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CselyavkovView

IMPLEMENT_DYNCREATE(CselyavkovView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CselyavkovView, COleDBRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CselyavkovView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RECORD_FIRST, &CselyavkovView::OnRecordFirst)
	ON_COMMAND(ID_RECORD_LAST, &CselyavkovView::OnRecordLast)
	ON_COMMAND(ID_RECORD_NEXT, &CselyavkovView::OnRecordNext)
	ON_COMMAND(ID_RECORD_PREV, &CselyavkovView::OnRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, &CselyavkovView::OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, &CselyavkovView::OnUpdateRecordPrev)
	ON_BN_CLICKED(IDC_INSERT, &CselyavkovView::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_EDIT, &CselyavkovView::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_DELETE, &CselyavkovView::OnBnClickedDelete)
	ON_COMMAND(ID_SORT_ID, &CselyavkovView::OnSortId)
	ON_COMMAND(ID_SORT_NAME, &CselyavkovView::OnSortName)
	ON_COMMAND(ID_SORT_DATE, &CselyavkovView::OnSortDate)
	ON_COMMAND(ID_SORT_PLACE, &CselyavkovView::OnSortPlace)
	ON_COMMAND(ID_FILTER_ID, &CselyavkovView::OnFilterId)
	ON_COMMAND(ID_FILTER_DATE, &CselyavkovView::OnFilterDate)
	ON_COMMAND(ID_FILTER_NAME, &CselyavkovView::OnFilterName)
	ON_COMMAND(ID_FILTER_PLACE, &CselyavkovView::OnFilterPlace)
	ON_EN_CHANGE(IDC_EDIT_ID, &CselyavkovView::OnEnChangeEditId)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CselyavkovView::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()

// CselyavkovView construction/destruction

CselyavkovView::CselyavkovView()
	: COleDBRecordView(IDD_SELYAVKOV_FORM)
	, m_bAdding(false)
	, m_order_str(_T("ID"))
	, m_where_str(_T(""))
	, m_date(COleDateTime::GetCurrentTime())
{}


CselyavkovView::~CselyavkovView()
{
}

void CselyavkovView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	// you can insert DDX_* functions, as well as SetDlgItem*/GetDlgItem* API calls to link your database to the view
	// ex. ::SetDlgItemText(m_hWnd, IDC_MYCONTROL, m_pSet->m_MyColumn);
	// See MSDN and OLEDB samples for more information
	DDX_Control(pDX, IDC_EDIT_ID, m_edit_id);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edit_name);
	DDX_Control(pDX, IDC_EDIT_PLACE, m_edit_place);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_control);
}

BOOL CselyavkovView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CselyavkovView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_selyavkovSet;
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->OpenAll();
		if (FAILED(hr))
		{
			// Failed to open recordset.  If the recordset is a 
			// stored procedure, make sure that you have properly
			// initialized any input parameters before calling
			// the OpenAll() method.

			AfxMessageBox(_T("Record set failed to open."), MB_OK);
			// Disable the Next and Previous record commands,
			// since attempting to change the current record without an
			// open RowSet will cause a crash
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
		if( hr == DB_S_ENDOFROWSET )
		{
			// the rowset is empty (does not contain any rows)
			AfxMessageBox(_T("Record set opened but there were no rows to return."), MB_OK);
			// Disable the Next and Previous record commands
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
	}
	COleDBRecordView::OnInitialUpdate();

}


// CselyavkovView printing


void CselyavkovView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CselyavkovView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CselyavkovView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CselyavkovView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CselyavkovView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CselyavkovView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CselyavkovView diagnostics

#ifdef _DEBUG
void CselyavkovView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CselyavkovView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CselyavkovDoc* CselyavkovView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CselyavkovDoc)));
	return (CselyavkovDoc*)m_pDocument;
}
#endif //_DEBUG


// CselyavkovView database support
CRowset<>* CselyavkovView::OnGetRowset()
{
	return m_pSet->GetRowsetBase();
}



// CselyavkovView message handlers


void CselyavkovView::OnRecordFirst()
{
	m_pSet->MoveFirst(); // переход на первую позицию
	displayMembersOfDataSourse();
}


void CselyavkovView::OnRecordLast()
{
	m_pSet->MoveLast();
	displayMembersOfDataSourse();
}


void CselyavkovView::OnRecordNext()
{
	m_pSet->MoveNext();
	displayMembersOfDataSourse();
}


void CselyavkovView::OnRecordPrev()
{
	m_pSet->MovePrev();
	displayMembersOfDataSourse();

}


void CselyavkovView::OnUpdateRecordFirst(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CselyavkovView::OnUpdateRecordPrev(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CselyavkovView::OnBnClickedInsert()
{
	if (!m_bAdding)
	{
		m_bAdding = true;
		SetDlgItemText(IDC_INSERT, _T("SAVE"));
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(SW_SHOW);
		SetDlgItemText(IDC_EDIT_ID, NULL);
		SetDlgItemText(IDC_EDIT_NAME, NULL);
		SetDlgItemText(IDC_EDIT_PLACE, NULL);
		SetDlgItemText(IDC_EDIT_DATE, NULL);
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
	}
	else
	{
		m_pSet->MoveLast();
		FillOleDBParameters();
		m_pSet->Insert();
		m_pSet->MoveLast();
		SetDlgItemText(IDC_INSERT, _T("INSERT"));
		m_bAdding = false;
	}

}


void CselyavkovView::OnBnClickedEdit()
{
	FillOleDBParameters();
	m_pSet->SetData(); // изменение значений полей источника данных
					   // передача источнику данных информации об изменениях, 
					   // выполненных над строкой.
	m_pSet->Update();

}


void CselyavkovView::OnBnClickedDelete()
{
	m_pSet->Delete();
}


void CselyavkovView::OnSortId()
{
	m_order_str = L"ID";
	ReQuery();

}


void CselyavkovView::OnSortName()
{
	m_order_str = L"name";
	ReQuery();
}


void CselyavkovView::OnSortDate()
{
	m_order_str = L"date";
	ReQuery();
}


void CselyavkovView::OnSortPlace()
{
	m_order_str = L"place";
	ReQuery();
}


void CselyavkovView::OnFilterId()
{
	DoFilter(L"ID");
}


void CselyavkovView::OnFilterDate()
{
	DoFilter(L"date");
}


void CselyavkovView::OnFilterName()
{
	DoFilter(L"name");
}


void CselyavkovView::OnFilterPlace()
{
	DoFilter(L"place");
}


void CselyavkovView::OnEnChangeEditId()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the COleDBRecordView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CselyavkovView::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
