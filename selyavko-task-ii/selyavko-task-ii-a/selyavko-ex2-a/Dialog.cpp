// Dialog.cpp: файл реализации
//

#include "pch.h"
#include "selyavko-ex2-a.h"
#include "Dialog.h"
#include "afxdialogex.h"


// Диалоговое окно Dialog

IMPLEMENT_DYNAMIC(Dialog, CDialogEx)

Dialog::Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, editName(_T(""))
{

}

Dialog::~Dialog()
{
}

void Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listSurname);
	DDX_Control(pDX, IDC_LIST1, listName);
	DDX_Text(pDX, IDC_EDIT1, editName);
	DDX_Control(pDX, IDC_EDIT1, edit);
	DDX_Control(pDX, IDC_EDIT2, find);
}


BEGIN_MESSAGE_MAP(Dialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Dialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений Dialog


void Dialog::OnBnClickedButton1()
{
	CString value;
	edit.GetWindowTextW(value);
	CString field;
	int index = 0;
	CArray<CString, CString> v;
	// last argument is the delimitter
	while (AfxExtractSubString(field, value, index, _T(' ')))
	{
		v.Add(field);
		++index;
	}

	if (v.GetSize() != 3) MessageBox(CString("Данные введены не верно"));
	else
	{
		listSurname.AddString(v[0]);
		listName.AddString(v[1] + " " + v[2]);
	}
	
}


void Dialog::OnBnClickedButton2()
{
	if (listSurname.GetSelCount() != 0 && listName.GetSelCount() != 0)
	{
		CString surname;
		listSurname.GetText(listSurname.GetCurSel(), surname);
		CString name;
		listName.GetText(listName.GetCurSel(), name);
		edit.SetWindowTextW(surname + " " + name);
	}
}


void Dialog::OnBnClickedButton3()
{
	CString value;
	find.GetWindowTextW(value);
	
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		for (int i = 0; i < listSurname.GetCount(); i++) listSurname.SetSel(i, 0);
		if (listSurname.FindStringExact(0, value) != -1)
		{
			for (int i = 0; i < listSurname.GetCount(); i++)
			{

				int index = listSurname.FindStringExact(i, value);
				listSurname.SetSel(index, 1);

			}
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
		for (int i = 0; i < listName.GetCount(); i++) listName.SetSel(i, 0);
		for (int i = 0; i < listName.GetCount(); i++)
		{
			CString nameValue;
			CString listValue;
			listName.GetText(i, listValue);
			AfxExtractSubString(nameValue, listValue, 0, _T(' '));
			if(nameValue == value) listName.SetSel(i, 1);
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO3))
	{
		for (int i = 0; i < listName.GetCount(); i++) listName.SetSel(i, 0);
		for (int i = 0; i < listName.GetCount(); i++)
		{
			CString nameValue;
			CString listValue;
			listName.GetText(i, listValue);
			AfxExtractSubString(nameValue, listValue, 1, _T(' '));
			if (nameValue == value) listName.SetSel(i, 1);
		}
	}
	else MessageBox(CString("Выберите поле для поиска"));
}
