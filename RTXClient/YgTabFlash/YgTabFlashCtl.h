#if !defined(AFX_YGTABFLASHCTL_H__1AA1E6FB_1473_47B8_A4A5_D629484AFA8D__INCLUDED_)
#define AFX_YGTABFLASHCTL_H__1AA1E6FB_1473_47B8_A4A5_D629484AFA8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>
// YgTabFlashCtl.h : Declaration of the CYgTabFlashCtrl ActiveX Control class.
#include "YgNoticeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl : See YgTabFlashCtl.cpp for implementation.

class CYgTabFlashCtrl : public COleControl
{
	DECLARE_DYNCREATE(CYgTabFlashCtrl)

	DECLARE_EVENT_RECEIVER(CYgTabFlashCtrl)

// Constructor
public:
	CYgTabFlashCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYgTabFlashCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CYgTabFlashCtrl();

	DECLARE_INTERFACE_MAP()
		BEGIN_INTERFACE_PART(RTXPluginFrameSize, IRTXPluginFrameSize)
		STDMETHOD(GetCustomSize)(long* x, long* y);
	END_INTERFACE_PART(RTXPluginFrameSize)

		BEGIN_INTERFACE_PART(RTXCPluginExtTabNotify, IRTXCPluginExtTabNotify)
		STDMETHOD(EnterExtTab)();
		STDMETHOD(LeaveExtTab)();
	END_INTERFACE_PART(RTXCPluginExtTabNotify)
		
		BEGIN_INTERFACE_PART(RTXPluginTab, IRTXPluginTab)
		STDMETHOD(InitCtrl)(/*[in]*/ IDispatch* RtxRoot);
	END_INTERFACE_PART(RTXPluginTab)

	DECLARE_OLECREATE_EX(CYgTabFlashCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CYgTabFlashCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CYgTabFlashCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CYgTabFlashCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CYgTabFlashCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CYgTabFlashCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CYgTabFlashCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CYgTabFlashCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};

public:
	IRTXCRootPtr m_ptrRoot;
	HRESULT LeaveExtTab();
	HRESULT EnterExtTab();

	void OnModuleEvent(BSTR bstrdata);	//事件应响方法
	BOOL LoadEventModule();	//获取插件Module,并钩住事件

private:	
	CYgNoticeDlg* m_pDialog;
	CComQIPtr<IRTXEvent>	m_ptrEvent;
	CEventSinkRTXEvent		m_EventSinkModuleEvent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGTABFLASHCTL_H__1AA1E6FB_1473_47B8_A4A5_D629484AFA8D__INCLUDED)
