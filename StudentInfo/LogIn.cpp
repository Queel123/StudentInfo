// LogIn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "LogIn.h"
#include "afxdialogex.h"


// LogIn �Ի���

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


// LogIn ��Ϣ�������
BOOL LogIn::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_rsLogInSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsLogInSet.IsOpen())
	{
		AfxMessageBox(_T("���ݿ��ʧ�ܣ�"));
		return TRUE;
	}
	else if(m_rsLogInSet.IsBOF())
	{
		AfxMessageBox(_T("���ݼ��գ�"));
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void LogIn::OnEnChangeEditUserid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}




void LogIn::OnBnClickedBnLog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strPassword.IsEmpty() || m_strUserId.IsEmpty())
	{
		AfxMessageBox(_T("��������Ӧ����"));
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
			AfxMessageBox(_T("��¼ʧ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nResponse = AfxMessageBox(_T("�Ƿ����Ҫ�˳�ϵͳ?"),MB_YESNO);
	if(nResponse == IDYES)
		CDialog::OnOK();
}

// ��նԻ�������ʾѧ����Ϣ�ı༭��ؼ�
void LogIn::ClearEditData(void)
{
	m_strPassword = "";
	m_strUserId = "";
	
	UpdateData(FALSE);
	return;
}

// �������ݳ�Ա��ֵ���ݸ��Ի���ؼ���ʾ����
void LogIn::ReadRecord(void)
{

	m_strPassword = m_rsLogInSet.m_Password;
	m_strUserId = m_rsLogInSet.m_UserId;

	UpdateData(FALSE);
	return;
}

// ���ؼ�����ʾ����Ϣ���ݸ����ݳ�Ա
void LogIn::WriteRecord(void)
{
	UpdateData(TRUE);
	m_rsLogInSet.m_UserId=m_strUserId;
	m_rsLogInSet.m_Password=m_strPassword;

}