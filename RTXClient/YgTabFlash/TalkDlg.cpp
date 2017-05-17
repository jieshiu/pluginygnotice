// TalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YgTabFlash.h"
#include "TalkDlg.h"
#include "YgNoticeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog


CTalkDlg::CTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTalkDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_parentWnd=pParent;
	m_csLocalAccount=_T("");
}


void CTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalkDlg)
	DDX_Control(pDX, IDC_RICHEDIT1, m_RichEditShow);
	DDX_Control(pDX, IDC_RICHEDIT2, m_richInput);
	DDX_Control(pDX, IDC_BTNSEND, m_btnSendTalk);
	DDX_Control(pDX, IDC_BTNRECODE, m_btnRecode);
	DDX_Control(pDX, IDC_BTNCLOSE, m_btnClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTalkDlg, CDialog)
	//{{AFX_MSG_MAP(CTalkDlg)	
	ON_BN_CLICKED(IDC_BTNSEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTNCLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg message handlers

void CTalkDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CTalkDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTalkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_strDisplayName="СW";
	m_richInput.SetFocus();
	CString strTitle;
	strTitle.Format(_T("�� %s �ĶԻ�"), m_strDisplayName);
	SetWindowText(strTitle);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTalkDlg::SetLocalAccount(CString csAccount)
{
	m_csLocalAccount=csAccount;
}

void CTalkDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}

BOOL CTalkDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			if(GetKeyState(VK_CONTROL)<0)
			{
				OnBtnSend();
				return TRUE;
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CTalkDlg::_InsertText(LPCTSTR lpszText)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects = (unsigned long)~(CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor = RGB(1, 144, 223);

	int nStartPos = m_RichEditShow.GetWindowTextLength();
	m_RichEditShow.SetSel(nStartPos, nStartPos);

	m_RichEditShow.ReplaceSel(lpszText);

	int nEndPos = m_RichEditShow.GetWindowTextLength();

	m_RichEditShow.SetSel(nStartPos, nEndPos);
	m_RichEditShow.SetSelectionCharFormat(cf);

	m_RichEditShow.SetSel(nEndPos, nEndPos);
}

// RichEdi д�뷢��ʱ��
void CTalkDlg::_InsertHeader(LPCTSTR lpszInfo)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects = (unsigned long)~(CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor = RGB(102, 0, 237);

	int nStartPos = m_RichEditShow.GetWindowTextLength();
	m_RichEditShow.SetSel(nStartPos, nStartPos);

	m_RichEditShow.ReplaceSel(lpszInfo);

	int nEndPos = m_RichEditShow.GetWindowTextLength();
	m_RichEditShow.SetSel(nStartPos, nEndPos);

	m_RichEditShow.SetSelectionCharFormat(cf);

	m_RichEditShow.SetSel(nEndPos, nEndPos);
}

void CTalkDlg::AddRecvText(LPCTSTR msg,LPCTSTR msgtime)
{
	// ��Ϣ ������ �� ����ʱ��	
	CString cstmp=msgtime;
	CString csStartTime=_T("СW(...) ");
	csStartTime+=cstmp;
	csStartTime+=CString(_T("\r\n"));
	// RichEdi д�뷢��ʱ��
	//_InsertHeader(csStartTime);
	m_RichEditShow.SetSel(-1, -1);
	m_RichEditShow.ReplaceSel((LPCTSTR)csStartTime);

	CString strMsg = msg;
	strMsg += _T("\r\n");
	
	//_InsertText(strMsg);
	m_RichEditShow.SetSel(-1, -1);
	m_RichEditShow.ReplaceSel((LPCTSTR)strMsg);

	m_RichEditShow.HideSelection(FALSE, FALSE);
	// �Թ��������������һ��
	//m_RichEditShow.LineScroll(1);
	m_RichEditShow.PostMessage(WM_VSCROLL, SB_BOTTOM,0);
}

void CTalkDlg::AddSendText(LPCTSTR msg)
{
	CTime m_StartTime1 = CTime::GetCurrentTime();
	
	CString csStartTime;
	// ��Ϣ ������ �� ����ʱ��
	CString csSendTime=m_StartTime1.Format(_T("%Y-%m-%d %H:%M:%S"));
	csStartTime.Format(_T("%s %s\r\n"), m_csLocalAccount,csSendTime );
	//_InsertHeader(csStartTime);
	m_RichEditShow.SetSel(-1, -1);
	m_RichEditShow.ReplaceSel((LPCTSTR)csStartTime);

	if(m_parentWnd != NULL)
	{
		((CYgNoticeDlg*)m_parentWnd)->SendTalk(msg,csSendTime);
	}

	CString strMsg = msg;
	strMsg += _T("\r\n");

	//_InsertText(strMsg);
	m_RichEditShow.SetSel(-1, -1);
	m_RichEditShow.ReplaceSel((LPCTSTR)strMsg);

	// �Թ��������������һ��
	//m_RichEditShow.LineScroll(1);
	m_RichEditShow.HideSelection(TRUE, FALSE);
	m_RichEditShow.PostMessage(WM_VSCROLL, SB_BOTTOM,0);	
}

void CTalkDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	CString strSend;
	
	m_richInput.GetWindowText(strSend);	//�ӽ����ȡ����
	
	// ����û�ʲôҲû���밴����,����ʾ����
	if (strSend.IsEmpty())
	{
		// ����Ҫ��Ҫ��ʾ����ֱ�ӷ���
		m_richInput.SetFocus();
		return;
	}

	//
	//����

	AddSendText((LPCTSTR)strSend);

	m_richInput.SetWindowText(_T(""));
	m_richInput.SetFocus();
}

void CTalkDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CTalkDlg::OnReceiveTalk(LPCTSTR msg,LPCTSTR msgtime)
{
	AddRecvText(msg,msgtime);
}
