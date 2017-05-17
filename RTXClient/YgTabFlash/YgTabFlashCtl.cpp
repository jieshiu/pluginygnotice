// YgTabFlashCtl.cpp : Implementation of the CYgTabFlashCtrl ActiveX Control class.

#include "stdafx.h"
#include "YgTabFlash.h"
#include "YgTabFlashCtl.h"
#include "YgTabFlashPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CYgTabFlashCtrl, COleControl)

BEGIN_INTERFACE_MAP(CYgTabFlashCtrl, COleControl)
INTERFACE_PART(CYgTabFlashCtrl, IID_IRTXPluginFrameSize, RTXPluginFrameSize)
INTERFACE_PART(CYgTabFlashCtrl, IID_IRTXCPluginExtTabNotify, RTXCPluginExtTabNotify)
INTERFACE_PART(CYgTabFlashCtrl, IID_IRTXPluginTab, RTXPluginTab)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CYgTabFlashCtrl, COleControl)
	//{{AFX_MSG_MAP(CYgTabFlashCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CYgTabFlashCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CYgTabFlashCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CYgTabFlashCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CYgTabFlashCtrl, COleControl)
	//{{AFX_EVENT_MAP(CYgTabFlashCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CYgTabFlashCtrl, 1)
	PROPPAGEID(CYgTabFlashPropPage::guid)
END_PROPPAGEIDS(CYgTabFlashCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CYgTabFlashCtrl, "YGTABFLASH.YgTabFlashCtrl.1",
	0x2866b93d, 0xef7b, 0x4c1a, 0x8e, 0, 0x4d, 0x62, 0x6f, 0x32, 0x3, 0xf8)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CYgTabFlashCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DYgTabFlash =
		{ 0xdf1a4646, 0xbb8e, 0x49cb, { 0xad, 0xe0, 0x9, 0xf9, 0x79, 0x25, 0xef, 0x18 } };
const IID BASED_CODE IID_DYgTabFlashEvents =
		{ 0x825e61a, 0xbb46, 0x45d3, { 0x8d, 0x94, 0xd, 0xe1, 0xbb, 0xaf, 0x41, 0xa9 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwYgTabFlashOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CYgTabFlashCtrl, IDS_YGTABFLASH, _dwYgTabFlashOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::CYgTabFlashCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CYgTabFlashCtrl

BOOL CYgTabFlashCtrl::CYgTabFlashCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_YGTABFLASH,
			IDB_YGTABFLASH,
			afxRegApartmentThreading,
			_dwYgTabFlashOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::CYgTabFlashCtrl - Constructor

CYgTabFlashCtrl::CYgTabFlashCtrl()
{
	InitializeIIDs(&IID_DYgTabFlash, &IID_DYgTabFlashEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::~CYgTabFlashCtrl - Destructor

CYgTabFlashCtrl::~CYgTabFlashCtrl()
{
	// TODO: Cleanup your control's instance data here.
	//// 一定需要在合适的时机UnhookEvent下事件！
	try
	{	
		m_EventSinkModuleEvent.UnhookEvent(evt_OnModuleEvent, this, &CYgTabFlashCtrl::OnModuleEvent);
		VERIFY(m_EventSinkModuleEvent.Unadvise());
	}
	catch (...) {
	}

}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::OnDraw - Drawing function

void CYgTabFlashCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::DoPropExchange - Persistence support

void CYgTabFlashCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::OnResetState - Reset control to default state

void CYgTabFlashCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	//_trace(_T("YgTabFlash:OnResetState"));
	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl::AboutBox - Display an "About" box to the user

void CYgTabFlashCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_YGTABFLASH);
	_trace(_T("YgTabFlash:AboutBox"));
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashCtrl message handlers

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXPluginFrameSize::AddRef()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginFrameSize)
	//_trace(_T("YgTabFlash:XRTXPluginFrameSize::AddRef"));
		return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXPluginFrameSize::Release()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginFrameSize)
		//_trace(_T("YgTabFlash:XRTXPluginFrameSize::Release"));
		return pThis->ExternalRelease();
}

