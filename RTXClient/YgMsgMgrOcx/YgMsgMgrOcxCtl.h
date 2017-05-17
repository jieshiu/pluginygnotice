#if !defined(AFX_YGMSGMGROCXCTL_H__F4EE26A7_486B_4AE2_845B_85D19C2614C8__INCLUDED_)
#define AFX_YGMSGMGROCXCTL_H__F4EE26A7_486B_4AE2_845B_85D19C2614C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <atlbase.h>
#include "YgMsgMgrDlg.h"
// YgMsgMgrOcxCtl.h : Declaration of the CYgMsgMgrOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl : See YgMsgMgrOcxCtl.cpp for implementation.

class CYgMsgMgrOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CYgMsgMgrOcxCtrl)

// Constructor
public:
	CYgMsgMgrOcxCtrl();

	DECLARE_INTERFACE_MAP()
		BEGIN_INTERFACE_PART(RTXPluginMsgMgr, IRTXPluginMsgMgr)
        STDMETHOD(InitCtrl)(IDispatch* RtxRoot);
	STDMETHOD(OnMsgMgrCmd)(int iCmd);
	END_INTERFACE_PART(RTXPluginMsgMgr)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYgMsgMgrOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CYgMsgMgrOcxCtrl();

	DECLARE_OLECREATE_EX(CYgMsgMgrOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CYgMsgMgrOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CYgMsgMgrOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CYgMsgMgrOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CYgMsgMgrOcxCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CYgMsgMgrOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CYgMsgMgrOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CYgMsgMgrOcxCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
	IRTXCRootPtr m_ptrRoot;
	CString m_strLocalAccount;
	CString m_strAccountPath;
	CYgMsgMgrDlg m_Mydlg;
	void FireDemoEvent(UINT iEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGMSGMGROCXCTL_H__F4EE26A7_486B_4AE2_845B_85D19C2614C8__INCLUDED)
