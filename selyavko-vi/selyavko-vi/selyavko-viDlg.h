
// selyavko-viDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "datagrid1.h"
#include "adodc2.h"


// CselyavkoviDlg dialog
class CselyavkoviDlg : public CDialogEx
{
// Construction
public:
	CselyavkoviDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELYAVKOVI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_sort_value;
	CComboBox m_filter_spis;
	CButton m_sort_obr;
	CButton m_app_filter;
	CDatagrid1 m_grid;
	CEdit m_filter_value;
	CAdodc2 m_adodb;


	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedButtonFilter();
};