STDMETHODIMP CYgTabFlashCtrl::XRTXPluginFrameSize::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginFrameSize)
		_trace(_T("YgTabFlash:XRTXPluginFrameSize::QueryInterface"));
		return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CYgTabFlashCtrl::XRTXPluginFrameSize::GetCustomSize(long* x, long* y)
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginFrameSize)
    *x = 191;
	*y = 362;
	_trace(_T("YgTabFlash:XRTXPluginFrameSize::GetCustomSize"));
	return E_FAIL; //这里返回E_FAIL,表示ocx窗体可以随RTX窗体大小变化
}

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXCPluginExtTabNotify::AddRef()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXCPluginExtTabNotify)
		//_trace(_T("YgTabFlash:XRTXCPluginExtTabNotify::AddRef"));
		return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXCPluginExtTabNotify::Release()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXCPluginExtTabNotify)
		//_trace(_T("YgTabFlash:XRTXCPluginExtTabNotify::Release"));
		return pThis->ExternalRelease();
}


STDMETHODIMP CYgTabFlashCtrl::XRTXCPluginExtTabNotify::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXCPluginExtTabNotify)
		_trace(_T("YgTabFlash:XRTXCPluginExtTabNotify::QueryInterface"));
		return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CYgTabFlashCtrl::XRTXCPluginExtTabNotify::EnterExtTab()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXCPluginExtTabNotify)
_trace(_T("YgTabFlash:XRTXCPluginExtTabNotify::EnterExtTab"));

		return pThis->EnterExtTab();
}


STDMETHODIMP CYgTabFlashCtrl::XRTXCPluginExtTabNotify::LeaveExtTab()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXCPluginExtTabNotify)
		_trace(_T("YgTabFlash:XRTXCPluginExtTabNotify::LeaveExtTab"));
		return pThis->LeaveExtTab();
}

HRESULT CYgTabFlashCtrl::EnterExtTab()
{
	IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();	
    	ptrData->SetString(_bstr_t(_T("NotifyContent")), _bstr_t(_T("收到 EnterExtTab通知")));
	VARIANT varRet;
	IRTXCEventCenterPtr ptrEventCtr ;
	m_ptrRoot->get_RTXCEventCenter(&ptrEventCtr);
	varRet = ptrEventCtr->FireModuleEvent(ENTER_TAB_EVENT, m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE],ptrData);	
	_trace(_T("YgTabFlash:CYgTabFlashCtrl::EnterExtTab"));

	return S_OK;
	
}

HRESULT CYgTabFlashCtrl::LeaveExtTab()
{
	IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();
	ptrData->SetString(_bstr_t(_T("NotifyContent")), _bstr_t(_T("收到 LeaveExtTabb通知")));
	VARIANT varRet;
	IRTXCEventCenterPtr ptrEventCtr ;
	m_ptrRoot->get_RTXCEventCenter(&ptrEventCtr);
	varRet = ptrEventCtr->FireModuleEvent(LEAVE_TAB_EVENT, m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE],ptrData);	
	_trace(_T("YgTabFlash:CYgTabFlashCtrl::LeaveExtTab"));
	return S_OK;
	
}

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXPluginTab::AddRef()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginTab)
		//_trace(_T("YgTabFlash:XRTXPluginTab::AddRef"));
		return pThis->ExternalAddRef();
}

STDMETHODIMP CYgTabFlashCtrl::XRTXPluginTab::InitCtrl( IDispatch* RtxRoot)
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginTab)
		pThis->m_ptrRoot = (IRTXCRoot* )RtxRoot;
	_trace(_T("YgTabFlash:InitCtrl,m_ptrRoot[%x]"),RtxRoot);
	if (pThis->m_pDialog) {
		pThis->m_pDialog->Init (pThis->m_ptrRoot);	//把RTXRoot指针传给m_pDialog
	}

	pThis->SetTimer(_RTXC_LOAD_MODULE_TIMER,1000, NULL);
	return S_OK;
}

STDMETHODIMP_(ULONG)CYgTabFlashCtrl::XRTXPluginTab::Release()
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginTab)
		//_trace(_T("YgTabFlash:XRTXPluginTab::Release"));
		return pThis->ExternalRelease();
}

STDMETHODIMP CYgTabFlashCtrl::XRTXPluginTab::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CYgTabFlashCtrl, RTXPluginTab)
		_trace(_T("YgTabFlash:XRTXPluginTab::QueryInterface"));
		return pThis->ExternalQueryInterface(&iid, ppvObj);
}


void CYgTabFlashCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnLButtonDown(nFlags, point);
}

