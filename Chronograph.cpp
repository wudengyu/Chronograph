
// Chronograph.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Chronograph.h"
#include "CMainWindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChronographApp

BEGIN_MESSAGE_MAP(CChronographApp, CWinApp)
END_MESSAGE_MAP()

// 唯一的 CChronographApp 对象

CChronographApp theApp;


// CChronographApp 初始化

BOOL CChronographApp::InitInstance()
{
	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CChronographApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	return CWinApp::ExitInstance();
}





