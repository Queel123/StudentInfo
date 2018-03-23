#pragma once

#include "StudentInfoDlg.h"
#include "loginset.h"
// LogIn �Ի���

class LogIn : public CDialogEx
{
	DECLARE_DYNAMIC(LogIn)

public:
	LogIn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogIn();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditUserid();
	afx_msg void OnBnClickedBnLog();
	afx_msg void OnBnClickedBnExit();
	CString m_strPassword;
	CString m_strUserId;
	// ��Ӧ�ڽ����ļ�¼��
	LogInSet m_rsLogInSet;
	// ��նԻ�������ʾѧ����Ϣ�ı༭��ؼ�
	void ClearEditData(void);
	// �������ݳ�Ա��ֵ���ݸ��Ի���ؼ���ʾ����
	void ReadRecord(void);
	// ���ؼ�����ʾ����Ϣ���ݸ����ݳ�Ա
	void WriteRecord(void);
	// �Ի����ʼ������
	BOOL OnInitDialog(void);
	// �ռ�¼����־
	bool m_bEmpty;
	// ��¼ָ��ָ���һ����¼��־
	bool m_bFirst;
	// ��¼ָ��ָ�����һ����¼��־
	bool m_bLast;
};
