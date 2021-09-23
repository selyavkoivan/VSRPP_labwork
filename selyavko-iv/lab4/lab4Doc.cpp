
// lab4Doc.cpp: реализация класса Clab4Doc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "lab4.h"
#endif

#include "lab4Doc.h"
#include "MainDlg.h"
#include "pch.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Clab4Doc

IMPLEMENT_DYNCREATE(Clab4Doc, CDocument)

BEGIN_MESSAGE_MAP(Clab4Doc, CDocument)
END_MESSAGE_MAP()



// Создание или уничтожение Clab4Doc

Clab4Doc::Clab4Doc() noexcept
{
	CoInitialize(nullptr);
	_bstr_t strCon("lab4");
	try
	{
		auto hr = _db.CreateInstance((__uuidof(ADODB::Connection)));
		if (FAILED(hr))
		{
			exit(-1);
		}

		hr = _db->Open(strCon, "", "", 0);
		if (FAILED(hr))
		{
			exit(-1);
		}

	}
	catch (_com_error& ce)
	{
		exit(-1);
	}
}

Clab4Doc::~Clab4Doc()
{
	_db->Close();
	CoUninitialize();
}

ADODB::_CommandPtr Clab4Doc::GetCommand()
{
	ADODB::_CommandPtr cmd = NULL;

	try
	{
		auto hr = cmd.CreateInstance(__uuidof(ADODB::Command));
		if (FAILED(hr))
		{
			exit(-1);
		}

		cmd->ActiveConnection = _db;
	}
	catch (_com_error& ce)
	{
		exit(-2);
	}

	return cmd;
}

BOOL Clab4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация Clab4Doc

void Clab4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void Clab4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void Clab4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void Clab4Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика Clab4Doc

#ifdef _DEBUG
void Clab4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Clab4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды Clab4Doc
