
// lab4Doc.h: интерфейс класса Clab4Doc 
//

#include <comdef.h>
#import "C:\Program files\Common Files\System\ado\msado15.dll" rename("EOF", "ADOEOF")


#pragma once


class Clab4Doc : public CDocument
{
protected: // создать только из сериализации
	Clab4Doc() noexcept;
	DECLARE_DYNCREATE(Clab4Doc)

// Атрибуты
public:

// Операции
public:
	ADODB::_CommandPtr GetCommand();

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
	virtual ~Clab4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	ADODB::_ConnectionPtr _db;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
