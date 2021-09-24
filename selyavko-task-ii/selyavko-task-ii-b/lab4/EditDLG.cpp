// EditDLG.cpp: файл реализации
//

#include "pch.h"
#include "lab4.h"
#include "EditDLG.h"
#include "afxdialogex.h"


// Диалоговое окно EditDLG

IMPLEMENT_DYNAMIC(EditDLG, CDialogEx)

EditDLG::EditDLG(_CommandPtr cmd, Student *user, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, _nname(_T(""))
	, _ntm(_T(""))
	, _cmd(cmd)
	, _user(user)
	, isSerious(FALSE)
{

}

EditDLG::~EditDLG()
{
}

void EditDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _nname);
	DDV_MaxChars(pDX, _nname, 30);
	DDX_Text(pDX, IDC_EDIT2, _ntm);
	DDV_MaxChars(pDX, _ntm, 10);
	DDX_Check(pDX, IDC_CHECK1, isSerious);
}


BEGIN_MESSAGE_MAP(EditDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditDLG::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений EditDLG




void EditDLG::OnBnClickedOk()
{
	UpdateData(TRUE);
	_bstr_t update_stmt = "UPDATE lossTime SET name = '";
	update_stmt += _nname.GetBuffer();
	update_stmt += "', countOfMissedHours = ";
	update_stmt += _ntm.GetBuffer();
	update_stmt += ", reasonIsSerious = ";
	update_stmt += isSerious ? "true" : "false";
	update_stmt += " WHERE ID = ";
	CString s;
	s.AppendFormat(_T("%d"), _user->ID);
	_bstr_t ss(s);
	update_stmt += ss;
	update_stmt += ";";

	_cmd->CommandText = update_stmt;
	_cmd->CommandType = ADODB::adCmdText;

	try
	{
		_cmd->Execute(nullptr, nullptr, ADODB::adCmdText);
	}
	catch (_com_error& ue)
	{
		MessageBox(CString("Данные введены неверно"));
	}


	CDialogEx::OnOK();
}
