// COptionsDlg.cpp: 实现文件
//

#include "pch.h"
#include "Chronograph.h"
#include "afxdialogex.h"
#include "COptionsDlg.h"


// COptionsDlg 对话框

IMPLEMENT_DYNAMIC(COptionsDlg, CDialogEx)

COptionsDlg::COptionsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPTION, pParent)
{
	m_mode = 0;
	m_total = 300;
	m_fontface=CString(L"宋体");
	m_fontcolor = 0;
	m_fontsize = 240;
	m_backcolor = 0;
	m_transparent = false;
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FONT_SIZE, m_fontsize);
	DDX_Radio(pDX, IDC_MODE_REAL, m_mode);
	DDX_Text(pDX, IDC_TOTAL, m_total);
	DDX_Check(pDX, IDC_TRANSPARENT, m_transparent);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_FONT_FACE, &COptionsDlg::OnCbnSelchangeFontFace)
	ON_BN_CLICKED(IDC_FONT_COLOR, &COptionsDlg::OnBnClickedFontColor)
	ON_BN_CLICKED(IDC_BACK_COLOR, &COptionsDlg::OnBnClickedBackColor)
END_MESSAGE_MAP()


// COptionsDlg 消息处理程序


void COptionsDlg::OnCbnSelchangeFontFace()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCFontComboBox* pCB = (CMFCFontComboBox*)GetDlgItem(IDC_FONT_FACE);
	m_fontface=pCB->GetSelFont()->m_strName;
}


void COptionsDlg::OnBnClickedFontColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCColorButton* pCB = (CMFCColorButton*)GetDlgItem(IDC_FONT_COLOR);
	m_fontcolor = pCB->GetColor();
}


void COptionsDlg::OnBnClickedBackColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCColorButton* pCB = (CMFCColorButton*)GetDlgItem(IDC_BACK_COLOR);
	m_backcolor = pCB->GetColor();
}


BOOL COptionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CMFCFontComboBox*)GetDlgItem(IDC_FONT_FACE))->SelectFont(m_fontface);
	((CMFCColorButton*)GetDlgItem(IDC_FONT_COLOR))->SetColor(m_fontcolor);
	((CMFCColorButton*)GetDlgItem(IDC_BACK_COLOR))->SetColor(m_backcolor);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
