// CGradeSet.h : CGradeSet ���ʵ��



// CGradeSet ʵ��

// ���������� 2017��6��8��, 14:31

#include "stdafx.h"
#include "CGradeSet.h"
IMPLEMENT_DYNAMIC(CGradeSet, CRecordset)

CGradeSet::CGradeSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_COURSECNo = L"";
	m_COURSECName = L"";
	m_COURSECRedit = 0;
	m_SCCHOICESNo = L"";
	m_SCCHOICECNo = L"";
	m_SCCHOICESCGrade = 0;
	m_STUDENTSNo = L"";
	m_STUDENTSName = L"";
	m_STUDENTSSex = L"";
	m_STUDENTSMajor = L"";
	m_STUDENTSBirthDate;
	m_STUDENTSSchoolDate;
	m_nFields = 12;
	m_nDefaultType = snapshot;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CGradeSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=C:\\Users\\Administrator\\Documents\\Tencent Files\\495678265\\FileRecv\\MobileFile\\StudentInfo.accdb;DefaultDir=C:\\Users\\Administrator\\Documents\\Tencent Files\\495678265\\FileRecv\\MobileFile;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CGradeSet::GetDefaultSQL()
{
	return _T("[COURSE],[SCCHOICE],[STUDENT]");
}

void CGradeSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[COURSE].[CNo]"), m_COURSECNo);
	RFX_Text(pFX, _T("[COURSE].[CName]"), m_COURSECName);
	RFX_Long(pFX, _T("[COURSE].[CRedit]"), m_COURSECRedit);
	RFX_Text(pFX, _T("[SCCHOICE].[SNo]"), m_SCCHOICESNo);
	RFX_Text(pFX, _T("[SCCHOICE].[CNo]"), m_SCCHOICECNo);
	RFX_Long(pFX, _T("[SCCHOICE].[SCGrade]"), m_SCCHOICESCGrade);
	RFX_Text(pFX, _T("[STUDENT].[SNo]"), m_STUDENTSNo);
	RFX_Text(pFX, _T("[STUDENT].[SName]"), m_STUDENTSName);
	RFX_Text(pFX, _T("[STUDENT].[SSex]"), m_STUDENTSSex);
	RFX_Text(pFX, _T("[STUDENT].[SMajor]"), m_STUDENTSMajor);
	RFX_Date(pFX, _T("[STUDENT].[SBirthDate]"), m_STUDENTSBirthDate);
	RFX_Date(pFX, _T("[STUDENT].[SSchoolDate]"), m_STUDENTSSchoolDate);

}
/////////////////////////////////////////////////////////////////////////////
// CGradeSet ���

#ifdef _DEBUG
void CGradeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGradeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


