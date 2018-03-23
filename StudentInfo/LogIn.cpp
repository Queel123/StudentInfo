// LogIn.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "LogIn.h"
#include "afxdialogex.h"


// LogIn 对话框

IMPLEMENT_DYNAMIC(LogIn, CDialogEx)

LogIn::LogIn(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogIn::IDD, pParent)
	, m_strPassword(_T(""))
	, m_strUserId(_T(""))
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
{

}

LogIn::~LogIn()
{
}

void LogIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserId);
}


BEGIN_MESSAGE_MAP(LogIn, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_USERID, &LogIn::OnEnChangeEditUserid)
	ON_BN_CLICKED(IDC_BN_LOG, &LogIn::OnBnClickedBnLog)
	ON_BN_CLICKED(IDC_BN_EXIT, &LogIn::OnBnClickedBnExit)
END_MESSAGE_MAP()


// LogIn 消息处理程序
BOOL LogIn::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	m_rsLogInSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsLogInSet.IsOpen())
	{
		AfxMessageBox(_T("数据库打开失败！"));
		return TRUE;
	}
	else if(m_rsLogInSet.IsBOF())
	{
		AfxMessageBox(_T("数据集空！"));
		m_bEmpty = true;
		ClearEditData();
	}
	else
	{
		m_bEmpty = false;
		m_rsLogInSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ClearEditData();

	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void LogIn::OnEnChangeEditUserid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void LogIn::OnBnClickedBnLog()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strPassword.IsEmpty() || m_strUserId.IsEmpty())
	{
		AfxMessageBox(_T("请输入相应数据"));
		CWnd * pWnd;	
		pWnd = GetDlgItem(IDC_EDIT_USERID);
		pWnd->SetFocus();
		return;
	}
	else 
	{	
		bool mbUserIdInput = FALSE;
		m_rsLogInSet.m_strFilter="UserId='"+m_strUserId;
		m_rsLogInSet.m_strFilter=m_rsLogInSet.m_strFilter+"'";
		m_rsLogInSet.m_strFilter=m_rsLogInSet.m_strFilter+" AND Password='";
		m_rsLogInSet.m_strFilter=m_rsLogInSet.m_strFilter+m_strPassword;
		m_rsLogInSet.m_strFilter=m_rsLogInSet.m_strFilter+"'";
		m_rsLogInSet.Requery();
		if(m_rsLogInSet.IsEOF())
		{	
			AfxMessageBox(_T("登录失败"));
			m_bEmpty=true;
			ClearEditData();
		}
		else
		{
			CStudentInfoDlg dlg;
			dlg.DoModal();
		}
	}
}


void LogIn::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	int nResponse = AfxMessageBox(_T("是否真的要退出系统?"),MB_YESNO);
	if(nResponse == IDYES)
		CDialog::OnOK();
}

// 清空对话框中显示学生信息的编辑框控件
void LogIn::ClearEditData(void)
{
	m_strPassword = "";
	m_strUserId = "";
	
	UpdateData(FALSE);
	return;
}

// 将域数据成员的值传递给对话框控件显示出来
void LogIn::ReadRecord(void)
{

	m_strPassword = m_rsLogInSet.m_Password;
	m_strUserId = m_rsLogInSet.m_UserId;

	UpdateData(FALSE);
	return;
}

// 将控件中显示的信息传递给数据成员
void LogIn::WriteRecord(void)
{
	UpdateData(TRUE);
	m_rsLogInSet.m_UserId=m_strUserId;
	m_rsLogInSet.m_Password=m_strPassword;

}