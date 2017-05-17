#if !defined(AFX_TALKDLG_H__B649C121_1CF8_430E_B9E4_38C04B8E3342__INCLUDED_)
#define AFX_TALKDLG_H__B649C121_1CF8_430E_B9E4_38C04B8E3342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TalkDlg.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog

class CTalkDlg : public CDialog
{
// Construction
public:
	CTalkDlg(CWnd* pParent = NULL);   // standard constructor
	CString					m_strDisplayName;
	CString m_csLocalAccount;
	void OnReceiveTalk(LPCTSTR msg,LPCTSTR msgtime);
	void SetLocalAccount(CString csAccount);
// Dialog Data
	//{{AFX_DATA(CTalkDlg)
	enum { IDD = IDD_DLGTALK };
	CRichEditCtrl	m_RichEditShow;
	CRichEditCtrl	m_richInput;
	CXPButton	m_btnSendTalk;
	CXPButton	m_btnRecode;
	CXPButton	m_btnClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void _InsertText(LPCTSTR lpszText);
	void _InsertHeader(LPCTSTR lpszInfo);
	void AddRecvText(LPCTSTR msg,LPCTSTR msgtime);
	void AddSendText(LPCTSTR msg);
	CWnd* m_parentWnd;
	// Generated message map functions
	//{{AFX_MSG(CTalkDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKDLG_H__B649C121_1CF8_430E_B9E4_38C04B8E3342__INCLUDED_)
