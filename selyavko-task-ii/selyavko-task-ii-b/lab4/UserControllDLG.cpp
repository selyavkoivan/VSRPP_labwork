// UserControllDLG.cpp: файл реализации
//

#include "pch.h"
#include "lab4.h"
#include "UserControllDLG.h"
#include "afxdialogex.h"
#include <string>
#include "EditDLG.h"

// Диалоговое окно UserControllDLG

IMPLEMENT_DYNAMIC(UserControllDLG, CDialogEx)

UserControllDLG::UserControllDLG(ADODB::_CommandPtr cmd, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, _list()
	, _cmd(cmd)
	, _choice(_T(""))
{

}

UserControllDLG::~UserControllDLG()
{
}

void UserControllDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, _list);
	_update_users();
	DDX_LBString(pDX, IDC_LIST2, _choice);
}


BEGIN_MESSAGE_MAP(UserControllDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UserControllDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserControllDLG::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &UserControllDLG::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST2, &UserControllDLG::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// Обработчики сообщений UserControllDLG


void UserControllDLG::_update_users()
{
	ADODB::_RecordsetPtr _pRs("ADODB.Recordset");
	CCustomRs _rs;
	IADORecordBindingPtr _picRs(_pRs);

	try
	{
		auto hr = _pRs->Open(L"SELECT name, visits FROM LABA4 ORDER BY name", _cmd->ActiveConnection->ConnectionString, ADODB::adOpenStatic, ADODB::adLockOptimistic, ADODB::adCmdText);
		if (FAILED(hr))
		{
			_com_issue_error(hr);
		}
		
		hr = _picRs->BindToRecordset(&_rs);
		if (FAILED(hr))
		{
			_com_issue_error(hr);
		}


		_users.clear();
		while (!_pRs->ADOEOF)
		{
			Student user;
			user.name = CString((_rs._username_status == ADODB::adFieldOK ? _rs._username : "<ERROR USERNAME>"));
			user.visits = (_rs.visits_status == ADODB::adFieldOK ? _rs.visits : -1);

			_users.push_back(user);

			_pRs->MoveNext();
		}

	}
	catch (_com_error& e)
	{
		exit(-2);
	}

	_update_screenlist();
}

void UserControllDLG::_update_screenlist()
{
	_list.ResetContent();

	for (auto user_i : _users)
	{
		CString out;
		out.AppendFormat(_T("%s посетил %d занятий в этом семестре"), user_i.name, user_i.visits);

		_list.AddString(out);
	}
}



void UserControllDLG::OnBnClickedButton1()
{
	int choice_i = _list.GetCurSel();

	if (choice_i != LB_ERR)
	{
		_bstr_t insert_stmt("DELETE FROM LABA4 WHERE name = ");
		insert_stmt += "'";
		insert_stmt += _users[choice_i].name.GetBuffer();
		insert_stmt += "';";

		_cmd->CommandText = insert_stmt;
		_cmd->CommandType = ADODB::adCmdText;

		try
		{
			_cmd->Execute(nullptr, nullptr, ADODB::adCmdText);
		}
		catch (_com_error& ue)
		{
			exit(-1);
		}

		_update_users();
	}
}


void UserControllDLG::OnBnClickedButton2()
{
	int choice_i = _list.GetCurSel();
	if (choice_i != LB_ERR)
	{
		EditDLG edit(_cmd, &_users[choice_i]);
		edit.DoModal();
		_update_users();
	}
}


void UserControllDLG::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void UserControllDLG::OnLbnSelchangeList2()
{
	// TODO: добавьте свой код обработчика уведомлений
}
