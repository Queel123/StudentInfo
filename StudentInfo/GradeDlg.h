#pragma once
#include "afxcmn.h"
#include "CGradeSet.h"


// CGradeDlg 对话框

class CGradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGradeDlg)

public:
	CGradeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGradeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_GRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnExit();
	CString m_strSNo_Q;
	CListCtrl m_listDisp;
	CString m_strCCount;
	CString m_strCAvg;
	CString m_strCReditS;
	// 对应于建立的记录集
	CGradeSet m_rsGradeSet;
	// 存储连接3个数据库表的字符串
	CString m_strConnCondition;
	// 对话框初始化代码
	BOOL OnInitDialog(void);
};
