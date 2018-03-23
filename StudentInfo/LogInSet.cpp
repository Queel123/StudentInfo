// LogInSet.h : LogInSet ���ʵ��



// LogInSet ʵ��

// ���������� 2017��6��10��, 15:31

#include "stdafx.h"
#include "LogInSet.h"
IMPLEMENT_DYNAMIC(LogInSet, CRecordset)

LogInSet::LogInSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_UserId = L"";
	m_Password = L"";
	m_nFields = 2;
	m_nDefaultType = snapshot;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString LogInSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=C:\\Users\\Administrator\\Documents\\Tencent Files\\495678265\\FileRecv\\MobileFile\\StudentInfo.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString LogInSet::GetDefaultSQL()
{
	return _T("[LOG]");
}

void LogInSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[UserId]"), m_UserId);
	RFX_Text(pFX, _T("[Password]"), m_Password);

}
/////////////////////////////////////////////////////////////////////////////
// LogInSet ���

#ifdef _DEBUG
void LogInSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void LogInSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


