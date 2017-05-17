#pragma once

// PlugInYgNoticeModule.h : header file
//
#include "RTXEvent.h"
/////////////////////////////////////////////////////////////////////////////
// CPlugInYgNoticeModule command target

class CPlugInYgNoticeModule : public CCmdTarget
{
	DECLARE_DYNCREATE(CPlugInYgNoticeModule)
	DECLARE_EVENT_RECEIVER(CPlugInYgNoticeModule)

	CPlugInYgNoticeModule();           // protected constructor used by dynamic creation

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlugInYgNoticeModule)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlugInYgNoticeModule();

	BEGIN_DUAL_INTERFACE_PART(MenuSink, IRTXCUICommand)
		STDMETHOD(OnInvoke)( enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter );
	STDMETHOD(OnQueryState) (enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter,
		BSTR * bstrText,
		enum RTXC_UI_ITEM_STATE * State );
	
	END_DUAL_INTERFACE_PART(MenuSink)

	//IRTXPluginHandler
	BEGIN_INTERFACE_PART(RTXPluginHandler, IRTXPluginHandler)
		STDMETHOD(OnEvent)(BSTR id ,IDispatch* pData, VARIANT* pRet);
	END_INTERFACE_PART(RTXPluginHandler)

	// Generated message map functions
	//{{AFX_MSG(CPlugInYgNoticeModule)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	BEGIN_DUAL_INTERFACE_PART(RTXCModule, IRTXCPlugin)
		STDMETHOD(get_Identifier)(BSTR *pVal)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
				
			return pThis->get_Identifier(pVal);
		}

		STDMETHOD(get_Name)(BSTR *pVal)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
				
			return pThis->get_Name(pVal);
		}

		STDMETHOD(get_ModuleSite)(IDispatch* *pVal)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
		
			return pThis->get_ModuleSite(pVal);
		}

		STDMETHOD(OnLoad)(IDispatch* RTXCModuleSite)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
			
			return pThis->OnLoad(RTXCModuleSite);
		}

		STDMETHOD(OnAccountChange)()
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
				
			return pThis->OnAccountChange();
		}
		
		STDMETHOD(OnInvoke)(VARIANT Receiver, VARIANT Parameter, VARIANT Extra, VARIANT* Result)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
				
			return pThis->OnInvoke(Receiver, Parameter, Extra, Result);
		}
		
		STDMETHOD(OnUnload)(enum RTXC_MODULE_UNLOAD_REASON Reason)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)
				
			return pThis->OnUnload(Reason);
		}

		STDMETHOD(get_Info)(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal)
		{
			METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXCModule)

			return pThis->get_Info(Field, pVal);
		}
	END_DUAL_INTERFACE_PART(RTXCModule)	
	
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CPlugInYgNoticeModule)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPlugInYgNoticeModule)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	IRTXCRootPtr m_ptrRoot;
	IRTXCModuleSitePtr m_ptrModuleSite;

    IActionMgrPtr m_ptrActionMgr;
	IRTXCMenuPtr m_ptrMenu;
	ITabBaseMgr* m_pTabBaseMgr;
	CEventSinkActionMgr m_EventSinkActionMgr;

	long m_lEnterCookie;
	long m_lLeaveCookie;
	long m_lCookie;



	IRTXCPresencePtr m_ptrPresence;
	IRTXCRTXBuddyManagerPtr m_ptrRTXBuddyManager;
	IRTXCRTXGroupManagerPtr m_ptrRTXGroupManager;
	IRTXCMFCSupportPtr m_ptrMFCSupport;

	CRTXCEventSinkRoot m_RootEventSink;

	void OnLoginResult(RTXC_LOGIN_RESULT Result);

	CRTXCEventSinkPresence m_PresenceEventSink;

	void OnPresenceChange(BSTR Account, RTX_PRESENCE RTXPresence);

	CRTXCEventSinkModuleSite m_ModuleSiteEventSink;

	void OnDataReceived(LPCTSTR Key);
	void OnViewData(LPCTSTR Key);
	void OnSendDataResult(RTXC_MODULE_SEND_DATA_RESULT Result, const VARIANT* Extra);
	
	CRTXCEventSinkRTXBuddyManager m_RTXBuddyManagerEventSink;

	void OnBuddyProfileChange(IRTXCRTXBuddy* RTXCRTXBuddy);

	CRTXCEventSinkRTXGroupManager m_RTXGroupManagerEventSink;

	void OnGroupChange(IRTXCRTXGroup* RTXCRTXGroup);
	void OnGroupAdd(IRTXCRTXGroup* RTXCRTXGroup);
	void OnGroupRemove(IRTXCRTXGroup* RTXCRTXGroup);
	void OnBuddyAdd(IRTXCRTXGroup* RTXCRTXGroup, IRTXCRTXBuddy* RTXCRTXBuddy);
	void OnBuddyRemove(IRTXCRTXGroup* RTXCRTXGroup, IRTXCRTXBuddy* RTXCRTXBuddy);

	CRTXCEventSinkMFCSupport m_MFCSupportEventSink;	

	void OnPreTranslateMessage(long MSGPointer, VARIANT_BOOL* Handled);
	void OnIdle(long Count);

	HRESULT get_Identifier(BSTR* pVal);
	HRESULT get_Name(BSTR* pVal);

	HRESULT get_ModuleSite(IDispatch* *pVal);

	HRESULT OnLoad(IDispatch* RTXCModuleSite);
	
	HRESULT OnAccountChange();

	HRESULT OnInvoke(VARIANT Receiver, VARIANT Parameter, VARIANT Extra, VARIANT* Result);
	
	HRESULT OnUnload(enum RTXC_MODULE_UNLOAD_REASON Reason);

	HRESULT get_Info(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal);

	void OnActionDel(LPCTSTR lpszGroup, const VARIANT * pVarID, const VARIANT * pVarExtraInfo);
	void OnActionInvoked(LPCTSTR lpszGroup, const VARIANT * pVarID, const VARIANT * pVarExtraInfo);
	
	void InitAction();
	void NoticeAction(BOOL bShow);
	HRESULT MenuOnInvoke(enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter);
	CString BuildGUID();

	CString GetStructUser(VARIANT Parameter);
	CString GetIMThirdUser(VARIANT Parameter);

	CString GetStructUserToMenu(VARIANT Parameter);
	CString GetIMThirdUserToMenu(VARIANT Parameter);

	CComObject<CRTXEvent>*	m_ptrEvent;
	CComObject<CRTXEvent>* _CreateEvent();

	long m_lNoticeNotReadCount;
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void ReportError(int nError);
	HINSTANCE GotoURL(LPCTSTR url, int showcmd);
	void OpenURL(LPCTSTR url);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
