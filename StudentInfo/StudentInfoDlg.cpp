
// StudentInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"
#include "LogIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInfoDlg �Ի���




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


// CStudentInfoDlg ��Ϣ�������

BOOL CStudentInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStudentInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStudentInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentInfoDlg::OnBnClickedBnStudent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStudentDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnCourse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCourseDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnScchoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSCChoiceDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnGrade()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CGradeDlg dlg;
	dlg.DoModal();
}


void CStudentInfoDlg::OnBnClickedBnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nResponse = AfxMessageBox(_T("�Ƿ����Ҫ�˳�ϵͳ?"),MB_YESNO);
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



