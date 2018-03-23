// CStudentSet.h : CStudentSet 类的实现



// CStudentSet 实现

// 代码生成在 2017年6月6日, 18:05

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
/*#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。*/
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Text(pFX, _T("[SName]"), m_SName);
	RFX_Text(pFX, _T("[SSex]"), m_SSex);
	RFX_Text(pFX, _T("[SMajor]"), m_SMajor);
	RFX_Date(pFX, _T("[SBirthDate]"), m_SBirthDate);
	RFX_Date(pFX, _T("[SSchoolDate]"), m_SSchoolDate);

}
/////////////////////////////////////////////////////////////////////////////
// CStudentSet 诊断

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


