#pragma once
#include "afxcmn.h"
#include "CGradeSet.h"


// CGradeDlg �Ի���

class CGradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGradeDlg)

public:
	CGradeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGradeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_GRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnExit();
	CString m_strSNo_Q;
	CListCtrl m_listDisp;
	CString m_strCCount;
	CString m_strCAvg;
	CString m_strCReditS;
	// ��Ӧ�ڽ����ļ�¼��
	CGradeSet m_rsGradeSet;
	// �洢����3�����ݿ����ַ���
	CString m_strConnCondition;
	// �Ի����ʼ������
	BOOL OnInitDialog(void);
};
