#if !defined(AFX_MSGWND_H__1DC7047D_8675_4C80_B335_54F78F3BBD76__INCLUDED_)
#define AFX_MSGWND_H__1DC7047D_8675_4C80_B335_54F78F3BBD76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgWnd window

class CMsgWnd : public CWnd
{
// Construction
public:
	CMsgWnd();

// Attributes
protected:
    CBitmap m_Bitmap;
	BITMAP bmBitmap;
	BOOL m_bFlag;
	BOOL m_bSetPopTimer;
	BOOL m_bSetCloseTimer;
	BOOL m_bSetDelayTimer;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgWnd)
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:	
	CString m_strMessage;
	CString m_strCaption;
	
	virtual ~CMsgWnd();
    void CreateMsgWindow();
	void SetPromptMessage(LPCTSTR lpszMsg);
	void SetPromptCaption(LPCTSTR lpszCaption);
	void StartTimer();
	// Generated message map functions
protected:
	//{{AFX_MSG(CMsgWnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGWND_H__1DC7047D_8675_4C80_B335_54F78F3BBD76__INCLUDED_)
