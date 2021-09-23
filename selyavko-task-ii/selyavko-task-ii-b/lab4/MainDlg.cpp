// MainDlg.cpp: файл реализации
//

#include "pch.h"
#include "lab4.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// Диалоговое окно MainDlg

IMPLEMENT_DYNAMIC(AddDlg, CDialogEx)

AddDlg::AddDlg(ADODB::_CommandPtr cmd, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, _new_name(_T(""))
	, visits_new(_T(""))
	, _cmd(cmd)
{

}

AddDlg::~AddDlg()
{
}

void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _new_name);
	DDV_MaxChars(pDX, _new_name, 30);
	DDX_Text(pDX, IDC_EDIT2, visits_new);
	DDV_MaxChars(pDX, visits_new, 10);
	DDX_Control(pDX, IDC_BUTTON1, _add_button);
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &AddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений MainDlg

void AddDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	
	_bstr_t insert_stmt("INSERT INTO LABA4(name, visits) VALUES (");
	insert_stmt += "'";
	insert_stmt += _new_name.GetBuffer();
	insert_stmt += "' , ";
	insert_stmt += visits_new.GetBuffer();
	insert_stmt += ");";

	_cmd->CommandText = insert_stmt;
	_cmd->CommandType = ADODB::adCmdText;

	try
	{
		_cmd->Execute(nullptr, nullptr, ADODB::adCmdText);
	}
	catch (_com_error& ue)
	{
		MessageBox(CString("Name isn't unique!"));
	}
	_new_name = "";
	visits_new = "";

	UpdateData(TRUE);
	
}


void AddDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}
