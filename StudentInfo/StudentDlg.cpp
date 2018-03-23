// StudentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StudentDlg.h"
#include "afxdialogex.h"


// CStudentDlg 对话框

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentDlg::IDD, pParent)
	, m_strSNo_Q(_T(""))
	, m_strSNAME_Q(_T(""))
	, m_strSNo(_T(""))
	, m_strSSDate(_T(""))
	, m_strSSex(_T(""))
	, m_strSMajor(_T(""))
	, m_strSBDate(_T(""))
	, m_strSName(_T(""))
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
	, m_bAdd(false)
	, m_bEdit(false)
{

}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SNo_Q, m_strSNo_Q);
	DDX_Text(pDX, IDC_EDIT_SNAME_Q, m_strSNAME_Q);
	DDX_Text(pDX, IDC_EDIT_SNo, m_strSNo);
	DDX_Text(pDX, IDC_EDIT_SSDATE, m_strSSDate);
	DDX_Text(pDX, IDC_EDIT_SSEX, m_strSSex);
	DDX_Text(pDX, IDC_EDIT_SMAJOR, m_strSMajor);
	DDX_Text(pDX, IDC_EDIT_SBDATE, m_strSBDate);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_strSName);
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BN_CANCEL, &CStudentDlg::OnBnClickedBnCancel)

	ON_BN_CLICKED(IDC_BN_FIRST, &CStudentDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_QUERY, &CStudentDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_PREV, &CStudentDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CStudentDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CStudentDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_ADD, &CStudentDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CStudentDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CStudentDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CStudentDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_EXIT, &CStudentDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()


// CStudentDlg 消息处理程序


BOOL CStudentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	m_rsStudentSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsStudentSet.IsOpen())
	{
		AfxMessageBox(_T("数据库打开失败！"));
		return TRUE;
	}
	else if(m_rsStudentSet.IsBOF())
	{
		AfxMessageBox(_T("数据集空！"));
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
		SetEditState();
	}
	else
	{
		m_bEmpty = false;
		m_rsStudentSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}




void CStudentDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsStudentSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CStudentDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strSNo_Q.IsEmpty() && m_strSNAME_Q.IsEmpty())
	{
		m_rsStudentSet.m_strFilter = "";
		m_rsStudentSet.Requery();
		if(m_rsStudentSet.IsBOF())
		{
			AfxMessageBox(_T("数据集空！"));
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsStudentSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbSNoQInput = FALSE;
	if(!m_strSNo_Q.IsEmpty())
	{
		m_rsStudentSet.m_strFilter = "SNo='"+m_strSNo_Q;
		m_rsStudentSet.m_strFilter = m_rsStudentSet.m_strFilter + "'";

		mbSNoQInput = TRUE;
	}
	if(!m_strSNAME_Q.IsEmpty())
	{
		if(mbSNoQInput)
		{
			m_rsStudentSet.m_strFilter = m_rsStudentSet.m_strFilter + " AND SName='";
			m_rsStudentSet.m_strFilter = m_rsStudentSet.m_strFilter + m_strSNAME_Q;
			m_rsStudentSet.m_strFilter = m_rsStudentSet.m_strFilter + "'";
		}
		else
		{
			m_rsStudentSet.m_strFilter = "SName='" + m_strSNAME_Q;
			m_rsStudentSet.m_strFilter = m_rsStudentSet.m_strFilter + "'";
		}
	}
	m_rsStudentSet.Requery();
	if(m_rsStudentSet.IsEOF())
	{
		AfxMessageBox(_T("没有查到相关记录！"));
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsStudentSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}
}


void CStudentDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsStudentSet.MovePrev();
	if(m_rsStudentSet.IsBOF())
	{
		m_rsStudentSet.MoveFirst();
		m_bFirst = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CStudentDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsStudentSet.MoveNext();
	if(m_rsStudentSet.IsEOF())
	{
		m_rsStudentSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CStudentDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsStudentSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CStudentDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_SNo);
	pWnd -> SetFocus();
}


void CStudentDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_SNAME);
	pWnd -> SetFocus();
}


void CStudentDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AfxMessageBox(_T("确定要删除此条记录吗?"),MB_YESNO)!=IDYES)
		return;
	m_rsStudentSet.Delete();
	m_rsStudentSet.Requery();
	if(m_rsStudentSet.IsBOF())
	{
		AfxMessageBox(_T("表中已经没有记录了！"));
		ClearEditData();
		m_bEmpty=true;
		SetMoveBNState();
		return;
	}
	m_bFirst=true;
	m_bLast=false;
	ReadRecord();
	SetMoveBNState();
}

