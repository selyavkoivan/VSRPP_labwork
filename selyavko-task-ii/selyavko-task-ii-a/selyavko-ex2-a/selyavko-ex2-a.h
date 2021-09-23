
// selyavko-ex2-a.h: основной файл заголовка для приложения selyavko-ex2-a
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Cselyavkoex2aApp:
// Сведения о реализации этого класса: selyavko-ex2-a.cpp
//

class Cselyavkoex2aApp : public CWinAppEx
{
public:
	Cselyavkoex2aApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cselyavkoex2aApp theApp;
