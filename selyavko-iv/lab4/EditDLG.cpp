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
{

}

EditDLG::~EditDLG()
{
}

void EditDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _nname);
	DDV_MaxChars(pDX, _nname, 50);
	DDX_Text(pDX, IDC_EDIT2, _ntm);
	DDV_MaxChars(pDX, _ntm, 100);
}


BEGIN_MESSAGE_MAP(EditDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditDLG::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &EditDLG::OnEnChangeEdit2)
END_MESSAGE_MAP()


// Обработчики сообщений EditDLG




void EditDLG::OnBnClickedOk()
{
	UpdateData(TRUE);
	_bstr_t update_stmt = "UPDATE LABA4 SET name = '";
	update_stmt += _nname.GetBuffer();
	update_stmt += "', placeOfArrival = '";
	update_stmt += _ntm.GetBuffer();
	update_stmt += "' WHERE name = '";
	update_stmt += _user->name.GetBuffer();
	update_stmt += "';";

	_cmd->CommandText = update_stmt;
	_cmd->CommandType = ADODB::adCmdText;
	if (_nname == "") MessageBox(CString("Пожалуйста, введите имя"));
	else if (_ntm == "") MessageBox(CString("Пожалуйста, введите информацию о путевке"));
	else
	{
		try
		{
			_cmd->Execute(nullptr, nullptr, ADODB::adCmdText);
		}
		catch (_com_error& ue)
		{
			MessageBox(CString("Имя должно быть уникально"));
		}
	}

	CDialogEx::OnOK();
}


void EditDLG::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
