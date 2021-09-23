#pragma once

#include <comdef.h>
#import "C:\Program files\Common Files\System\ado\msado15.dll" rename("EOF", "ADOEOF")
#include "lab4Doc.h"

// Диалоговое окно MainDlg

class AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddDlg)

public:
	AddDlg(ADODB::_CommandPtr _cmd, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString _new_name;
private:
	CString visits_new;
	CButton _add_button;
	ADODB::_CommandPtr _cmd;
public:
	afx_msg void OnBnClickedOk();
};
