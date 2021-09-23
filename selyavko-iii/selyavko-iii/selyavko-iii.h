
// selyavko-iii.h: основной файл заголовка для приложения selyavko-iii
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CselyavkoiiiApp:
// Сведения о реализации этого класса: selyavko-iii.cpp
//

class CselyavkoiiiApp : public CWinAppEx
{
public:
	CselyavkoiiiApp() noexcept;


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

extern CselyavkoiiiApp theApp;
