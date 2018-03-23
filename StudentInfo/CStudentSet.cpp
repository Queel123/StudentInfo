// CStudentSet.h : CStudentSet ���ʵ��



// CStudentSet ʵ��

// ���������� 2017��6��6��, 18:05

#include "stdafx.h"
#include "CStudentSet.h"
IMPLEMENT_DYNAMIC(CStudentSet, CRecordset)

CStudentSet::CStudentSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SNo = L"";
	m_SName = L"";
	m_SSex = L"";
	m_SMajor = L"";
	m_SBirthDate;
	m_SSchoolDate;
	m_nFields = 6;
	m_nDefaultType = snapshot;
}
/*#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��*/
CString CStudentSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=C:\\USERS\\ADMINISTRATOR\\DOCUMENTS\\TENCENT FILES\\495678265\\FileRecv\\MobileFile\\StudentInfo.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CStudentSet::GetDefaultSQL()
{
	return _T("[STUDENT]");
}

void CStudentSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Text(pFX, _T("[SName]"), m_SName);
	RFX_Text(pFX, _T("[SSex]"), m_SSex);
	RFX_Text(pFX, _T("[SMajor]"), m_SMajor);
	RFX_Date(pFX, _T("[SBirthDate]"), m_SBirthDate);
	RFX_Date(pFX, _T("[SSchoolDate]"), m_SSchoolDate);

}
/////////////////////////////////////////////////////////////////////////////
// CStudentSet ���

#ifdef _DEBUG
void CStudentSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudentSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


