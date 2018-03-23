#pragma once

#include "CSCChoiceSet.h"
// CSCChoiceDlg �Ի���

class CSCChoiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSCChoiceDlg)

public:
	CSCChoiceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSCChoiceDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SCCHOICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_strCNo;
	CString m_strCNo_Q;
	CString m_strSCGrade;
	CString m_strSNo;
	CString m_strSNo_Q;
// ���CStudentSet�Ķ�����Ϊһ�����ݳ�Ա
	CSCChoiceSet m_rsSCChoiceSet;
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
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnExit();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnAdd();
};
