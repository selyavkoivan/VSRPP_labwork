// Dialog.cpp: файл реализации
//

#include "pch.h"
#include "selyavko-iii.h"
#include "Dialog.h"
#include "afxdialogex.h"


// Диалоговое окно Dialog

IMPLEMENT_DYNAMIC(Dialog, CDialogEx)

Dialog::Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Dialog::~Dialog()
{
}

void Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LEFT, left_list);
	DDX_Control(pDX, IDC_LIST_RIGHT, list_right);
}


BEGIN_MESSAGE_MAP(Dialog, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &Dialog::OnBnClickedToRightListButton)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog::OnBnClickedToLeftListButton)
END_MESSAGE_MAP()


// Обработчики сообщений Dialog

BOOL Dialog::OnInitDialog()
{

	CDialog::OnInitDialog();
	left_list.AddString(L"Первая строка");
	left_list.AddString(L"Вторая строка");
	left_list.AddString(L"Третья строка");
	left_list.AddString(L"Четвертая строка");
	left_list.AddString(L"Пятая строка");
	left_list.AddString(L"Шестая строка");
	left_list.AddString(L"Седьмая строка");
	left_list.AddString(L"Восьмая строка");
	left_list.AddString(L"Девятая строка");
	left_list.AddString(L"Десятая строка");
	return TRUE;   
}


void Dialog::OnBnClickedToRightListButton()
{
	int count = left_list.GetSelCount();
	int* IndexBuf = new int[left_list.GetSelCount()];
	left_list.GetSelItems(left_list.GetSelCount(), IndexBuf);  // массив с индексами выделенных элементов
	list_right.SelItemRange(0, 0, list_right.GetCount());
	for (int i = 0; i < count; i++)
	{
		CString ItemSelected;
		left_list.GetText(IndexBuf[i], ItemSelected); // получение текста по индексу
		left_list.SetSel(IndexBuf[i], 0);
		list_right.AddString(ItemSelected);
		list_right.SetSel(list_right.GetCount() - 1, 1);
	}
}

void Dialog::OnBnClickedToLeftListButton()
{
	int count = list_right.GetSelCount();
	int* IndexBuf = new int[list_right.GetSelCount()];
	list_right.GetSelItems(list_right.GetSelCount(), IndexBuf);
	left_list.SelItemRange(0, 0, left_list.GetCount());
	for (int i = 0; i < count; i++)
	{
		CString ItemSelected;
		list_right.GetText(IndexBuf[i], ItemSelected);
		list_right.SetSel(IndexBuf[i], 0);
		left_list.AddString(ItemSelected);
		left_list.SetSel(left_list.GetCount() - 1, 1);
	}
}
