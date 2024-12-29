
// Chronograph.h: Chronograph 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CChronographApp:
// 有关此类的实现，请参阅 Chronograph.cpp
//

class CChronographApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CChronographApp theApp;
