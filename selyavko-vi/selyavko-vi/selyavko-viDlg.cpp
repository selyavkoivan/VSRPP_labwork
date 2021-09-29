
// selyavko-viDlg.cpp : implementation file
//

#include "stdafx.h"
#include "selyavko-vi.h"
#include "selyavko-viDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CselyavkoviDlg dialog



CselyavkoviDlg::CselyavkoviDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELYAVKOVI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CselyavkoviDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SORT, m_sort_value);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_filter_spis);
	DDX_Control(pDX, IDC_CHECK_DESC, m_sort_obr);
	DDX_Control(pDX, IDC_BUTTON_FILTER, m_app_filter);
	DDX_Control(pDX, IDC_DATAGRID1, m_grid);
	DDX_Control(pDX, IDC_EDIT_FILTER, m_filter_value);
	DDX_Control(pDX, IDC_ADODC2, m_adodb);
}

BEGIN_MESSAGE_MAP(CselyavkoviDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_SORT, &CselyavkoviDlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_FILTER, &CselyavkoviDlg::OnBnClickedButtonFilter)
END_MESSAGE_MAP()


// CselyavkoviDlg message handlers

BOOL CselyavkoviDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	m_sort_value.AddString(CString("unsort"));
	m_sort_value.AddString(CString("ID"));
	m_sort_value.AddString(CString("name"));
	m_sort_value.AddString(CString("place"));
	m_sort_value.AddString(CString("date"));
	


	m_filter_spis.AddString(CString("unfilter"));
	m_filter_spis.AddString(CString("ID"));
	m_filter_spis.AddString(CString("name"));
	m_filter_spis.AddString(CString("place"));
	m_filter_spis.AddString(CString("date"));


	return TRUE;
}

void CselyavkoviDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CselyavkoviDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CselyavkoviDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CselyavkoviDlg::OnSelchangeCombo1()
{
	CString str1, str2;
	str1 = "SELECT * FROM vouchers";
	if (m_sort_value.GetCurSel() == 0)
		str2 = "";
	else
	{
		m_sort_value.GetLBText(m_sort_value.GetCurSel(), str2);
		str2 = (CString)" ORDER BY " + str2;
		if (m_sort_obr.GetCheck())
			str2 += " DESC";
	}
	str1 += str2;
	
	m_adodb.put_RecordSource(str1);
	m_adodb.Refresh();

}


void CselyavkoviDlg::OnBnClickedButtonFilter()
{

	CString str1, str2, str3;
	str1 = "SELECT * FROM vouchers ";
	m_filter_spis.GetLBText(m_filter_spis.GetCurSel(), str2);
	if (str2 == "unfilter")
	{
		str2 = "";
		str3 = "";
	}
	else
		if (str2 != "")
		{
			m_filter_value.GetWindowText(str3);

			str1 += "WHERE ";
			str1 += str2;
			str1 += " LIKE ";
			str1 += "'%";
			str1 += str3;
			str1 += "%'";
		}
	m_adodb.put_RecordSource(str1);
	m_adodb.Refresh();

}
