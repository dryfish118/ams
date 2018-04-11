
// amsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CamsDlg 对话框
class CamsDlg : public CDialogEx
{
// 构造
public:
	CamsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

  void add(CString str);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  CListBox m_list;
  int m_delay;
  afx_msg void OnSize(UINT nType, int cx, int cy);
};