//保存按钮
void CStudentDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strSNo.IsEmpty() || m_strSName.IsEmpty() || m_strSSex.IsEmpty() || m_strSMajor.IsEmpty() || m_strSSDate.IsEmpty() || m_strSBDate.IsEmpty())
	{
		AfxMessageBox(_T("请输入相应数据！"));
		CWnd * pWnd;	
		pWnd = GetDlgItem(IDC_EDIT_SNo);
		pWnd->SetFocus();
		return;
	}

	if(m_bAdd)
	{
		m_rsStudentSet.AddNew();

	}
	else
	{
		m_rsStudentSet.Edit();
	}
	WriteRecord();
	m_rsStudentSet.Update();
	m_rsStudentSet.Requery();
	m_rsStudentSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}
//	int nResponse = AfxMessageBox(_T("是否真的要退出系统?"),MB_YESNO);
//	if(nResponse == IDYES)
//		CDialog::OnOK();

//退出按钮
void CStudentDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


// 清空对话框中显示学生信息的编辑框控件
void CStudentDlg::ClearEditData(void)
{
	m_strSNo = "";
	m_strSName = "";
	m_strSSex = "";
	m_strSMajor = "";
	m_strSBDate = "";
	m_strSSDate = "";
	
	UpdateData(FALSE);
	return;
}


// 将域数据成员的值传递给对话框控件显示出来
void CStudentDlg::ReadRecord(void)
{

	m_strSNo = m_rsStudentSet.m_SNo;
	m_strSName = m_rsStudentSet.m_SName;
	m_strSSex = m_rsStudentSet.m_SSex;
	m_strSMajor = m_rsStudentSet.m_SMajor;
	m_strSBDate = m_rsStudentSet.m_SBirthDate.Format("%Y-%m-%d");
	m_strSSDate = m_rsStudentSet.m_SSchoolDate.Format("%Y-%m-%d");

	UpdateData(FALSE);
	return;
}


// 将控件中显示的信息传递给数据成员
void CStudentDlg::WriteRecord(void)
{
	UpdateData(TRUE);
	m_rsStudentSet.m_SNo=m_strSNo;
	m_rsStudentSet.m_SName=m_strSName;
	m_rsStudentSet.m_SSex=m_strSSex;
	m_rsStudentSet.m_SMajor=m_strSMajor;
	
	int a,b,c;
	CString timestrB = m_strSBDate;
	sscanf(timestrB.GetBuffer(timestrB.GetLength()), "%d-%d-%d", &a, &b, &c);
	CTime timeB(a,b,c,0,0,0);
	m_rsStudentSet.m_SBirthDate = timeB;
	CString timestrS = m_strSSDate;
	sscanf(timestrS.GetBuffer(timestrS.GetLength()), "%d-%d-%d", &a, &b, &c);
	CTime timeS(a,b,c,0,0,0);
	m_rsStudentSet.m_SSchoolDate = timeS;
}


// 根据记录集是否为空、记录指针的位置及对数据库的操作类型来设置“滚动记录指针”按钮的使用状态
void CStudentDlg::SetMoveBNState(void)
{
	CWnd *pWnd;
	if(m_bEdit||m_bEmpty)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd -> EnableWindow(FALSE);
		return;
	}	
	if(m_bFirst)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd -> EnableWindow(TRUE);
	}
	else if(m_bLast)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd -> EnableWindow(FALSE);
	}
	else
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd -> EnableWindow(TRUE);
	}
	return;
}


// 根据对数据库的操作类型设置编辑框控件的可编辑状态
void CStudentDlg::SetEditState(void)
{
	CWnd *pWnd;
	if(m_bEdit)
	{
		pWnd = GetDlgItem(IDC_BN_ADD);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_EDIT);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_DELETE);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_QUERY);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_SAVE);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_CANCEL);
		pWnd -> EnableWindow(TRUE);
		
		pWnd = GetDlgItem(IDC_EDIT_SNo);
		if(m_bAdd)
			pWnd -> EnableWindow(TRUE);
		else
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SNAME);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SSEX);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SMAJOR);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SBDATE);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SSDATE);
		pWnd -> EnableWindow(TRUE);
	}
	else
	{
		pWnd = GetDlgItem(IDC_BN_ADD);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_EDIT);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_DELETE);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_QUERY);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_SAVE);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_CANCEL);
		pWnd -> EnableWindow(FALSE);
		
		pWnd = GetDlgItem(IDC_EDIT_SNo);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SNAME);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SSEX);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SMAJOR);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SBDATE);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SSDATE);
		pWnd -> EnableWindow(FALSE);
	}
	return;
}
