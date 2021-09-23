
// lab4.h: основной файл заголовка для приложения lab4
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Clab4App:
// Сведения о реализации этого класса: lab4.cpp
//

class Clab4App : public CWinApp
{
public:
	Clab4App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Clab4App theApp;
