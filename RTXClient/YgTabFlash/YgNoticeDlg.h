#if !defined(AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_)
#define AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YgNoticeDlg.h : header file
//
#include "TalkDlg.h"
#include "XPButton.h"
#include "ToolTipWnd.h"
#include "SAStatusLog.h"
#include "HyperLink.h"	
#include "BtnST.h"	

/////////////////////////////////////////////////////////////////////////////
// CYgNoticeDlg dialog

class CYgNoticeDlg : public CDialog
{
// Construction
public:
	CYgNoticeDlg(CWnd* pParent = NULL);   // standard constructor

	void Init(IRTXCRootPtr pModule);
	void OnReceiveNotice(LPCTSTR strReceiver,LPCTSTR strNotice,LPCTSTR strLevel);
	void OnReceiveTalk(LPCTSTR strTalk);
	void OnSetReceiver(LPCTSTR strReceiver);
	void SendNoticeReadEven();
	void SendTalk(LPCTSTR strTalk,LPCTSTR csTime);
	void SetRTXRight();
	void OnViewTips(CString key);

// Dialog Data
	//{{AFX_DATA(CYgNoticeDlg)
	enum { IDD = IDD_FORMVIEW };
	CXPButton	m_talk;
	CXPButton	m_sendnotice;
	CListCtrl	m_list;
	CString	m_Notice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYgNoticeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTalkDlg* GetTalkDialog();
	
	// Generated message map functions
	//{{AFX_MSG(CYgNoticeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnBtnTalk();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CHyperLink m_OALink1;
	CHyperLink m_OALink2;

public:
	IRTXCModuleSitePtr m_ptrModule;
	IRTXCRootPtr m_ptrRoot;
	//IRTXCCRight m_ptrRight;
	BOOL m_bAdmin;
	CTalkDlg *m_pDlg;
	long m_lNoticeNotReadCount;
	//CToolTipWnd m_bttWnd;
	CSAStatusLog m_statusLog;
	CString m_csLocalAccount;
	CString m_csAccountPath;
	CString m_csReceiver;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_)
