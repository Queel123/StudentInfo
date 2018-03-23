// CCourseSet.h : CCourseSet 类的实现



// CCourseSet 实现

// 代码生成在 2017年6月7日, 19:31

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
/*#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。*/
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[CName]"), m_CName);
	RFX_Text(pFX, _T("[CRedit]"), m_CRedit);

}
/////////////////////////////////////////////////////////////////////////////
// CCourseSet 诊断

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


