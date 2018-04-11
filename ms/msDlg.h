
// msDlg.h : ͷ�ļ�
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

// CmsDlg �Ի���
class CmsDlg : public CDialogEx
{
// ����
public:
	CmsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
