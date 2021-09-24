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
	_update_users(0);
	DDX_LBString(pDX, IDC_LIST2, _choice);
	DDX_Control(pDX, IDC_EDIT1, Edit);
}


BEGIN_MESSAGE_MAP(UserControllDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UserControllDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserControllDLG::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &UserControllDLG::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST2, &UserControllDLG::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON4, &UserControllDLG::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &UserControllDLG::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &UserControllDLG::OnBnClickedButton5)
END_MESSAGE_MAP()


// Обработчики сообщений UserControllDLG


void UserControllDLG::_update_users(int field)
{
	ADODB::_RecordsetPtr _pRs("ADODB.Recordset");
	CCustomRs _rs;
	IADORecordBindingPtr _picRs(_pRs);
	
	try
	{
	
		_bstr_t command = "SELECT * FROM lossTime";
		switch (field)
		{
		case 1: command += " ORDER BY name"; break;
		case 2: command += " ORDER BY reasonIsSerious"; break;
		case 3: command += " ORDER BY countOfMissedHours"; break;
		case 4:
		{
			CString Value;
			Edit.GetWindowTextW(Value); 
			command += " WHERE name LIKE '%" + _bstr_t(Value) + "%'";
			break;
		}
		case 5:
		{
			CString Value;
			Edit.GetWindowTextW(Value); 
			command += " WHERE reasonIsSerious = " + _bstr_t(Value);
			break;
		}
		case 6:
		{
			CString Value;
			Edit.GetWindowTextW(Value); 
			command += " WHERE countOfMissedHours = " + _bstr_t(Value); 
			break;
		}
		}
		auto hr = _pRs->Open(command, _cmd->ActiveConnection->ConnectionString, ADODB::adOpenStatic, ADODB::adLockOptimistic, ADODB::adCmdText);
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
			user.ID = (_rs.ID);
			user.username = CString((_rs._username_status == ADODB::adFieldOK ? _rs._username : "<ERROR USERNAME>"));
			user.countOfMissedHours = (_rs.countOfMissedHours_status == ADODB::adFieldOK ? _rs.countOfMissedHours : 1);
			user.reasonIsSerious = (_rs.reasonIsSerious_status == ADODB::adFieldOK ? _rs.reasonIsSerious : -1);
			

			_users.push_back(user);

			_pRs->MoveNext();
		}

	}
	catch (_com_error& e)
	{
		if (field == 0) exit(-2);
		else MessageBox(CString("ОШИБКА! Введите верные данные для фильтрации"));
	}
	_update_screenlist();
	
}

void UserControllDLG::_update_screenlist()
{
	_list.ResetContent();

	for (auto user_i : _users)
	{
		
		CString out;
		out.AppendFormat(_T("%s пропустил %d часов по "), user_i.username, user_i.countOfMissedHours);
		out += user_i.reasonIsSerious ? "уважительной причине" : "неуважительной причине";
	
		_list.AddString(out);
	}
	
}



void UserControllDLG::OnBnClickedButton1()
{
	int choice_i = _list.GetCurSel();

	if (choice_i != LB_ERR)
	{
		_bstr_t insert_stmt("DELETE FROM lossTime WHERE ID = ");
		CString s;
		s.AppendFormat(_T("%d"), _users[choice_i].ID);
		_bstr_t ss(s);
		insert_stmt += ss;
		insert_stmt += ";";

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

		_update_users(0);
	}
}


void UserControllDLG::OnBnClickedButton2()
{
	int choice_i = _list.GetCurSel();
	if (choice_i != LB_ERR)
	{
		EditDLG edit(_cmd, &_users[choice_i]);
		edit.DoModal();
		_update_users(0);
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


void UserControllDLG::OnBnClickedButton4()
{
	if (IsDlgButtonChecked(IDC_RADIO1)) _update_users(1);
	else if (IsDlgButtonChecked(IDC_RADIO2)) _update_users(2);
	else if (IsDlgButtonChecked(IDC_RADIO3)) _update_users(3);
	else MessageBox(CString("Выберите поле для сортировки"));
}


void UserControllDLG::OnBnClickedButton3()
{
	if (IsDlgButtonChecked(IDC_RADIO1)) _update_users(4);
	else if (IsDlgButtonChecked(IDC_RADIO2)) _update_users(5);
	else if (IsDlgButtonChecked(IDC_RADIO3)) _update_users(6);
	else MessageBox(CString("Выберите поле для фильтрации"));
}


void UserControllDLG::OnBnClickedButton5()
{
	_update_users(0);
}
