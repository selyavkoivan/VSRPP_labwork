#pragma once

#include <comdef.h>
#import "C:\Users\User\source\repos\msado15.dll"  rename("EOF", "ADOEOF")
#include <vector>

// Диалоговое окно UserControllDLG


#include <icrsint.h>
_COM_SMARTPTR_TYPEDEF(IADORecordBinding, __uuidof(IADORecordBinding));

using namespace ADODB;

class CCustomRs : public CADORecordBinding
{
	BEGIN_ADO_BINDING(CCustomRs)
		ADO_VARIABLE_LENGTH_ENTRY2(1, ADODB::adVarChar, _username, sizeof(_username), _username_status, false)
		ADO_VARIABLE_LENGTH_ENTRY2(2, ADODB::adVarChar, placeOfArrival, sizeof(placeOfArrival), placeOfArrival_status, false)
	END_ADO_BINDING()

public:
	CHAR _username[50];
	CHAR placeOfArrival[100];
	ULONG _username_status;
	ULONG placeOfArrival_status;
};

struct Student
{
	CString name;
	CString placeOfArrival;
};

class UserControllDLG : public CDialogEx
{
	DECLARE_DYNAMIC(UserControllDLG)

public:
	UserControllDLG(ADODB::_CommandPtr cmd, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~UserControllDLG();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CListBox _list;
	ADODB::_CommandPtr _cmd;

private:
	std::vector<Student> _users;

	void _update_users(int);
	void _update_screenlist();
	void _filter();

	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CString _choice;
	CString filter;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton3();

	afx_msg void OnBnClickedButton4();

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	
	afx_msg void OnEnChangeEdit1();
	CEdit filterEDIT;
	CButton radio1;
	CButton radio2;
};
