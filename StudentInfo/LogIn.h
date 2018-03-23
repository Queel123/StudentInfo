#pragma once

#include "StudentInfoDlg.h"
#include "loginset.h"
// LogIn 对话框

class LogIn : public CDialogEx
{
	DECLARE_DYNAMIC(LogIn)

public:
	LogIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LogIn();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditUserid();
	afx_msg void OnBnClickedBnLog();
	afx_msg void OnBnClickedBnExit();
	CString m_strPassword;
	CString m_strUserId;
	// 对应于建立的记录集
	LogInSet m_rsLogInSet;
	// 清空对话框中显示学生信息的编辑框控件
	void ClearEditData(void);
	// 将域数据成员的值传递给对话框控件显示出来
	void ReadRecord(void);
	// 将控件中显示的信息传递给数据成员
	void WriteRecord(void);
	// 对话框初始化代码
	BOOL OnInitDialog(void);
	// 空记录集标志
	bool m_bEmpty;
	// 记录指针指向第一条记录标志
	bool m_bFirst;
	// 记录指针指向最后一条记录标志
	bool m_bLast;
};
