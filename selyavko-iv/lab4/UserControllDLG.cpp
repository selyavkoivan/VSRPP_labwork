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
	, filter(_T(""))
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
	DDX_Text(pDX, IDC_EDIT1, filter);
	DDV_MaxChars(pDX, filter, 50);
	DDX_Control(pDX, IDC_EDIT1, filterEDIT);
	DDX_Control(pDX, IDC_RADIO1, radio1);
	DDX_Control(pDX, IDC_RADIO2, radio2);
}


BEGIN_MESSAGE_MAP(UserControllDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UserControllDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserControllDLG::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &UserControllDLG::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST2, &UserControllDLG::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON3, &UserControllDLG::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &UserControllDLG::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &UserControllDLG::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &UserControllDLG::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &UserControllDLG::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Обработчики сообщений UserControllDLG


void UserControllDLG::_update_users(int order)
{
	ADODB::_RecordsetPtr _pRs("ADODB.Recordset");
	CCustomRs _rs;
	IADORecordBindingPtr _picRs(_pRs);

	try
	{
		std::string command = "SELECT * FROM LABA4";
		if (order) command += " order by placeOfArrival";
		auto hr = _pRs->Open(new _variant_t(command.c_str()), _cmd->ActiveConnection->ConnectionString, ADODB::adOpenStatic, ADODB::adLockOptimistic, ADODB::adCmdText);
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
			user.placeOfArrival = CString((_rs.placeOfArrival_status == ADODB::adFieldOK ? _rs.placeOfArrival: "<ERROR PLACE>"));

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
		out.AppendFormat(_T("%s получил путевку %s"), user_i.name, user_i.placeOfArrival);

		
		_list.InsertString(_list.GetCount(), out);
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

void UserControllDLG::_filter()
{
	ADODB::_RecordsetPtr _pRs("ADODB.Recordset");
	CCustomRs _rs;
	IADORecordBindingPtr _picRs(_pRs);

	try
	{
		if (IsDlgButtonChecked(IDC_RADIO1) || IsDlgButtonChecked(IDC_RADIO2))
		{
			CString filterBUFFER;
			filterEDIT.GetWindowTextW(filterBUFFER);
			_bstr_t command = "SELECT * FROM LABA4 WHERE ";
			command += IsDlgButtonChecked(IDC_RADIO1) ? "name " : "placeOfArrival ";
			command += "LIKE '%";
			command += filterBUFFER.GetBuffer();
			command += "%'";
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
				user.name = CString((_rs._username_status == ADODB::adFieldOK ? _rs._username : "<ERROR USERNAME>"));
				user.placeOfArrival = CString((_rs.placeOfArrival_status == ADODB::adFieldOK ? _rs.placeOfArrival : "<ERROR PLACE>"));

				_users.push_back(user);

				_pRs->MoveNext();
			}
		}
		else MessageBox(CString("Выберите поле для фильтрации"));

		

	}
	catch (_com_error& e)
	{
		exit(-2);
	}

	_update_screenlist();
}

void UserControllDLG::OnLbnSelchangeList2()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void UserControllDLG::OnBnClickedButton3()
{
	_filter();
}
void UserControllDLG::OnBnClickedButton5()
{
	_update_users(0);
}

void UserControllDLG::OnBnClickedButton4()
{
	_update_users(0);
}


void UserControllDLG::OnBnClickedButton6()
{
	_update_users(1);
}





void UserControllDLG::OnEnChangeEdit1()
{

	
}
