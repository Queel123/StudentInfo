
// StudentInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"
#include "LogIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInfoDlg 对话框




CStudentInfoDlg::CStudentInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentInfoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStudentInfoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_STUDENT, &CStudentInfoDlg::OnBnClickedBnStudent)
	ON_BN_CLICKED(IDC_BN_COURSE, &CStudentInfoDlg::OnBnClickedBnCourse)
	ON_BN_CLICKED(IDC_BN_SCCHOICE, &CStudentInfoDlg::OnBnClickedBnScchoice)
	ON_BN_CLICKED(IDC_BN_GRADE, &CStudentInfoDlg::OnBnClickedBnGrade)
	ON_BN_CLICKED(IDC_BN_EXIT, &CStudentInfoDlg::OnBnClickedBnExit)
//	ON_BN_CLICKED(IDCANCEL, &CStudentInfoDlg::OnBnClickedCancel)

END_MESSAGE_MAP()


// CStudentInfoDlg 消息处理程序

BOOL CStudentInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStudentInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentInfoDlg::OnBnClickedBnStudent()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudentDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnCourse()
{
	// TODO: 在此添加控件通知处理程序代码
	CCourseDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnScchoice()
{
	// TODO: 在此添加控件通知处理程序代码
	CSCChoiceDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnGrade()
{
	// TODO: 在此添加控件通知处理程序代码
	CGradeDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	int nResponse = AfxMessageBox(_T("是否真的要退出系统?"),MB_YESNO);
	if(nResponse == IDYES)
		CDialog::OnOK();
}



void CStudentInfoDlg::SetAllItemsPos()
{	
	CRect rcDlg;
	GetClientRect(rcDlg);
	int dlgWidth = rcDlg.right - rcDlg.left;
	int dlgHeight = rcDlg.bottom - rcDlg.top;

	SetItemPos(IDC_BN_STUDENT,45,65,20,dlgWidth-70);
	SetItemPos(IDC_BN_COURSE,65,85,20,dlgWidth-70);
	SetItemPos(IDC_BN_SCCHOICE,85,105,20,dlgWidth-70);
	SetItemPos(IDC_BN_GRADE,105,125,20,dlgWidth-70);
	SetItemPos(IDC_BN_EXIT,125,145,20,dlgWidth-70);
	InvalidateRect(NULL, TRUE);
}

void CStudentInfoDlg::SetItemPos(UINT id, int top, int bottom, int left, int right)
	{
		CWnd * p = (CWnd *)GetDlgItem(id);
		CRect rc;

		p->GetWindowRect(rc);
		ScreenToClient(rc);
		rc.top = top;
		rc.bottom = bottom;
		rc.left = left;
		rc.right = right;
		p->MoveWindow(rc);
	}



