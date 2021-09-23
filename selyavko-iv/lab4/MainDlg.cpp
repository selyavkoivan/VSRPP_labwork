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
	, placeOfArrival_new(_T(""))
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
	DDV_MaxChars(pDX, _new_name, 50);
	DDX_Text(pDX, IDC_EDIT2, placeOfArrival_new);
	DDV_MaxChars(pDX, placeOfArrival_new, 100);
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
	
	_bstr_t insert_stmt("INSERT INTO LABA4(name, placeOfArrival) VALUES (");
	insert_stmt += "'";
	insert_stmt += _new_name.GetBuffer();
	insert_stmt += "' , '";
	insert_stmt += placeOfArrival_new.GetBuffer();
	insert_stmt += "');";

	_cmd->CommandText = insert_stmt;
	_cmd->CommandType = ADODB::adCmdText;

	if(_new_name == "") MessageBox(CString("Пожалуйста, введите имя"));
	else if (placeOfArrival_new == "") MessageBox(CString("Пожалуйста, введите информацию о путевке"));
	else
	{
		try
		{
			_cmd->Execute(nullptr, nullptr, ADODB::adCmdText);
		}
		catch (_com_error& ue)
		{
			MessageBox(CString("Имя не уникально"));
		}
	}
	_new_name = "";
	placeOfArrival_new = "";

	UpdateData(TRUE);
	
}


void AddDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}
