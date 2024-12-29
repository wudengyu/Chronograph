#pragma once
#include "afxdialogex.h"


// COptionsDlg 对话框

class COptionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COptionsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_fontface;
	COLORREF m_fontcolor;
	COLORREF m_backcolor;
	int m_fontsize;
	int m_mode;
	int m_total;
	BOOL m_transparent;
	afx_msg void OnCbnSelchangeFontFace();
	afx_msg void OnBnClickedFontColor();
	afx_msg void OnBnClickedBackColor();
	virtual BOOL OnInitDialog();
};
