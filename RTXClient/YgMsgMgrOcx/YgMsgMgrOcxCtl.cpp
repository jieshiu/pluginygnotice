// YgMsgMgrOcxCtl.cpp : Implementation of the CYgMsgMgrOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "YgMsgMgrOcx.h"
#include "YgMsgMgrOcxCtl.h"
#include "YgMsgMgrOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CYgMsgMgrOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CYgMsgMgrOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CYgMsgMgrOcxCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CYgMsgMgrOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CYgMsgMgrOcxCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CYgMsgMgrOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CYgMsgMgrOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CYgMsgMgrOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()

BEGIN_INTERFACE_MAP(CYgMsgMgrOcxCtrl, COleControl)
INTERFACE_PART(CYgMsgMgrOcxCtrl, IID_IRTXPluginMsgMgr, RTXPluginMsgMgr)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CYgMsgMgrOcxCtrl, 1)
	PROPPAGEID(CYgMsgMgrOcxPropPage::guid)
END_PROPPAGEIDS(CYgMsgMgrOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CYgMsgMgrOcxCtrl, "YGMSGMGROCX.YgMsgMgrOcxCtrl.1",
	0x89e5e583, 0x202b, 0x43a5, 0x86, 0x39, 0x10, 0x1e, 0xa5, 0x84, 0x73, 0xbb)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CYgMsgMgrOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DYgMsgMgrOcx =
		{ 0x423b95a, 0x2f9d, 0x4824, { 0x81, 0x44, 0x74, 0xc6, 0x4a, 0x71, 0x56, 0xf5 } };
const IID BASED_CODE IID_DYgMsgMgrOcxEvents =
		{ 0x3731f508, 0x82e2, 0x4354, { 0xaf, 0x23, 0xce, 0x57, 0x45, 0x47, 0xab, 0x38 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwYgMsgMgrOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CYgMsgMgrOcxCtrl, IDS_YGMSGMGROCX, _dwYgMsgMgrOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::CYgMsgMgrOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CYgMsgMgrOcxCtrl

BOOL CYgMsgMgrOcxCtrl::CYgMsgMgrOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_YGMSGMGROCX,
			IDB_YGMSGMGROCX,
			afxRegApartmentThreading,
			_dwYgMsgMgrOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::CYgMsgMgrOcxCtrl - Constructor

CYgMsgMgrOcxCtrl::CYgMsgMgrOcxCtrl()
{
	InitializeIIDs(&IID_DYgMsgMgrOcx, &IID_DYgMsgMgrOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::~CYgMsgMgrOcxCtrl - Destructor

CYgMsgMgrOcxCtrl::~CYgMsgMgrOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::OnDraw - Drawing function

void CYgMsgMgrOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
	m_Mydlg.MoveWindow(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::DoPropExchange - Persistence support

void CYgMsgMgrOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::OnResetState - Reset control to default state

void CYgMsgMgrOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl::AboutBox - Display an "About" box to the user

void CYgMsgMgrOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_YGMSGMGROCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxCtrl message handlers
STDMETHODIMP_(ULONG) CYgMsgMgrOcxCtrl::XRTXPluginMsgMgr::AddRef()
{
	 METHOD_PROLOGUE(CYgMsgMgrOcxCtrl, RTXPluginMsgMgr)
	 return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CYgMsgMgrOcxCtrl::XRTXPluginMsgMgr::Release()
{
	 METHOD_PROLOGUE(CYgMsgMgrOcxCtrl, RTXPluginMsgMgr)
	 return pThis->ExternalRelease();
}

STDMETHODIMP CYgMsgMgrOcxCtrl::XRTXPluginMsgMgr::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CYgMsgMgrOcxCtrl, RTXPluginMsgMgr)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}
STDMETHODIMP CYgMsgMgrOcxCtrl::XRTXPluginMsgMgr::InitCtrl(IDispatch* RtxRoot)
{
	METHOD_PROLOGUE(CYgMsgMgrOcxCtrl, RTXPluginMsgMgr)
    pThis->m_ptrRoot = (IRTXCRoot* )RtxRoot;
	_trace(_T("YgMsgMgrOcx:InitCtrl,m_ptrRoot[%x]"),RtxRoot);

		    // 得到本地用户名	
        pThis->m_strLocalAccount = (LPCTSTR)pThis->m_ptrRoot->Account; 
		//得到用户个人文件夹目录		
		HRESULT hr = pThis->m_ptrRoot->get_FileListPath((BSTR *)&pThis->m_strAccountPath);
		if(SUCCEEDED(hr))
		{
			_trace(_T("YgMsgMgrOcx:InitCtrl,AccountPath[%s]"),pThis->m_strAccountPath);
		}

	return S_OK;
}
STDMETHODIMP CYgMsgMgrOcxCtrl::XRTXPluginMsgMgr::OnMsgMgrCmd(int iCmd)
{
	switch(iCmd) 
	{
	case 0:
		::MessageBox(NULL, _T("您按了导出铵钮！"),_T("ActiveX响应"), MB_OK);
		break;
	case 1:
		::MessageBox(NULL, _T("您按了删除铵钮！"),_T("ActiveX响应"), MB_OK);
		break;
	case 2:
		::MessageBox(NULL, _T("您按了会话铵钮！"),_T("ActiveX响应"), MB_OK);
		break;
	case 3:
		::MessageBox(NULL, _T("您按了删新铵钮！"),_T("ActiveX响应"), MB_OK);
		break;
    case 4:
        ::MessageBox(NULL, _T("您按了邮寄铵钮！"),_T("ActiveX响应"), MB_OK);
		break;
	default:
		break;
	}
	return S_OK;
}

void CYgMsgMgrOcxCtrl::FireDemoEvent(UINT iEvent)
{
	BoundPropertyChanged(iEvent);
}

int CYgMsgMgrOcxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Mydlg.Create(CYgMsgMgrDlg::IDD, this);
	m_Mydlg.ShowWindow(TRUE);
	
	return 0;
}
