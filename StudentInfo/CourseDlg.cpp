// CourseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CourseDlg.h"
#include "afxdialogex.h"
#include "CCourseSet.h"

// CCourseDlg �Ի���

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


// CCourseDlg ��Ϣ�������

BOOL CCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_rsCourseSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsCourseSet.IsOpen())
	{
		AfxMessageBox(_T("���ݿ��ʧ�ܣ�"));
		return TRUE;
	}
	else if(m_rsCourseSet.IsBOF())
	{
		AfxMessageBox(_T("���ݼ��գ�"));
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CCourseDlg::OnBnClickedBnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strCNo.IsEmpty() || m_strCName.IsEmpty() || m_strCRedit.IsEmpty())
	{
		AfxMessageBox(_T("��������Ӧ���ݣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strCNo_Q.IsEmpty() && m_strCNAME_Q.IsEmpty())
	{
		m_rsCourseSet.m_strFilter = "";
		m_rsCourseSet.Requery();
		if(m_rsCourseSet.IsBOF())
		{
			AfxMessageBox(_T("���ݼ��գ�"));
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
		AfxMessageBox(_T("û�в鵽��ؼ�¼��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsCourseSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsCourseSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CCourseDlg::OnBnClickedBnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(AfxMessageBox(_T("ȷ��Ҫɾ��������¼��?"),MB_YESNO)!=IDYES)
		return;
	m_rsCourseSet.Delete();
	m_rsCourseSet.Requery();
	if(m_rsCourseSet.IsBOF())
	{
		AfxMessageBox(_T("�����Ѿ�û�м�¼�ˣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CCourseDlg::OnBnClickedBnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


// ��նԻ�������ʾѧ����Ϣ�ı༭��ؼ�
void CCourseDlg::ClearEditData(void)
{
	m_strCNo = "";
	m_strCName = "";
	m_strCRedit = "";

	
	UpdateData(FALSE);
	return;
}


// �������ݳ�Ա��ֵ���ݸ��Ի���ؼ���ʾ����
void CCourseDlg::ReadRecord(void)
{

	m_strCNo = m_rsCourseSet.m_CNo;
	m_strCName = m_rsCourseSet.m_CName;
	m_strCRedit = m_rsCourseSet.m_CRedit;


	UpdateData(FALSE);
	return;
}


// ���ؼ�����ʾ����Ϣ���ݸ����ݳ�Ա
void CCourseDlg::WriteRecord(void)
{
	UpdateData(TRUE);
	m_rsCourseSet.m_CNo=m_strCNo;
	m_rsCourseSet.m_CName=m_strCName;
	m_rsCourseSet.m_CRedit=m_strCRedit;
	

}


// ���ݼ�¼���Ƿ�Ϊ�ա���¼ָ���λ�ü������ݿ�Ĳ������������á�������¼ָ�롱��ť��ʹ��״̬
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


// ���ݶ����ݿ�Ĳ����������ñ༭��ؼ��Ŀɱ༭״̬
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