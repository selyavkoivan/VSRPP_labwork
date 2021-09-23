#pragma once


// Диалоговое окно Dialog

class Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog)
	

public:
	Dialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Dialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CListBox listSurname;
	CListBox listName;
	CString editName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit edit;
	afx_msg void OnBnClickedButton3();
	CEdit find;
};
