
// MiniDrawDoc.cpp: реализация класса CMiniDrawDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MiniDraw.h"
#endif

#include "MiniDrawDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMiniDrawDoc

IMPLEMENT_DYNCREATE(CMiniDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CMiniDrawDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CMiniDrawDoc::OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CMiniDrawDoc::OnUpdateEditClearAll)
	ON_COMMAND(ID_EDIT_UNDO, &CMiniDrawDoc::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMiniDrawDoc::OnUpdateEditUndo)
	

	
	ON_COMMAND(ID_EDIT_REDO, &CMiniDrawDoc::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMiniDrawDoc::OnUpdateEditRedo)
	ON_COMMAND(ID_APP_ABOUT, &CMiniDrawDoc::OnAppAbout)
END_MESSAGE_MAP()


// Создание или уничтожение CMiniDrawDoc

CMiniDrawDoc::CMiniDrawDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CMiniDrawDoc::~CMiniDrawDoc()
{
}

BOOL CMiniDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CMiniDrawDoc

void CMiniDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CTypedPtrArray<CObArray, CLine*> LineArray;
		for (int i = 0; i < top; i++)
		{
			LineArray.Add(m_LineArray[i]);
		}
		LineArray.Serialize(ar);
	}
	else
	{
		m_LineArray.Serialize(ar);
		top = m_LineArray.GetSize();
	}
}


#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMiniDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMiniDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMiniDrawDoc::SetSearchContent(const CString& value)
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

// Диагностика CMiniDrawDoc

#ifdef _DEBUG
void CMiniDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMiniDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



void CMiniDrawDoc::DeleteContents()
{
	int Index = (int)m_LineArray.GetSize();
	while (Index--)
		delete m_LineArray.GetAt(Index);
	m_LineArray.RemoveAll();
	CDocument::DeleteContents();
	top = 0;
}




void CMiniDrawDoc::OnEditClearAll()
{
	DeleteContents();
	UpdateAllViews(0);
	SetModifiedFlag();
}


void CMiniDrawDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((int)m_LineArray.GetSize());
}


void CMiniDrawDoc::OnEditUndo()
{
	if (top > 0)
	{
		if (top != GetNumLines())
		{
			m_LineArray.RemoveAt(top);
		}
		top--;
	}
	UpdateAllViews(0);
	SetModifiedFlag();
}


void CMiniDrawDoc::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((int)top);
}



void CMiniDrawDoc::OnEditRedo()
{
	if (top < GetNumLines())
		top++;
	UpdateAllViews(0);
}


void CMiniDrawDoc::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	bool flag = top == GetNumLines();
	pCmdUI->Enable(!flag);
}

void CMiniDrawDoc::OnAppAbout()
{
	// TODO: добавьте свой код обработчика команд
}
