#pragma once


// Диалоговое окно EditDLG

#include <comdef.h>
#import "C:\Program files\Common Files\System\ado\msado15.dll"  rename("EOF", "ADOEOF")
#include "UserControllDLG.h"

class EditDLG : public CDialogEx
{
	DECLARE_DYNAMIC(EditDLG)

public:
	EditDLG(_CommandPtr _cmd, Student *user, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~EditDLG();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
private:
	CString _nname;
	CString _ntm;
	Student *_user;
	_CommandPtr _cmd;
public:
	afx_msg void OnBnClickedOk();
	BOOL isSerious;
};
