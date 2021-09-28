
// selyavko-vView.h : interface of the CselyavkovView class
//
#pragma warning(disable: 4996)
#pragma once
#include "afxwin.h"
#include "FilterDlg.h"
#include "afxdtctl.h"
#include "ATLComTime.h"
class CselyavkovSet;

class CselyavkovView : public COleDBRecordView
{
protected: // create from serialization only
	CselyavkovView();
	DECLARE_DYNCREATE(CselyavkovView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_SELYAVKOV_FORM };
#endif
	CselyavkovSet* m_pSet;

// Attributes
public:
	CselyavkovDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRowset<>* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CselyavkovView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CselyavkovView::displayMembersOfDataSourse()
	{
		CString str;
		str.Format(_T("%d"), m_pSet->m_ID); //форматирование 
		m_edit_id.SetWindowText(str); // визуальное отображение данных
		str = m_pSet->m_name;
		m_edit_name.SetWindowText(str);
		str = m_pSet->m_place;
		m_edit_place.SetWindowText(str);
		str = m_pSet->m_date;

		CString field;

		CArray<CString, CString> v;

		int index = 0;
		// last argument is the delimitter
		while (AfxExtractSubString(field, str, index, _T('-')))
		{
			v.Add(field);
			++index;
		}
		m_date_control.SetTime(COleDateTime(_ttoi(v[0]), _ttoi(v[1]), _ttoi(v[2]), 0, 0, 0));
	
	}
	void FillOleDBParameters()
	{
		int i;	
		CString str;
		m_pSet->m_dwnameLength = 51;
		m_pSet->m_dwplaceLength = 51;
		m_pSet->m_dwdateLength = 51;
		char chars[51]; 
		m_edit_id.GetWindowTextW(str);
		
		m_pSet->m_ID = _ttoi(str);
		m_edit_name.GetWindowTextW(str);
		
		memset(chars, 0, 51);
		for (i = 0; i < str.GetLength(); i++)
			
			chars[i] = (unsigned char)str[i];
		
		strcpy(m_pSet->m_name, chars);
		
		memcpy(m_pSet->m_name, &chars[0], 51);
		m_edit_place.GetWindowTextW(str);
		memset(chars, 0, 51);
		for (i = 0; i < str.GetLength(); i++)
			chars[i] = (unsigned char)str[i];
		strcpy(m_pSet->m_place, chars);
		memcpy(m_pSet->m_place, &chars[0], 51);
		m_date_control.GetWindowTextW(str);
		memset(chars, 0, 51);
		for (i = 0; i < str.GetLength(); i++)
			chars[i] = (unsigned char)str[i];
		strcpy(m_pSet->m_date, chars);
		memcpy(m_pSet->m_date, &chars[0], 51);
		

	}

	CString m_where_str;
	CString	m_order_str;
	
	void ReQuery()
	{
		m_pSet->ReOpen(m_where_str, m_order_str);
		OnMove(ID_RECORD_FIRST);
	}

	
	void DoFilter(CString column)
	{
		CFilterDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			dlg.m_filter_Value.Replace(L"'", L"''"); // Замена на "''"
			dlg.m_filter_Value.Replace(L"--", L"");
			m_where_str.Format(L"%s = '%s'", column, dlg.m_filter_Value);
			ReQuery();
		}
	}



	bool m_bAdding;
	

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_id;
	CEdit m_edit_name;
	CEdit m_edit_place;
	
	
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordLast();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordFirst(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnSortId();
	afx_msg void OnSortName();
	afx_msg void OnSortDate();
	afx_msg void OnSortPlace();
	afx_msg void OnFilterId();
	afx_msg void OnFilterDate();
	afx_msg void OnFilterName();
	afx_msg void OnFilterPlace();
	afx_msg void OnEnChangeEditId();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	COleDateTime m_date;
	CDateTimeCtrl m_date_control;
};

#ifndef _DEBUG  // debug version in selyavko-vView.cpp
inline CselyavkovDoc* CselyavkovView::GetDocument() const
   { return reinterpret_cast<CselyavkovDoc*>(m_pDocument); }
#endif

