#if !defined(AFX_YGMSGMGRDLG_H__D944877B_A0E8_4764_B2B8_B600F3F9E18F__INCLUDED_)
#define AFX_YGMSGMGRDLG_H__D944877B_A0E8_4764_B2B8_B600F3F9E18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YgMsgMgrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrDlg dialog
class CYgMsgMgrOcxCtrl;

class CYgMsgMgrDlg : public CDialog
{
// Construction
public:
	CYgMsgMgrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYgMsgMgrDlg)
	enum { IDD = IDD_DLG_MSGMGR };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYgMsgMgrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CYgMsgMgrDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CYgMsgMgrOcxCtrl* m_pYgMsgCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGMSGMGRDLG_H__D944877B_A0E8_4764_B2B8_B600F3F9E18F__INCLUDED_)