BOOL CYgTabFlashCtrl::LoadEventModule()
{
	try
	{	
		if (m_pDialog) 
		{
			m_pDialog->SetRTXRight();	
		}
		
		/// 查询EventModule插件是否被RTX加载
		//CComQIPtr<IRTXCModule> ptrRTXCModule = m_ptrRoot->GetModule(RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE);
		IRTXCModulePtr ptrRTXCModule = m_ptrRoot->GetModule(RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE);
		if (ptrRTXCModule)
		{
			
			/// 如果加载成功了,就通过OnInvoke这个方法来获取事件接口指针
			COleVariant varResult;
			if (FAILED(ptrRTXCModule->OnInvoke(_variant_t(_T("")), COleVariant((long)RTX_EVENT_GET_INTERFACE), _variant_t(_T("")), &varResult)))
			{
				ASSERT(FALSE);
				return FALSE;
			}
			
			if (varResult.vt == VT_DISPATCH)
			{
				m_ptrEvent = varResult.pdispVal;
				
				/// 钩住OnEventModule事件
				m_EventSinkModuleEvent.HookEvent(evt_OnModuleEvent, this, &CYgTabFlashCtrl::OnModuleEvent);
				VERIFY(m_EventSinkModuleEvent.Advise(m_ptrEvent));
				
				/// AfxMessageBox(_T("找到RTXC evt_OnModuleEvent 插事件！"));
				
				return TRUE;
			}		
		}		
	}
	catch (...) 
	{
		/// 错误处理~~
	}
	
	return FALSE;
}

void CYgTabFlashCtrl::OnModuleEvent(BSTR bstrdata)
{	
	_trace(_T("YgTabFlash:OnModuleEvent,bstrdata[%s]"),bstrdata);
	CString strReceive=LPCTSTR(bstrdata);
	CString csTemp;
	AfxExtractSubString(csTemp, (LPCTSTR)strReceive, 0, '|'); // 得到 NOTICE或TALK
	if(csTemp == "NOTICE")
	{
		CString csReceiver,csNotice,csLevel;
		AfxExtractSubString(csReceiver, (LPCTSTR)strReceive, 1, '|'); 
		AfxExtractSubString(csLevel, (LPCTSTR)strReceive, 2, '|'); 
		AfxExtractSubString(csNotice, (LPCTSTR)strReceive, 3, '|'); 
		m_pDialog->OnReceiveNotice(csReceiver,csNotice,csLevel);
	}
	else if(csTemp == "TALK")
	{
		CString csTalk;
		AfxExtractSubString(csTalk, (LPCTSTR)strReceive, 1, '|'); 
		m_pDialog->OnReceiveTalk(csTalk);
	}
	else if(csTemp == "RECEIVER")
	{
		CString csReceiver;
		AfxExtractSubString(csReceiver, (LPCTSTR)strReceive, 1, '|'); 
		m_pDialog->OnSetReceiver(csReceiver);
	}
	
}

void CYgTabFlashCtrl::OnTimer(UINT nIDEvent) 
{
	/// 每隔一定的事件去查询RTX中是否加载了Corp插件
	/// 由于OCX是先加载到RTX中,所以需要OCX加载成功之后,去查询插件是否被加载
	try
	{
		if (_RTXC_LOAD_MODULE_TIMER == nIDEvent)
		{
			if (LoadEventModule())
			{
				KillTimer(_RTXC_LOAD_MODULE_TIMER);
				
				/// AfxMessageBox(_T("找到RTXC Event 插件！"));
			}
		}
	}
	catch(...)
	{
		/// 错误处理~~
	}

	COleControl::OnTimer(nIDEvent);
}


int CYgTabFlashCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pDialog = new CYgNoticeDlg();
	//Check if new succeeded and we got a valid pointer to a dialog object
	if(m_pDialog != NULL)
	{
		BOOL ret = m_pDialog->Create(IDD_FORMVIEW,this);
		if(!ret)   //Create failed.
			AfxMessageBox(_T("Error creating Dialog"));
		m_pDialog->ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox(_T("Error Creating Dialog Object"));

	return 0;
}

void CYgTabFlashCtrl::OnSize(UINT nType, int cx, int cy) 
{
	if (m_pDialog)
	{
		m_pDialog->MoveWindow(0, 0, cx, cy);
	}

	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
