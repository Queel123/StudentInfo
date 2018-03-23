// CourseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CourseDlg.h"
#include "afxdialogex.h"
#include "CCourseSet.h"

// CCourseDlg 对话框

IMPLEMENT_DYNAMIC(CCourseDlg, CDialogEx)

CCourseDlg::CCourseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCourseDlg::IDD, pParent)
	, m_strCNo(_T(""))
	, m_strCName(_T(""))
	, m_strCNAME_Q(_T(""))
	, m_strCNo_Q(_T(""))
	, m_strCRedit(_T(""))
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
	, m_bAdd(false)
	, m_bEdit(false)
{


}

CCourseDlg::~CCourseDlg()
{
}

void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_CNAME_Q, m_strCNAME_Q);

	DDX_Text(pDX, IDC_EDIT_CNo_Q, m_strCNo_Q);
	DDX_Text(pDX, IDC_EDIT_CREDIT, m_strCRedit);
	DDX_Text(pDX, IDC_EDIT_CNo, m_strCNo);
}


BEGIN_MESSAGE_MAP(CCourseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_SAVE, &CCourseDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_QUERY, &CCourseDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_FIRST, &CCourseDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CCourseDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CCourseDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CCourseDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_ADD, &CCourseDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CCourseDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CCourseDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CCourseDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CCourseDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()


// CCourseDlg 消息处理程序

BOOL CCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	m_rsCourseSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsCourseSet.IsOpen())
	{
		AfxMessageBox(_T("数据库打开失败！"));
		return TRUE;
	}
	else if(m_rsCourseSet.IsBOF())
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
		m_rsCourseSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CCourseDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strCNo.IsEmpty() || m_strCName.IsEmpty() || m_strCRedit.IsEmpty())
	{
		AfxMessageBox(_T("请输入相应数据！"));
		CWnd * pWnd;
		pWnd = GetDlgItem(IDC_EDIT_CNo);
		pWnd->SetFocus();
		return;
	}
	if(m_bAdd)
	{
		m_rsCourseSet.AddNew();
	}
	else
	{
		m_rsCourseSet.Edit();
	}
	WriteRecord();
	m_rsCourseSet.Update();
	m_rsCourseSet.Requery();
	m_rsCourseSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CCourseDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strCNo_Q.IsEmpty() && m_strCNAME_Q.IsEmpty())
	{
		m_rsCourseSet.m_strFilter = "";
		m_rsCourseSet.Requery();
		if(m_rsCourseSet.IsBOF())
		{
			AfxMessageBox(_T("数据集空！"));
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsCourseSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbCNoQInput = FALSE;
	if(!m_strCNo_Q.IsEmpty())
	{
		m_rsCourseSet.m_strFilter = "CNo='"+m_strCNo_Q;
		m_rsCourseSet.m_strFilter = m_rsCourseSet.m_strFilter + "'";

		mbCNoQInput = TRUE;
	}
	if(!m_strCNAME_Q.IsEmpty())
	{
		if(mbCNoQInput)
		{
			m_rsCourseSet.m_strFilter = m_rsCourseSet.m_strFilter + " AND CName='";
			m_rsCourseSet.m_strFilter = m_rsCourseSet.m_strFilter + m_strCNAME_Q;

			m_rsCourseSet.m_strFilter = m_rsCourseSet.m_strFilter + "'";
		}
		else
		{
			m_rsCourseSet.m_strFilter = "CName='" + m_strCNAME_Q;
			m_rsCourseSet.m_strFilter = m_rsCourseSet.m_strFilter + "'";
		}
	}
	m_rsCourseSet.Requery();
	if(m_rsCourseSet.IsEOF())
	{
		AfxMessageBox(_T("没有查到相关记录！"));
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsCourseSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}
}


void CCourseDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsCourseSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsCourseSet.MovePrev();
	if(m_rsCourseSet.IsBOF())
	{
		m_rsCourseSet.MoveFirst();
		m_bFirst = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsCourseSet.MoveNext();
	if(m_rsCourseSet.IsEOF())
	{
		m_rsCourseSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsCourseSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_CNo);
	pWnd -> SetFocus();
}


void CCourseDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_CNAME);
	pWnd -> SetFocus();
}


void CCourseDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AfxMessageBox(_T("确定要删除此条记录吗?"),MB_YESNO)!=IDYES)
		return;
	m_rsCourseSet.Delete();
	m_rsCourseSet.Requery();
	if(m_rsCourseSet.IsBOF())
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


void CCourseDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CCourseDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


// 清空对话框中显示学生信息的编辑框控件
void CCourseDlg::ClearEditData(void)
{
	m_strCNo = "";
	m_strCName = "";
	m_strCRedit = "";

	
	UpdateData(FALSE);
	return;
}


// 将域数据成员的值传递给对话框控件显示出来
void CCourseDlg::ReadRecord(void)
{

	m_strCNo = m_rsCourseSet.m_CNo;
	m_strCName = m_rsCourseSet.m_CName;
	m_strCRedit = m_rsCourseSet.m_CRedit;


	UpdateData(FALSE);
	return;
}


// 将控件中显示的信息传递给数据成员
void CCourseDlg::WriteRecord(void)
{
	UpdateData(TRUE);
	m_rsCourseSet.m_CNo=m_strCNo;
	m_rsCourseSet.m_CName=m_strCName;
	m_rsCourseSet.m_CRedit=m_strCRedit;
	

}


// 根据记录集是否为空、记录指针的位置及对数据库的操作类型来设置“滚动记录指针”按钮的使用状态
void CCourseDlg::SetMoveBNState(void)
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
void CCourseDlg::SetEditState(void)
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
		
		pWnd = GetDlgItem(IDC_EDIT_CNo);
		if(m_bAdd)
			pWnd -> EnableWindow(TRUE);
		else
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CNAME);
		pWnd -> EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_CREDIT);
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
		
		pWnd = GetDlgItem(IDC_EDIT_CNo);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CNAME);
		pWnd -> EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CREDIT);
		pWnd -> EnableWindow(FALSE);
	}
	return;
}