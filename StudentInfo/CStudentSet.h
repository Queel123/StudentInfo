// CStudentSet.h : CStudentSet ������

#pragma once

// ���������� 2017��6��6��, 18:05

class CStudentSet : public CRecordset
{
public:
	CStudentSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��
	//�˴���CStringW�����޸�ΪCString���ͣ��������������Щ�ַ�����ΪASC2�ַ���������
	CString	m_SNo;	//ѧ��
	CString	m_SName;	//����
	CString	m_SSex;	//�Ա�
	CString	m_SMajor;	//רҵ
	CTime	m_SBirthDate;	//��������
	CTime	m_SSchoolDate;	//��ѧ����

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


