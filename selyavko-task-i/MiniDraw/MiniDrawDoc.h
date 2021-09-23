
// MiniDrawDoc.h: интерфейс класса CMiniDrawDoc 
//
#include<afxwin.h> // стандартные компоненты MFC
#include<afxext.h> // расширения библиотеки MFC
#include<afxdtctl.h> // поддержка общих элементов управления 
#include <afxtempl.h>   // шаблоны библиотеки MFC
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> // поддержка общих элементов  
#include <fstream>

#endif // _AFX_NO_AFXCMN_SUPPORT

using namespace std;

#pragma once
class CLine : public CObject
{
public:
	bool type;
	COLORREF color;

	DECLARE_SERIAL(CLine)


void Add(CLine* pLine, COLORREF color, bool type)
{
	this->type = type;
	this->color = color;
	this->m_X1 = pLine->m_X1;
	this->m_Y1 = pLine->m_Y1;
	this->m_X2 = pLine->m_X2;
	this->m_Y2 = pLine->m_Y2;
}

	int m_X1, m_Y1, m_X2, m_Y2;
	CLine()	{}
	CLine(int X1, int Y1, int X2, int Y2, COLORREF color, bool type)
	{
		m_X1 = X1; m_Y1 = Y1; m_X2 = X2; m_Y2 = Y2;
		this->color = color;
		this->type = type;
	}
	void Draw(CDC* PDC);
	virtual void Serialize(CArchive& ar);

};


class CMiniDrawDoc : public CDocument
{
protected: // создать только из сериализации
	CMiniDrawDoc() noexcept;
	DECLARE_DYNCREATE(CMiniDrawDoc)
	int top = 0;
	CTypedPtrArray<CObArray, CLine*> m_LineArray;
	
public:
	void AddLine(int X1, int Y1, int X2, int Y2, COLORREF, bool);
	CLine* GetLine(int Index);
	int GetNumLines();
	

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMiniDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

	virtual void DeleteContents();
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	

	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnAppAbout();
};

