// CGradeSet.h : CGradeSet ������

#pragma once

// ���������� 2017��6��8��, 14:31

class CGradeSet : public CRecordset
{
public:
	CGradeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGradeSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��
//��������ת�������� long&CString ��ת���� CString
	CString	m_COURSECNo;	//�γ̺�
	CString	m_COURSECName;	//�γ���
	long	m_COURSECRedit;	//ѧ��
	CString	m_SCCHOICESNo;	//ѧ��
	CString	m_SCCHOICECNo;	//�γ̺�
	long	m_SCCHOICESCGrade;	//�ɼ�
	CString	m_STUDENTSNo;	//ѧ��
	CString	m_STUDENTSName;	//����
	CString	m_STUDENTSSex;	//�Ա�
	CString	m_STUDENTSMajor;	//רҵ
	CTime	m_STUDENTSBirthDate;	//��������
	CTime	m_STUDENTSSchoolDate;	//��ѧ����

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


