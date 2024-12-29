#pragma once
#include <afxwin.h>

class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();
private:
	RECT m_preRect;
	time_t last = 0;
	tm timeinfo = {};
	int total = 100, elapse = 0, remain = 0, mode = 0;
	bool pause = false;
	CString m_textfont;
	COLORREF m_textcolor;
	int m_textsize;
	COLORREF m_bkcolor;
	bool m_transparent;
	bool m_bFullScreen;

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnPopStart();
	afx_msg void OnPopOption();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPopReset();
	afx_msg void OnPopFullscreen();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void SetTransparent();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

