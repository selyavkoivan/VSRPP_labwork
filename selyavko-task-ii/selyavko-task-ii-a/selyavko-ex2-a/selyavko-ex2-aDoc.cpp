
// selyavko-ex2-aDoc.cpp: реализация класса Cselyavkoex2aDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "selyavko-ex2-a.h"
#endif

#include "selyavko-ex2-aDoc.h"

#include <propkey.h>
#include "Dialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cselyavkoex2aDoc

IMPLEMENT_DYNCREATE(Cselyavkoex2aDoc, CDocument)

BEGIN_MESSAGE_MAP(Cselyavkoex2aDoc, CDocument)
	ON_COMMAND(ID_32771, &Cselyavkoex2aDoc::On32771)
END_MESSAGE_MAP()


// Создание или уничтожение Cselyavkoex2aDoc

Cselyavkoex2aDoc::Cselyavkoex2aDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

Cselyavkoex2aDoc::~Cselyavkoex2aDoc()
{
}

BOOL Cselyavkoex2aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация Cselyavkoex2aDoc

void Cselyavkoex2aDoc::Serialize(CArchive& ar)
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
void Cselyavkoex2aDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cselyavkoex2aDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void Cselyavkoex2aDoc::SetSearchContent(const CString& value)
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

// Диагностика Cselyavkoex2aDoc

#ifdef _DEBUG
void Cselyavkoex2aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cselyavkoex2aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды Cselyavkoex2aDoc


void Cselyavkoex2aDoc::On32771()
{
	Dialog dialog;
	dialog.DoModal();
}
