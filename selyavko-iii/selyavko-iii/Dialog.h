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

	virtual BOOL OnInitDialog();
	CListBox left_list;

	afx_msg void OnBnClickedToRightListButton();
	CListBox list_right;
	afx_msg void OnBnClickedToLeftListButton();
};
