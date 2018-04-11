
// amsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ams.h"
#include "amsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CamsDlg 对话框




CamsDlg::CamsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CamsDlg::IDD, pParent)
  , m_delay(100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CamsDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CamsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_WM_HOTKEY()
  ON_WM_TIMER()
  ON_WM_SIZE()
END_MESSAGE_MAP()


// CamsDlg 消息处理程序
CRect m_rect;
BOOL CamsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

  RegisterHotKey(GetSafeHwnd(), 1, MOD_CONTROL | MOD_WIN, 'Q');
  RegisterHotKey(GetSafeHwnd(), 2, MOD_CONTROL | MOD_WIN, 'W');

  CRect rect;
  m_list.GetClientRect(&rect);
  m_list.ClientToScreen(&rect);
  ScreenToClient(rect);

  GetClientRect(&m_rect);
  m_rect.left = rect.left - m_rect.left;
  m_rect.top = rect.top - m_rect.top;
  m_rect.right = m_rect.right - rect.right;
  m_rect.bottom = m_rect.bottom - rect.bottom;

  SetDlgItemInt(IDC_EDIT_DELAY, m_delay);

  add(L"程序启动，快捷键是Ctrl+Win+Q");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CamsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CamsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

COLORREF getColor(const CPoint& point)
{
  HDC hdc = GetDC(NULL);
  COLORREF clr = GetPixel(hdc, point.x, point.y);
  ReleaseDC(NULL, hdc);
  return clr;
}

CPoint m_point;
COLORREF m_color;
void CamsDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
  if (nHotKeyId == 1)
  {
    GetCursorPos(&m_point);
    m_color = getColor(m_point);

    KillTimer(1);
    SetTimer(1, 10, NULL);

    add(L"开始监控");
  }
  else if (nHotKeyId == 2)
  {
    GetCursorPos(&m_point);
    m_color = getColor(m_point);

    KillTimer(2);
    SetTimer(2, 3000, NULL);
  }

  CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CamsDlg::add(CString str)
{
  SYSTEMTIME st = {0};
  GetLocalTime(&st);
  CString s;
  s.Format(L"[%.2d:%.2d:%.2d %.3d]    %s", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, str);
  int i = m_list.AddString(s);
  m_list.SetCurSel(i);
}


void CamsDlg::OnTimer(UINT_PTR nIDEvent)
{
  if (nIDEvent == 1)
  {
    COLORREF clr = getColor(m_point);
    if (clr != m_color)
    {
      KillTimer(1);

      m_delay = GetDlgItemInt(IDC_EDIT_DELAY);
      if (m_delay == 0)
      {
        m_delay = 100;
      }

      SetTimer(3, m_delay, NULL);
      add(L"变色了");
    }
    else
    {
      add(L"未变色");
    }
  }
  else if (nIDEvent == 3)
  {
    KillTimer(3);

    SetCursorPos(m_point.x, m_point.y);
    CWnd* pWnd = WindowFromPoint(m_point);
    CPoint point(m_point);
    pWnd->ScreenToClient(&point);
    LPARAM lParam = MAKEWPARAM(point.x, point.y);
    pWnd->PostMessage(WM_LBUTTONDOWN, 1, lParam);
    pWnd->PostMessage(WM_LBUTTONUP, 1, lParam);

    add(L"点击");
  }
  else if (nIDEvent == 2)
  {
    KillTimer(2);
    SetCursorPos(m_point.x, m_point.y);

    CWnd* pWnd = WindowFromPoint(m_point);
    CPoint point(m_point);
    pWnd->ScreenToClient(&point);
    LPARAM lParam = MAKEWPARAM(point.x, point.y);
    pWnd->PostMessage(WM_LBUTTONDOWN, 1, lParam);
    pWnd->PostMessage(WM_LBUTTONUP, 1, lParam);
  }

  CDialogEx::OnTimer(nIDEvent);
}


void CamsDlg::OnSize(UINT nType, int cx, int cy)
{
  CDialogEx::OnSize(nType, cx, cy);

  if (m_list.GetSafeHwnd())
  {
    m_list.MoveWindow(m_rect.left, m_rect.top,
      cx - m_rect.left - m_rect.right,
      cy - m_rect.top - m_rect.bottom);
  }
}
