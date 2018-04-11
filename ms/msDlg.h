
// msDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

class CColorButton : public CButton
{
public:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    if ((lpDrawItemStruct->itemState & ODS_DISABLED) == ODS_DISABLED)
    {
      pDC->FillSolidRect(&lpDrawItemStruct->rcItem, 0x808080);
    }
    else
    {
      pDC->FillSolidRect(&lpDrawItemStruct->rcItem, 0x0000FF);
    }
  }
};

// CmsDlg 对话框
class CmsDlg : public CDialogEx
{
// 构造
public:
	CmsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  CColorButton m_button;
  afx_msg void OnBnClickedButton1();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnBnClickedButton2();
};
