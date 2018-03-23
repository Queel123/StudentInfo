// CSCChoiceSet.h : CSCChoiceSet ���ʵ��



// CSCChoiceSet ʵ��

// ���������� 2017��6��7��, 21:22

#include "stdafx.h"
#include "CSCChoiceSet.h"
IMPLEMENT_DYNAMIC(CSCChoiceSet, CRecordset)

CSCChoiceSet::CSCChoiceSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SNo = L"";
	m_CNo = L"";
	m_SCGrade = L"";
	m_nFields = 3;
	m_nDefaultType = snapshot;
}
/*#error ��ȫ���⣺�����ַ������ܰ������롣*/
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSCChoiceSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=C:\\USERS\\ADMINISTRATOR\\DOCUMENTS\\TENCENT FILES\\495678265\\FILERECV\\MOBILEFILE\\StudentInfo.accdb;DefaultDir=C:\\USERS\\ADMINISTRATOR\\DOCUMENTS\\TENCENT FILES\\495678265\\FILERECV\\MOBILEFILE;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CSCChoiceSet::GetDefaultSQL()
{
	return _T("[SCCHOICE]");
}

void CSCChoiceSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[SCGrade]"), m_SCGrade);

}
/////////////////////////////////////////////////////////////////////////////
// CSCChoiceSet ���

#ifdef _DEBUG
void CSCChoiceSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSCChoiceSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


