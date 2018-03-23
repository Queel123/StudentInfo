// LogInSet.h : LogInSet 类的实现



// LogInSet 实现

// 代码生成在 2017年6月10日, 15:31

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[UserId]"), m_UserId);
	RFX_Text(pFX, _T("[Password]"), m_Password);

}
/////////////////////////////////////////////////////////////////////////////
// LogInSet 诊断

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


