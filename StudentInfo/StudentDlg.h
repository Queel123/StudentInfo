#pragma once

#include "CStudentSet.h"  //���������CStudentSet������ݳ�Ա

// CStudentDlg �Ի���

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStudentDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_STUDENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBnCancel();
	CString m_strSNo_Q;
	CString m_strSNAME_Q;
	CString m_strSNo;
	CString m_strSSDate;
	CString m_strSSex;
	CString m_strSMajor;
	CString m_strSBDate;
	CString m_strSName;

// ��Ա����
public:

	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnExit();

// ���CStudentSet�Ķ�����Ϊһ�����ݳ�Ա
	CStudentSet m_rsStudentSet;

	// �ռ�¼����־
	bool m_bEmpty;
	// ��¼ָ��ָ���һ����¼��־
	bool m_bFirst;
	// ��¼ָ��ָ�����һ����¼��־
	bool m_bLast;
	// ��Ӽ�¼������־
	bool m_bAdd;
	// �޸ļ�¼������־
	bool m_bEdit;
	// ��նԻ�������ʾѧ����Ϣ�ı༭��ؼ�
	void ClearEditData(void);
	// �������ݳ�Ա��ֵ���ݸ��Ի���ؼ���ʾ����
	void ReadRecord(void);
	// ���ؼ�����ʾ����Ϣ���ݸ����ݳ�Ա
	void WriteRecord(void);
	// ���ݼ�¼���Ƿ�Ϊ�ա���¼ָ���λ�ü������ݿ�Ĳ������������á�������¼ָ�롱��ť��ʹ��״̬
	void SetMoveBNState(void);
	// ���ݶ����ݿ�Ĳ����������ñ༭��ؼ��Ŀɱ༭״̬
	void SetEditState(void);
	// �Ի����ʼ������
	BOOL OnInitDialog(void);
};
