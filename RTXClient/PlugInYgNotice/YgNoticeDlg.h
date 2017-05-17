#if !defined(AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_)
#define AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YgNoticeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYgNoticeDlg dialog

class CYgNoticeDlg : public CDialog
{
// Construction
public:
	CYgNoticeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYgNoticeDlg)
	enum { IDD = IDD_FORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYgNoticeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYgNoticeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGNOTICEDLG_H__7BBA619E_0C5E_4FF2_B54A_E689D24D0366__INCLUDED_)
