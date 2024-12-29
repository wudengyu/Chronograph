#include "pch.h"
#include "resource.h"
#include "CMainWindow.h"
#include "COptionsDlg.h"

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POP_START, &CMainWindow::OnPopStart)
	ON_COMMAND(ID_POP_RESET, &CMainWindow::OnPopReset)
	ON_COMMAND(ID_POP_OPTION, &CMainWindow::OnPopOption)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_POP_FULLSCREEN, &CMainWindow::OnPopFullscreen)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	m_textfont= CString();
	m_textcolor=RGB(0,0,0);
	m_textsize=240;
	m_bkcolor=RGB(255,255,255);
	m_transparent = false;
	m_bFullScreen = false;

	Create(NULL, L"Chronograph");
}

BOOL CMainWindow::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_LAYERED;
	return TRUE;
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!SetTimer(ID_TIMER_CLOCK, 500, NULL)) {
		MessageBox(L"注册定时器失败", L"错误",MB_ICONSTOP|MB_OK);
		return -1;
	}
	LoadAccelTable(MAKEINTRESOURCE(IDR_MAINFRAME));
	SetTransparent();
	OnPopReset();
	return 0;
}

void CMainWindow::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	time_t current = time(NULL);
	if (current == last) {
		return;
	}
	if (mode && !pause) {
		elapse += current - last;
	}
	switch (mode) {
	case 0:
		localtime_s(&timeinfo, &current);
		break;
	case 1:
		timeinfo.tm_hour = elapse / 3600;
		timeinfo.tm_min = elapse % 3600 / 60;
		timeinfo.tm_sec = elapse % 60;
		break;
	case 2:
		remain = total - elapse;
		if (remain >= 0) {
			timeinfo.tm_hour = remain / 3600;
			timeinfo.tm_min = remain % 3600 / 60;
			timeinfo.tm_sec = remain % 60;
		}
		break;
	}
	last = current;
	Invalidate();
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFrameWnd::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	wchar_t buffer[20];
	size_t lang = wcsftime(buffer, 20, L"%T", &timeinfo);
	CFont font;
	CBrush brush;
	brush.CreateSolidBrush(m_bkcolor);
	font.CreatePointFont(m_textsize, m_textfont);
	dc.SelectObject(&font);
	dc.SelectObject(&brush);
	dc.SetTextColor(m_textcolor);
	dc.SetBkMode(TRANSPARENT);
	DrawText(dc, buffer, lang, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	font.DeleteObject();

}

void CMainWindow::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(ID_TIMER_CLOCK);
	CFrameWnd::OnClose();
}


void CMainWindow::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXTMENU);
	CMenu* pContextMenu = menu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());

}

void CMainWindow::OnPopStart()
{
	// TODO: 在此添加命令处理程序代码
	if (pause)
		pause = false;
	else
		pause = true;
}

void CMainWindow::OnPopReset()
{
	// TODO: 在此添加命令处理程序代码
	last = time(NULL);
	elapse = 0;
	remain = 0;
	pause = true;
	switch (mode) {
	case 0:
		localtime_s(&timeinfo, &last);
		break;
	case 1:
		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec = 0;
		break;
	case 2:
		timeinfo.tm_hour = total / 3600;
		timeinfo.tm_min = total % 3600 / 60;
		timeinfo.tm_sec = total % 60;
		break;
	}
}

void CMainWindow::OnPopOption()
{
	// TODO: 在此添加命令处理程序代码
	int oldMode = mode;
	COptionsDlg optionDlg;
	optionDlg.m_mode = oldMode;
	optionDlg.m_total = total;
	optionDlg.m_fontface = m_textfont;
	optionDlg.m_fontcolor=m_textcolor;
	optionDlg.m_backcolor=m_bkcolor;
	optionDlg.m_fontsize = m_textsize/10;
	optionDlg.m_transparent = m_transparent;
	if (optionDlg.DoModal() == IDOK) {
		m_textfont = optionDlg.m_fontface;
		m_textsize = optionDlg.m_fontsize*10;
		m_textcolor = optionDlg.m_fontcolor;
		m_bkcolor = optionDlg.m_backcolor;
		mode = optionDlg.m_mode;
		total = optionDlg.m_total;
		m_transparent = optionDlg.m_transparent;
		if (mode != oldMode) {
			OnPopReset();
		}
		SetTransparent();
		//InvalidateRect(NULL,TRUE);
	}
}

BOOL CMainWindow::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CBrush brush(m_bkcolor);
	CRect rect;
	pDC->SelectObject(&brush);
	pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	return TRUE;
}


void CMainWindow::SetTransparent()
{
	// TODO: 在此处添加实现代码.
	if (m_transparent) {
		ModifyStyleEx(0, WS_EX_LAYERED);
		SetLayeredWindowAttributes(m_bkcolor, 100, LWA_COLORKEY);
	}
	else {
		ModifyStyleEx(WS_EX_LAYERED,0);
	}
}


void CMainWindow::OnPopFullscreen()
{
	// TODO: 在此添加命令处理程序代码
	if (m_bFullScreen) {
		ModifyStyle(0,WS_CAPTION | WS_SIZEBOX);
		ModifyStyleEx(0,WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE);
		MoveWindow(&m_preRect);
	}else{
		int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
		int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(&m_preRect);
		ModifyStyle(WS_CAPTION|WS_SIZEBOX, 0);
		ModifyStyleEx(WS_EX_WINDOWEDGE| WS_EX_CLIENTEDGE,0);
		MoveWindow(0, 0, nFullWidth, nFullHeight);
	}
	m_bFullScreen=!m_bFullScreen;
	
}


void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bFullScreen&&nChar == VK_ESCAPE) {
		OnPopFullscreen();
	}
	else {
		CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}
