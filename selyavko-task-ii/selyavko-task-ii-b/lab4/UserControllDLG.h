#pragma once

#include <comdef.h>
#import "C:\Program files\Common Files\System\ado\msado15.dll"  rename("EOF", "ADOEOF")
#include <vector>

// Диалоговое окно UserControllDLG


#include <icrsint.h>
_COM_SMARTPTR_TYPEDEF(IADORecordBinding, __uuidof(IADORecordBinding));

using namespace ADODB;

class CCustomRs : public CADORecordBinding
{
	BEGIN_ADO_BINDING(CCustomRs)
		ADO_VARIABLE_LENGTH_ENTRY2(1, ADODB::adInteger, ID, sizeof(ID), ID_status, false)
		ADO_VARIABLE_LENGTH_ENTRY2(2, ADODB::adVarChar, _username, sizeof(_username), _username_status, false)
		ADO_VARIABLE_LENGTH_ENTRY2(3, ADODB::adInteger, countOfMissedHours, sizeof(countOfMissedHours), countOfMissedHours_status, false)
		ADO_VARIABLE_LENGTH_ENTRY2(4, ADODB::adBoolean, reasonIsSerious, sizeof(reasonIsSerious), reasonIsSerious_status, false)
	END_ADO_BINDING()

public:
	int ID;
	CHAR _username[100];
	int countOfMissedHours;
	bool reasonIsSerious;


	ULONG ID_status;
	ULONG _username_status;
	ULONG countOfMissedHours_status;
	ULONG reasonIsSerious_status;
};

struct Student
{
	int ID;
	CString username;
	int countOfMissedHours;
	bool reasonIsSerious;
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

	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CString _choice;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList2();
	BOOL Name;
	BOOL Count;
	BOOL Reason;
	
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	CEdit Edit;
	afx_msg void OnBnClickedButton5();
};
