
// amsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CamsDlg �Ի���
class CamsDlg : public CDialogEx
{
// ����
public:
	CamsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

  void add(CString str);

	// ���ɵ���Ϣӳ�亯��
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
