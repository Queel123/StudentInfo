// CCourseSet.h : CCourseSet ���ʵ��



// CCourseSet ʵ��

// ���������� 2017��6��7��, 19:31

#include "stdafx.h"
#include "CCourseSet.h"
IMPLEMENT_DYNAMIC(CCourseSet, CRecordset)

CCourseSet::CCourseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CNo = L"";
	m_CName = L"";
	m_CRedit = L"";
	m_nFields = 3;
	m_nDefaultType = snapshot;
}
/*#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��*/
CString CCourseSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=C:\\USERS\\ADMINISTRATOR\\DOCUMENTS\\TENCENT FILES\\495678265\\FILERECV\\MOBILEFILE\\StudentInfo.accdb;DefaultDir=C:\\USERS\\ADMINISTRATOR\\DOCUMENTS\\TENCENT FILES\\495678265\\FILERECV\\MOBILEFILE;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CCourseSet::GetDefaultSQL()
{
	return _T("[COURSE]");
}

void CCourseSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[CName]"), m_CName);
	RFX_Text(pFX, _T("[CRedit]"), m_CRedit);

}
/////////////////////////////////////////////////////////////////////////////
// CCourseSet ���

#ifdef _DEBUG
void CCourseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCourseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


