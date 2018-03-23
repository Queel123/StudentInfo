#pragma once

#include "CStudentSet.h"  //由于添加了CStudentSet类的数据成员

// CStudentDlg 对话框

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStudentDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_STUDENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBnCancel();
	CString m_strSNo_Q;
	CString m_strSNAME_Q;
	CString m_strSNo;
	CString m_strSSDate;
	CString m_strSSex;
	CString m_strSMajor;
	CString m_strSBDate;
	CString m_strSName;

// 成员函数
public:

	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnExit();

// 添加CStudentSet的对象作为一个数据成员
	CStudentSet m_rsStudentSet;

	// 空记录集标志
	bool m_bEmpty;
	// 记录指针指向第一条记录标志
	bool m_bFirst;
	// 记录指针指向最后一条记录标志
	bool m_bLast;
	// 添加记录操作标志
	bool m_bAdd;
	// 修改记录操作标志
	bool m_bEdit;
	// 清空对话框中显示学生信息的编辑框控件
	void ClearEditData(void);
	// 将域数据成员的值传递给对话框控件显示出来
	void ReadRecord(void);
	// 将控件中显示的信息传递给数据成员
	void WriteRecord(void);
	// 根据记录集是否为空、记录指针的位置及对数据库的操作类型来设置“滚动记录指针”按钮的使用状态
	void SetMoveBNState(void);
	// 根据对数据库的操作类型设置编辑框控件的可编辑状态
	void SetEditState(void);
	// 对话框初始化代码
	BOOL OnInitDialog(void);
};
