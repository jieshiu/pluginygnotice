// PlugInYgNoticeModule.cpp : implementation file
//

#include "stdafx.h"
#include "PlugInYgNotice.h"
#include "PlugInYgNoticeModule.h"
#include "objbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlugInYgNoticeModule

IMPLEMENT_DYNCREATE(CPlugInYgNoticeModule, CCmdTarget)
DELEGATE_DUAL_INTERFACE(CPlugInYgNoticeModule, RTXCModule)
DELEGATE_DUAL_INTERFACE(CPlugInYgNoticeModule, MenuSink)

CPlugInYgNoticeModule::CPlugInYgNoticeModule()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	m_lNoticeNotReadCount=0;
	AfxOleLockApp();
}

CPlugInYgNoticeModule::~CPlugInYgNoticeModule()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CPlugInYgNoticeModule::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CPlugInYgNoticeModule, CCmdTarget)
	//{{AFX_MSG_MAP(CPlugInYgNoticeModule)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPlugInYgNoticeModule, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CPlugInYgNoticeModule)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CPlugInYgNoticeModule, CCmdTarget)
	INTERFACE_PART(CPlugInYgNoticeModule, IID_IRTXCModule, RTXCModule)
	INTERFACE_PART(CPlugInYgNoticeModule, IID_IRTXCPlugin, RTXCModule)
	INTERFACE_PART(CPlugInYgNoticeModule, IID_IRTXPluginHandler, RTXPluginHandler)	
END_INTERFACE_MAP()

// {31BCB913-6B09-476A-9E94-5E97EB997223}
IMPLEMENT_OLECREATE(CPlugInYgNoticeModule, "RTXC.PlugInYgNoticeModule", 
	0x31bcb913, 0x6b09, 0x476a, 0x9e, 0x94, 0x5e, 0x97, 0xeb, 0x99, 0x72, 0x23)

/////////////////////////////////////////////////////////////////////////////
// CPlugInYgNoticeModule message handlers

HRESULT CPlugInYgNoticeModule::get_Identifier(BSTR* pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
	
	*pVal = CString(RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE).AllocSysString();
	
	return S_OK;
}

HRESULT CPlugInYgNoticeModule::get_Name(BSTR* pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
	
	*pVal = CString(RTX_MODULE_NAME_PLUGINYGNOTICE).AllocSysString();
	
	return S_OK;
}

STDMETHODIMP_(ULONG) CPlugInYgNoticeModule::XRTXPluginHandler::AddRef()
{
	//得到嵌套类和自身之间的偏移
	METHOD_PROLOGUE_EX_(CPlugInYgNoticeModule, RTXPluginHandler)
		//pThis现在应该指向父类
		return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CPlugInYgNoticeModule::XRTXPluginHandler::Release()
{
	METHOD_PROLOGUE_EX_(CPlugInYgNoticeModule, RTXPluginHandler)
		return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CPlugInYgNoticeModule::XRTXPluginHandler::QueryInterface(
																	  REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CPlugInYgNoticeModule, RTXPluginHandler)
		return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);

}

HRESULT CPlugInYgNoticeModule::get_ModuleSite(IDispatch* *pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
				
	*pVal = (IDispatch*)m_ptrModuleSite;
	
	if (*pVal != NULL)
	{
		(*pVal)->AddRef();
		
		return S_OK;
	}
				
	return E_FAIL;
}

HRESULT CPlugInYgNoticeModule::OnLoad(IDispatch* RTXCModuleSite)
{
	RTX_CHECK_INVALIDARG_NULL(RTXCModuleSite);

	RTX_TRY
	{
		_trace(_T("PlugInYgNotice:OnLoad"));
		m_ptrModuleSite = RTXCModuleSite;
		m_ptrRoot = m_ptrModuleSite->RTXCRoot;

		m_RootEventSink.HookEvent(evt_OnLoginResult, this, &CPlugInYgNoticeModule::OnLoginResult);

		VERIFY(m_RootEventSink.Advise(m_ptrRoot));

		///////////////////////////////
		
        
		//添加主面板工具栏图标
        //Action
		CComQIPtr<IClientObjectsModule> pClientObjsModule = m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_CLIENT_OBJS];
		
		CComBSTR bstrAction( RTX_CLIENT_OBJECTS_IDENTIFIER_ACTIONMGR );
		HRESULT hr = pClientObjsModule->get_Object(bstrAction, (IDispatch ** )&m_ptrActionMgr);	
		if(SUCCEEDED(hr))
		{
			if (m_ptrRoot != NULL)
			{
				m_EventSinkActionMgr.HookEvent(evt_OnActionDel, this, &CPlugInYgNoticeModule::OnActionDel);
				m_EventSinkActionMgr.HookEvent(evt_OnActionInvoked, this, &CPlugInYgNoticeModule::OnActionInvoked);
				if (!m_EventSinkActionMgr.Advise(m_ptrActionMgr))
				{
					throw RTX_UNSPECIFIC_ERROR;
				}
			}
		}
		g_hPlugInYgNoticeModule = GetModuleHandle(_T("PlugInYgNotice.dll"));
		InitAction();
		
		//--------------------------------------//示范如何获得Action对象
		
		IActionCollectionPtr ptrActionCollection = m_ptrActionMgr->Actions[ACTION_GROUP_NAME_YOUCANDO_AREA];
		int nCount  = ptrActionCollection->Count;
		for( int i = 1 ; i <= nCount; i++)
		{
			long lPos = ptrActionCollection->Item[i]->Position;//示范如何获得Action对象

		}
		//-----------------------------------------

		pClientObjsModule->get_Object(RTX_CLIENT_OBJECTS_IDENTIFIER_MENU, (IDispatch** )&m_ptrMenu);
				IRTXCUICommand* pUICmd = dynamic_cast<IRTXCUICommand* >(&m_xMenuSink);
		/*
		CComPtr<IAppRoot> ptrAppRoot=NULL;
		//IAppRoot ptrAppRoot;
		REFIID iid1 = IID_IAppRoot;
		ExternalQueryInterface(&iid1,  (LPVOID*)&ptrAppRoot);

		if(ptrAppRoot != NULL)
		{
			CComPtr<IRTXCCRight> ptrRight=NULL;
			//IRTXCCRight ptrRight=NULL;			
			hr = ptrAppRoot->GetAppObject(_variant_t("RTXPlugin.CLientRightMgr"),(IDispatch **)&ptrRight);
			long bCanNotSendBroadcast=1;
			if(SUCCEEDED(hr))
			{			
				_variant_t lVal;
				ptrRight->GetGivenRightInfo(_bstr_t("RIGHT_INNER_SEND_BROADCAST_MSG"),&lVal);
				bCanNotSendBroadcast=lVal;
				if(bCanNotSendBroadcast == 0)
				{
						//"操作"菜单RTXC_UI_TYPE_MAINFRAME_ACTION
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_ORG_STRUCT_USER, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}
				}
			}		
		}*/

		CComQIPtr<IRTXCCRight> pRightModule = m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_RIGHT];
		if(pRightModule != NULL)
		{	
			_trace(_T("PlugInYgNotice::OnLoad:pRightModule:[%x]"),pRightModule);
			CString role;
			BSTR bstrText; 
			hr=pRightModule->GetClientRoleList(&bstrText);
			if(SUCCEEDED(hr))
			{
				role=bstrText;						
				int ret=role.Find(_T("管理员"));		
				if(ret != -1)
				{
					_trace(_T("PlugInYgNotice::OnLoad:GetClientRoleList-ret:[%d]"),ret);

					//添加常用联系人右键菜单,RTXC_UI_TYPE_MYCONTACTS_USERDEFINEDGROUP_USER为常用联系人
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_MYCONTACTS_USERDEFINEDGROUP_USER, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}

					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_ALL_CONTACTS_DISGROUP, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}

					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_RECENTCONTACT_DISGROUP, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}				

					//最近联系人RTXC_UI_TYPE_RECENTCONTACTS_SESSIONS_USER
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_RECENTCONTACTS_SESSIONS_USER, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}

					//
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_ORG_STRUCT_GROUP, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}

					//组织架构人员右键菜单RTXC_UI_TYPE_ORG_STRUCT_USER为组织架构人员
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_ORG_STRUCT_USER, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}

					//"操作"菜单RTXC_UI_TYPE_MAINFRAME_ACTION
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_MAINFRAME_ACTION, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}
					
					// 在IM 窗口添加第三方菜单
					if (FAILED(m_ptrMenu->AddItem(VARIANT_FALSE, -1, 
						RTXC_UI_TYPE_IM_THIRDPARTY, IDM_START_TAB_FLASH, pUICmd,
						_T("发送公告"), NULL, RTXC_MENU_ITEM_SEPARATOR_ABOVE_AND_BELOW,
						12, VARIANT_FALSE)))
					{
						throw RTX_UNSPECIFIC_ERROR;
					}
				}
				else
				{
					_trace(_T("PlugInYgNotice::OnLoad:ret = -1"));					
				}			
			}		
			else
			{
				_trace(_T("PlugInYgNotice::OnLoad:GetClientRoleList-fail"));				
			}
		}
		else
		{
			_trace(_T("PlugInYgNotice::OnLoad:pRightModule-NULL"));	
		}

			
				
		//挂接事件中心
		IRTXCEventCenterPtr ptrEventCtr = m_ptrRoot->RTXCEventCenter;
		CComPtr<IUnknown> ptrIUnkown ;
		REFIID iid = IID_IUnknown;
		ExternalQueryInterface(&iid,  (LPVOID*)&ptrIUnkown);		 
		
		CComPtr<IRTXCModule> ptrModule;
		REFIID iid2 = IID_IRTXCModule;
		ExternalQueryInterface(&iid2,  (LPVOID*)&ptrModule);
        m_lEnterCookie = ptrEventCtr->AddModuleEventSink(_bstr_t(ENTER_TAB_EVENT) , ptrIUnkown, FALSE, ptrModule);
		m_lLeaveCookie =  ptrEventCtr->AddModuleEventSink(_bstr_t(LEAVE_TAB_EVENT) , ptrIUnkown, FALSE, ptrModule);
		m_lCookie  = ptrEventCtr->AddModuleEventSink(_bstr_t(YGTEST_EVENT) , ptrIUnkown, FALSE, ptrModule);



        ///////////////////////////////////////////

		m_ptrPresence = m_ptrRoot->Presence;

		m_PresenceEventSink.HookEvent(evt_OnPresenceChange, this, &CPlugInYgNoticeModule::OnPresenceChange);

		VERIFY(m_PresenceEventSink.Advise(m_ptrPresence));

		m_ModuleSiteEventSink.HookEvent(evt_OnDataReceived, this, &CPlugInYgNoticeModule::OnDataReceived);
		m_ModuleSiteEventSink.HookEvent(evt_OnViewData, this, &CPlugInYgNoticeModule::OnViewData);
		m_ModuleSiteEventSink.HookEvent(evt_OnSendDataResult, this, &CPlugInYgNoticeModule::OnSendDataResult);
		
		VERIFY(m_ModuleSiteEventSink.Advise(m_ptrModuleSite));	

		m_ptrRTXBuddyManager = m_ptrRoot->RTXBuddyManager;
		
		m_RTXBuddyManagerEventSink.HookEvent(evt_OnBuddyProfileChange, this, &CPlugInYgNoticeModule::OnBuddyProfileChange);

		VERIFY(m_RTXBuddyManagerEventSink.Advise(m_ptrRTXBuddyManager));	

		m_ptrRTXGroupManager = m_ptrRoot->RTXGroupManager;

		m_RTXGroupManagerEventSink.HookEvent(evt_OnGroupChange, this, &CPlugInYgNoticeModule::OnGroupChange);
		m_RTXGroupManagerEventSink.HookEvent(evt_OnGroupAdd, this, &CPlugInYgNoticeModule::OnGroupAdd);
		m_RTXGroupManagerEventSink.HookEvent(evt_OnGroupRemove, this, &CPlugInYgNoticeModule::OnGroupRemove);
		m_RTXGroupManagerEventSink.HookEvent(evt_OnBuddyAdd, this, &CPlugInYgNoticeModule::OnBuddyAdd);
		m_RTXGroupManagerEventSink.HookEvent(evt_OnBuddyRemove, this, &CPlugInYgNoticeModule::OnBuddyRemove);

		VERIFY(m_RTXGroupManagerEventSink.Advise(m_ptrRTXGroupManager));	

		m_ptrMFCSupport = m_ptrRoot->MFCSupport;

		m_MFCSupportEventSink.HookEvent(evt_OnPreTranslateMessage, this, &CPlugInYgNoticeModule::OnPreTranslateMessage);
		m_MFCSupportEventSink.HookEvent(evt_OnIdle, this, &CPlugInYgNoticeModule::OnIdle);

		VERIFY(m_MFCSupportEventSink.Advise(m_ptrMFCSupport));

		m_ptrEvent = _CreateEvent();

		return S_OK;
	}
	RTX_CATCH_ALL(return E_FAIL)
}

void CPlugInYgNoticeModule::OnActionDel(LPCTSTR lpszGroup, const VARIANT * pVarID, const VARIANT * pVarExtraInfo)
{
	_trace(_T("PlugInYgNotice:OnActionDel"));
	if(CString(lpszGroup) == ACTION_GROUP_NAME_YOUCANDO_AREA)
	{
		ASSERT(pVarID->vt == VT_I4);
		switch(pVarID->lVal)
		{
		case 3:
			{
				ASSERT(pVarExtraInfo->vt == VT_DISPATCH);
				pVarExtraInfo->pdispVal->Release();//这样做的目的是收回MainFrame自己加的
				//Action的ExtraInfo里面的RTXCData对象内存	
				break;
			}
		}
	}

	if(CString(lpszGroup) == ACTION_GROUP_NAME_MAINTOOLBAR_AREA)
    {
        ASSERT(pVarID->vt == VT_I4);
        switch(pVarID->lVal)
        {
        case 10:
            {
                ASSERT(pVarExtraInfo->vt == VT_DISPATCH);
                pVarExtraInfo->pdispVal->Release();//这样做的目的是收回MainFrame自己加的
                //Action的ExtraInfo里面的RTXCData对象内存	
                break;
            }
        }
    }
}

LONG CPlugInYgNoticeModule::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS) {
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		lstrcpy(retdata,data);
		RegCloseKey(hkey);
	}

    return retval;
}

HINSTANCE CPlugInYgNoticeModule::GotoURL(LPCTSTR url, int showcmd)
{
	TCHAR key[MAX_PATH + MAX_PATH];

	// First try ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

	// If it failed, get the .htm regkey and lookup the program
	if ((UINT)result <= HINSTANCE_ERROR) {

		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
			lstrcat(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) {                       // No quotes found
					pos = _tcsstr(key, _T("%1"));       // Check for %1, without quotes 
					if (pos == NULL)                   // No parameter at all...
						pos = key+lstrlen(key)-1;
					else
						*pos = '\0';                 // Remove the parameter
				}
				else
					*pos = '\0';                       // Remove the parameter

				lstrcat(pos, _T(" "));
				lstrcat(pos, url);
				USES_CONVERSION;
				#ifdef  UNICODE                     
				  result = (HINSTANCE)WinExec(T2A(key),showcmd);
				#else   /* UNICODE */         
				  result = (HINSTANCE)WinExec(key,showcmd);
				#endif /* UNICODE */
			}
		}
	}

	return result;
}

void CPlugInYgNoticeModule::ReportError(int nError)
{
	CString str;
	switch (nError) {
		case 0:                       str = _T("The operating system is out\nof memory or resources."); break;
		case SE_ERR_PNF:              str = _T("The specified path was not found."); break;
		case SE_ERR_FNF:              str = _T("The specified file was not found."); break;
		case ERROR_BAD_FORMAT:        str = _T("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."); break;
		case SE_ERR_ACCESSDENIED:     str = _T("The operating system denied\naccess to the specified file."); break;
		case SE_ERR_ASSOCINCOMPLETE:  str = _T("The filename association is\nincomplete or invalid."); break;
		case SE_ERR_DDEBUSY:          str = _T("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."); break;
		case SE_ERR_DDEFAIL:          str = _T("The DDE transaction failed."); break;
		case SE_ERR_DDETIMEOUT:       str = _T("The DDE transaction could not\nbe completed because the request timed out."); break;
		case SE_ERR_DLLNOTFOUND:      str = _T("The specified dynamic-link library was not found."); break;
		case SE_ERR_NOASSOC:          str = _T("There is no application associated\nwith the given filename extension."); break;
		case SE_ERR_OOM:              str = _T("There was not enough memory to complete the operation."); break;
		case SE_ERR_SHARE:            str = _T("A sharing violation occurred. ");
		default:                      str.Format(_T("Unknown Error (%d) occurred."), nError); break;
	}
	str = _T("超链接打开失败:\n\n") + str;
	AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);
}


void CPlugInYgNoticeModule::OpenURL(LPCTSTR url)
{
	int result = (int)GotoURL(url, SW_SHOW);
	BOOL bVisited = (result > HINSTANCE_ERROR);
	if (!bVisited) {
		MessageBeep(MB_ICONEXCLAMATION);	// Unable to follow link
		ReportError(result);
	} 
}

void CPlugInYgNoticeModule::OnActionInvoked(LPCTSTR lpszGroup, const VARIANT * pVarID, const VARIANT * pVarExtraInfo)
{
	_trace(_T("PlugInYgNotice:OnActionInvoked-lpszGroup[%s]"),CString(lpszGroup));
	if(CString(lpszGroup) == ACTION_GROUP_NAME_YOUCANDO_AREA)
	{
		//您可以区域
		ASSERT(pVarID->vt == VT_I4);
		switch(pVarID->lVal)
		{
		case 3:
			{

				if (m_ptrRoot != NULL)
				{
				
					//// Tab的CLSID
					LPOLESTR pstr=NULL;
					StringFromCLSID(CLSID_YgTabFlash, &pstr);
					m_ptrRoot->ShowTabs(_bstr_t(pstr));
					
				}
				
				//AfxMessageBox(_T("Hello, Demo!"));
				break;
			}
		case 4:
			{
				OpenURL(_T("http://www.baidu.com"));
				break;
			}
		case 5:
			{
				OpenURL(_T("http://www.163.com"));
				break;
			}
		}
	}
	else if (CString(lpszGroup) == ACTION_GROUP_NAME_MAINTOOLBAR_AREA)
	{
		_trace(_T("PlugInYgNotice:OnActionInvoked-lVal[%d]"),pVarID->lVal);
		//主面板图标
		ASSERT(pVarID->vt == VT_I4);
		switch(pVarID->lVal)
		{
		case 10:
			{				
				_trace(_T("PlugInYgNotice:OnActionInvoked-Tab"));			
				/*//AfxMessageBox(_T("Hello,test"));		
                CString strpath = GetPlugInYgNoticeModulePath();
                strpath  += "Tabs//love.ico";

                IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();
                ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_ICON_PATH, _bstr_t(strpath));

				CString csTmp;
				csTmp.Format(_T("(%d)"),m_lNoticeNotReadCount);     
                ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_CAPTION, 
                    _bstr_t(csTmp));
				csTmp.Format(_T("%d个未回复帖"),m_lNoticeNotReadCount);
                ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_TOOLTIP, 
                    _bstr_t(csTmp));
                ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_DISABLE,
                    _bstr_t(_T("true")));
                ptrData->SetLong(RDK_MAINTOOLBARBTN_ITEM_WIDTH, 40);
                IDispatchPtr ptrDisp = ptrData;
                _variant_t varExtraInfo(ptrDisp.Detach());
                //m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)10), varExtraInfo);
                m_ptrActionMgr->SetActionExtraInfo(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)10), varExtraInfo);
				*/
				if (m_ptrRoot != NULL)
				{				
					_trace(_T("PlugInYgNotice:OnActionInvoked-ShowTabs"));			
					//// Tab的CLSID
					LPOLESTR pstr=NULL;
					StringFromCLSID(CLSID_YgTabFlash, &pstr);
					m_ptrRoot->ShowTabs(_bstr_t(pstr));
					
				}
			}
			break;
		default:
			break;
		}
	}
	else if (CString(lpszGroup) == ACTION_GROUP_NAME_STATUSBAR_AREA)	
	{
        //状态栏
		ASSERT(pVarID->vt == VT_I4);
		switch(pVarID->lVal)
		{
		case 1:
			_trace(_T("PlugInYgNotice:OnActionInvoked-STATUSBAR-1"));	
			break;
		case 2:
			//AfxMessageBox(_T("btn 1 is clicked!"));
			break;
		case 3:
			//AfxMessageBox(_T("btn 2 is clicked!"));
			break;
		case 4:
			//AfxMessageBox(_T("btn 3 is clicked!"));
			break;
        case 5:
            {
				/*
                AfxMessageBox(_T("btn 4 is clicked!"));
                CString strpath = GetPlugInYgNoticeModulePath();
                CString stricopath = strpath +"Tabs//statusbar.ico";        
                
                IRTXCDataPtr ptrData5 = m_ptrRoot->CreateRTXCData();
                if (ptrData5 != NULL)
                {
                    ptrData5->SetString(RDK_STATUSBAR_ITEM_ICON_PATH, _bstr_t(stricopath));
                    ptrData5->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip4!")));
                    ptrData5->SetString(RDK_STATUSBAR_ITEM_DISABLE, _bstr_t(_T("true")));
                    ptrData5->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_BUTTON);
                    ptrData5->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 17);
                    
                    IDispatchPtr pDisp = ptrData5;
                    _variant_t var(pDisp.Detach());
                    m_ptrActionMgr->SetActionExtraInfo(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)5), var);
                }
                */
            }

			break;
		default:
			break;
		}
	}
	else if (CString(lpszGroup) == ACTION_GROUP_NAME_IMTOOLBAR_AREA)
	{
	    //IM窗口
	}
}



void CPlugInYgNoticeModule::NoticeAction(BOOL bShow)
{
	_trace(_T("PlugInYgNotice:NoticeAction,bShow[%d]"),bShow);
	//状态栏
    if(bShow)
	{
		_trace(_T("PlugInYgNotice:NoticeAction -- TRUE"));		
		IRTXCDataPtr ptrData3 = m_ptrRoot->CreateRTXCData();	
		if (ptrData3 != NULL)
		{				
			ptrData3->SetString(RDK_STATUSBAR_ITEM_CAPTION, _bstr_t(_T("收到一个公告!")));
			ptrData3->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("公告已到达!")));
			ptrData3->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_TEXT);
			ptrData3->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 120);
			IDispatchPtr pDisp = ptrData3;
			_variant_t var(pDisp.Detach());
			m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)1), var);		
		}		
    }
	else
	{
		_trace(_T("PlugInYgNotice:NoticeAction -- FALSE"));			
		m_ptrActionMgr->DelAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)1));
	}  

	IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();
	if (ptrData != NULL)
    {		
		CString strpath = GetPlugInYgNoticeModulePath();
        strpath  += "Tabs//love.ico";
		CString csTmp;
		ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_ICON_PATH, _bstr_t(strpath));
		csTmp.Format(_T("(%d)"),m_lNoticeNotReadCount);     
        ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_CAPTION, _bstr_t(csTmp));
		csTmp.Format(_T("%d个未回复帖"),m_lNoticeNotReadCount);
        ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_TOOLTIP, _bstr_t(csTmp));
        ptrData->SetString(RDK_MAINTOOLBARBTN_ITEM_DISABLE,_bstr_t(_T("false")));
        ptrData->SetLong(RDK_MAINTOOLBARBTN_ITEM_WIDTH, 40);
        IDispatchPtr ptrDisp1 = ptrData;
        _variant_t varExtraInfo(ptrDisp1.Detach());        
        m_ptrActionMgr->SetActionExtraInfo(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)10), varExtraInfo);		
	}
}


void CPlugInYgNoticeModule::InitAction()
{
	_trace(_T("PlugInYgNotice:InitAction"));
	if(m_ptrActionMgr == NULL)
	{
		ASSERT(FALSE);
		return;
	}
	if(m_ptrRoot == NULL)
	{
		ASSERT(FALSE);
		return;
	}
	CString strpath = GetPlugInYgNoticeModulePath();
	CString stricopath="";
	//添加三个YouCanDo Item
	IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();
	if (ptrData != NULL)
	{		
		ptrData->SetString(RDK_YOUCANDO_ITEM_ICON_PATH, _bstr_t(_T("love.ico")));
		ptrData->SetString(RDK_YOUCANDO_ITEM_CAPTION, _bstr_t(_T("查看公告")));
		IDispatchPtr ptrDisp = ptrData;
		_variant_t varExtraInfo(ptrDisp.Detach());
		m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_YOUCANDO_AREA, _variant_t((long)3), varExtraInfo);
		m_ptrActionMgr->SetActionPos(ACTION_GROUP_NAME_YOUCANDO_AREA,_variant_t((long)3),0);
	}

	IRTXCDataPtr ptrData8 = m_ptrRoot->CreateRTXCData();
	if (ptrData8 != NULL)
	{		
		ptrData8->SetString(RDK_YOUCANDO_ITEM_ICON_PATH, _bstr_t(_T("love.ico")));
		ptrData8->SetString(RDK_YOUCANDO_ITEM_CAPTION, _bstr_t(_T("OA1")));
		IDispatchPtr ptrDisp = ptrData8;
		_variant_t varExtraInfo(ptrDisp.Detach());
		m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_YOUCANDO_AREA, _variant_t((long)4), varExtraInfo);
		m_ptrActionMgr->SetActionPos(ACTION_GROUP_NAME_YOUCANDO_AREA,_variant_t((long)4),0);
	}

	IRTXCDataPtr ptrData9 = m_ptrRoot->CreateRTXCData();
	if (ptrData9 != NULL)
	{		
		ptrData9->SetString(RDK_YOUCANDO_ITEM_ICON_PATH, _bstr_t(_T("love.ico")));
		ptrData9->SetString(RDK_YOUCANDO_ITEM_CAPTION, _bstr_t(_T("OA2")));
		IDispatchPtr ptrDisp = ptrData9;
		_variant_t varExtraInfo(ptrDisp.Detach());
		m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_YOUCANDO_AREA, _variant_t((long)5), varExtraInfo);
		m_ptrActionMgr->SetActionPos(ACTION_GROUP_NAME_YOUCANDO_AREA,_variant_t((long)5),0);
	}

	//工具栏图标
	IRTXCDataPtr ptrData2 = m_ptrRoot->CreateRTXCData();       
	if (ptrData2 != NULL)
    {
		stricopath = strpath +"Tabs//love.ico";        
        ptrData2->SetString(RDK_MAINTOOLBARBTN_ITEM_ICON_PATH, _bstr_t(stricopath));

		CString csTmp;
		csTmp.Format(_T("(%d)"),m_lNoticeNotReadCount);
        ptrData2->SetString(RDK_MAINTOOLBARBTN_ITEM_CAPTION, _bstr_t(csTmp));
		csTmp.Format(_T("%d个未回复帖"),m_lNoticeNotReadCount);
        ptrData2->SetString(RDK_MAINTOOLBARBTN_ITEM_TOOLTIP, _bstr_t(csTmp));
        ptrData2->SetString(RDK_MAINTOOLBARBTN_ITEM_DISABLE, _bstr_t(_T("false")));
        ptrData2->SetLong(RDK_MAINTOOLBARBTN_ITEM_WIDTH, 40);
        IDispatchPtr ptrDisp = ptrData2;
        _variant_t varExtraInfo(ptrDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)10), varExtraInfo);
//      m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)11), varExtraInfo);
//      m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_MAINTOOLBAR_AREA, _variant_t((long)12), varExtraInfo);
    }

    //状态栏
  /*  IRTXCDataPtr ptrData3 = m_ptrRoot->CreateRTXCData();
    if (ptrData3 != NULL)
    {
        ptrData3->SetString(RDK_STATUSBAR_ITEM_CAPTION, _bstr_t(_T("this is a test!")));
        ptrData3->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip!")));
        ptrData3->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_TEXT);
        ptrData3->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 120);
        
        IDispatchPtr pDisp = ptrData3;
        _variant_t var(pDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)1), var);
    }

	IRTXCDataPtr ptrData4 = m_ptrRoot->CreateRTXCData();
    if (ptrData4 != NULL)
    {
		stricopath = strpath +"Tabs//statusbar.ico";        
        ptrData4->SetString(RDK_STATUSBAR_ITEM_ICON_PATH, _bstr_t(stricopath));
        ptrData4->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip!")));
        ptrData4->SetString(RDK_STATUSBAR_ITEM_DISABLE, _bstr_t(_T("false")));
        ptrData4->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_BUTTON);
        ptrData4->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 17);
        
        IDispatchPtr pDisp = ptrData4;
        _variant_t var(pDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)2), var);
    }
    
    IRTXCDataPtr ptrData5 = m_ptrRoot->CreateRTXCData();
    if (ptrData5 != NULL)
    {
		stricopath = strpath +"Tabs//statusbar.ico";        
        ptrData5->SetString(RDK_STATUSBAR_ITEM_ICON_PATH, _bstr_t(stricopath));
        ptrData5->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip2!")));
        ptrData5->SetString(RDK_STATUSBAR_ITEM_DISABLE, _bstr_t(_T("false")));
        ptrData5->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_BUTTON);
        ptrData5->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 17);
        
        IDispatchPtr pDisp = ptrData5;
        _variant_t var(pDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)3), var);
    }
    
    IRTXCDataPtr ptrData6 = m_ptrRoot->CreateRTXCData();
    if (ptrData6 != NULL)
    {
		stricopath = strpath +"Tabs//statusbar.ico";        
        ptrData6->SetString(RDK_STATUSBAR_ITEM_ICON_PATH, _bstr_t(stricopath));
        ptrData6->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip3!")));
        ptrData6->SetString(RDK_STATUSBAR_ITEM_DISABLE, _bstr_t(_T("false")));
        ptrData6->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_BUTTON);
        ptrData6->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 17);
        
        IDispatchPtr pDisp = ptrData6;
        _variant_t var(pDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)4), var);
    }
    
    IRTXCDataPtr ptrData7 = m_ptrRoot->CreateRTXCData();
    if (ptrData7 != NULL)
    {
		stricopath = strpath +"Tabs//statusbar.ico";        
        ptrData7->SetString(RDK_STATUSBAR_ITEM_ICON_PATH, _bstr_t(stricopath));
        ptrData7->SetString(RDK_STATUSBAR_ITEM_TOOLTIP, _bstr_t(_T("this is a test fot tooltip4!")));
        ptrData7->SetString(RDK_STATUSBAR_ITEM_DISABLE, _bstr_t(_T("false")));
        ptrData7->SetString(RDK_STATUSBAR_ITEM_TYPE, RDK_STATUSBAR_ITEMTYPE_BUTTON);
        ptrData7->SetLong(RDK_STATUSBAR_ITEM_WIDTH, 17);
        
        IDispatchPtr pDisp = ptrData7;
        _variant_t var(pDisp.Detach());
        m_ptrActionMgr->AddAction(ACTION_GROUP_NAME_STATUSBAR_AREA, _variant_t((long)5), var);
    }
	*/
}

STDMETHODIMP CPlugInYgNoticeModule::XRTXPluginHandler::OnEvent(BSTR id ,IDispatch* pData, VARIANT* pRet)
{
	METHOD_PROLOGUE(CPlugInYgNoticeModule, RTXPluginHandler)
	
	IRTXCDataPtr ptrData = (IRTXCData* )pData;
	RTX_TRY
	{
		CString strEventId = id;
		CString strNotifyContent = (LPTSTR)ptrData->GetString(_bstr_t(_T("NotifyContent")));
		
        
		//::AfxMessageBox(strNotifyContent);
		_trace(_T("PlugInYgNotice:XRTXPluginHandler::OnEvent[%s]"),strNotifyContent);
		
		if (strEventId == ENTER_TAB_EVENT)
		{			
			if (pThis->m_pTabBaseMgr)
			{
				ITabBaseMgr* pTabBaseMgr = pThis->m_pTabBaseMgr;
				pTabBaseMgr->StopTabFlash(CLSID_YgTabFlash);
			}
		}
		else if (strEventId == YGTEST_EVENT)
		{			
			pThis->m_lNoticeNotReadCount = ptrData->GetLong(_bstr_t(_T("LONG_PARAM1")));
			pThis->NoticeAction(FALSE);
			_trace(_T("PlugInYgNotice::XRTXPluginHandler::OnEvent:YGTEST_EVENT:m_lNoticeNotReadCount[%d]"),pThis->m_lNoticeNotReadCount);				
			/*
			CString strMsg;
			strMsg.Format(_T("STR_PARAM1 = %s \r\n LONG_PARAM1 = %d \r\n Ret1 = 4321"), strNotifyContent, lParam);
			pRet->vt = VT_I4;
			pRet->lVal = 4321;
			::MessageBox(NULL,strMsg, _T("模块共享事件触发"), MB_OK);
			*/
		}
	}
	RTX_CATCH_ALL(return E_FAIL)
	return S_OK;
}

HRESULT CPlugInYgNoticeModule::OnAccountChange()
{
	return S_OK;
}

#define RTX_COPR_GET_ROOT 1
HRESULT CPlugInYgNoticeModule::OnInvoke(VARIANT Receiver, 
								  VARIANT Parameter, VARIANT Extra, VARIANT* Result)
{
	if ((Parameter.vt == VT_I4) && (Parameter.lVal == RTX_COPR_GET_ROOT))
	{
		IRTXEvent * p = NULL;
		
		if (SUCCEEDED(m_ptrEvent->QueryInterface(IID_IRTXEvent, (void**)&p)) && p != NULL)
		{
			Result->vt = VT_DISPATCH;
			Result->pdispVal = (IDispatch *)p;
			
			p->AddRef();
		}
		
		return Result != NULL ? S_OK : E_FAIL;
	}
	return S_OK;
}

HRESULT CPlugInYgNoticeModule::OnUnload(enum RTXC_MODULE_UNLOAD_REASON Reason)
{
	IRTXCUICommand* pUICmd = dynamic_cast<IRTXCUICommand* >(&m_xMenuSink);
	m_ptrMenu->DelItem(RTXC_UI_TYPE_ORG_STRUCT_USER, IDM_START_TAB_FLASH,
		pUICmd);
	_trace(_T("PlugInYgNotice:OnUnload"));
		//注销模块事件的接收
	IRTXCEventCenterPtr ptrEventCtr = m_ptrRoot->RTXCEventCenter;
	CComPtr<IUnknown> ptrIUnkown ;
		REFIID iid = IID_IUnknown;
	ExternalQueryInterface(&iid,  (LPVOID*)&ptrIUnkown);
	CComPtr<IRTXCModule> ptrModule;
	REFIID iid2 = IID_IRTXCModule;
	ExternalQueryInterface(&iid2,  (LPVOID*)&ptrModule);
	
	if (m_lEnterCookie)
	{
		ptrEventCtr->RemoveModuleEventSink(_bstr_t(ENTER_TAB_EVENT) , m_lEnterCookie, ptrModule);				
	}
	if (m_lLeaveCookie)
	{
		ptrEventCtr->RemoveModuleEventSink(_bstr_t(LEAVE_TAB_EVENT) , m_lLeaveCookie, ptrModule);
	}
	//注销模块事件的接收
			if (m_lCookie)
			{				
				ptrEventCtr->RemoveModuleEventSink(_bstr_t(YGTEST_EVENT) , m_lCookie, ptrModule);	

			}
	
	VERIFY(m_RootEventSink.Unadvise());
	m_RootEventSink.UnhookEvent(evt_OnLoginResult, this, &CPlugInYgNoticeModule::OnLoginResult);

	VERIFY(m_PresenceEventSink.Unadvise());
	m_PresenceEventSink.UnhookEvent(evt_OnPresenceChange, this, &CPlugInYgNoticeModule::OnPresenceChange);
	VERIFY(m_ModuleSiteEventSink.Unadvise());
	m_ModuleSiteEventSink.UnhookEvent(evt_OnDataReceived, this, &CPlugInYgNoticeModule::OnDataReceived);
	m_ModuleSiteEventSink.UnhookEvent(evt_OnViewData, this, &CPlugInYgNoticeModule::OnViewData);
	m_ModuleSiteEventSink.UnhookEvent(evt_OnSendDataResult, this, &CPlugInYgNoticeModule::OnSendDataResult);

	VERIFY(m_RTXBuddyManagerEventSink.Unadvise());
	m_RTXBuddyManagerEventSink.UnhookEvent(evt_OnBuddyProfileChange, this, &CPlugInYgNoticeModule::OnBuddyProfileChange);

	VERIFY(m_RTXGroupManagerEventSink.Unadvise());
	m_RTXGroupManagerEventSink.UnhookEvent(evt_OnGroupChange, this, &CPlugInYgNoticeModule::OnGroupChange);
	m_RTXGroupManagerEventSink.UnhookEvent(evt_OnGroupAdd, this, &CPlugInYgNoticeModule::OnGroupAdd);
	m_RTXGroupManagerEventSink.UnhookEvent(evt_OnGroupRemove, this, &CPlugInYgNoticeModule::OnGroupRemove);
	m_RTXGroupManagerEventSink.UnhookEvent(evt_OnBuddyAdd, this, &CPlugInYgNoticeModule::OnBuddyAdd);
	m_RTXGroupManagerEventSink.UnhookEvent(evt_OnBuddyRemove, this, &CPlugInYgNoticeModule::OnBuddyRemove);

	VERIFY(m_MFCSupportEventSink.Unadvise());
	m_MFCSupportEventSink.UnhookEvent(evt_OnPreTranslateMessage, this, &CPlugInYgNoticeModule::OnPreTranslateMessage);
	m_MFCSupportEventSink.UnhookEvent(evt_OnIdle, this, &CPlugInYgNoticeModule::OnIdle);

	return S_OK;
}

HRESULT CPlugInYgNoticeModule::get_Info(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);

	*pVal = NULL;

	if (Field == RTXC_PLUGIN_INFO_FIELD_DESCRIPTION)
	{
		*pVal = CString(RTX_MODULE_DESCRIPTION_PLUGINYGNOTICE).AllocSysString();
	}

	return S_OK;
}

void CPlugInYgNoticeModule::OnLoginResult(RTXC_LOGIN_RESULT Result)
{
	
}

void CPlugInYgNoticeModule::OnPresenceChange(BSTR Account, RTX_PRESENCE RTXPresence)
{

}

void CPlugInYgNoticeModule::OnDataReceived(LPCTSTR Key)
{
	_trace(_T("PlugInYgNotice:OnDataReceived"));
	//IRTXCDataPtr ptrData ;
	RTX_TRY
	{
		//ptrData = m_ptrModuleSite->GetData(Key, VARIANT_TRUE);
		IRTXCDataPtr& ptrData = m_ptrModuleSite->GetData(_bstr_t(Key), VARIANT_TRUE);  //获取服务器应用传过来的数据,获取出来为一个RTXCData对象
	
		CComBSTR bstrSender = (BSTR)ptrData->GetString(_bstr_t("Sender"));  //获取发送者
		CComBSTR bstrMsg = (BSTR)ptrData->GetString(_bstr_t("Content"));	   //获取消息内容
		
		CString strReceive=LPCTSTR(bstrMsg);
		CString csTemp;
		AfxExtractSubString(csTemp, (LPCTSTR)strReceive, 0, '|'); // 得到 NOTICE或TALK
		if(csTemp == "NOTICE")
		{
			m_lNoticeNotReadCount++;
			IClientObjectsModulePtr ptrClientObjects = m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_CLIENT_OBJS];
			ITabBaseMgr* pTabBaseMgr = NULL;
			HRESULT hr = ptrClientObjects->get_Object(RTX_CLIENT_OBJECTS_IDENTIFIER_TABBASEMGR, (IDispatch** )&pTabBaseMgr);
			if (hr == S_OK && pTabBaseMgr)
			{
				m_pTabBaseMgr = pTabBaseMgr;
				pTabBaseMgr->StartTabFlash(CLSID_YgTabFlash, 29);
			}
			NoticeAction(TRUE);
		}	

		//// 测试事件触发函数
		if (m_ptrEvent)
		{
			m_ptrEvent->OnEvent(bstrMsg);
		}
	}
	RTX_CATCH_ALL(ASSERT(FALSE));
}

#define RDK_SENDER _T("Sender")
#define RDK_MSG_CONTENT _T("Content")
void CPlugInYgNoticeModule::OnViewData(LPCTSTR Key)
{
	_trace(_T("PlugInYgNotice:OnViewData"));
	//接受到消息tip后 点击会到这里对消息进行进一步处理
	IRTXCDataPtr ptrData ;
	
	RTX_TRY
	{
		ptrData = m_ptrModuleSite->GetData(Key, VARIANT_TRUE);
	}
	RTX_CATCH_ALL(ASSERT(FALSE));
	
	if(ptrData)
	{			
		CString strMsg ;
		strMsg.Format( _T("发送者:%s \r\n信息内容: %s"),CComBSTR((BSTR)ptrData->GetString(RDK_SENDER)).m_str, 
			CComBSTR((BSTR)ptrData->GetString(RDK_MSG_CONTENT)).m_str);
		AfxMessageBox(strMsg);
	}
}

void CPlugInYgNoticeModule::OnSendDataResult(RTXC_MODULE_SEND_DATA_RESULT Result, const VARIANT* Extra)
{

}

void CPlugInYgNoticeModule::OnBuddyProfileChange(IRTXCRTXBuddy* RTXCRTXBuddy)
{

}

void CPlugInYgNoticeModule::OnGroupChange(IRTXCRTXGroup* RTXCRTXGroup)
{

}

void CPlugInYgNoticeModule::OnGroupAdd(IRTXCRTXGroup* RTXCRTXGroup)
{

}

void CPlugInYgNoticeModule::OnGroupRemove(IRTXCRTXGroup* RTXCRTXGroup)
{

}

void CPlugInYgNoticeModule::OnBuddyAdd(IRTXCRTXGroup* RTXCRTXGroup, IRTXCRTXBuddy* RTXCRTXBuddy)
{
	
}

void CPlugInYgNoticeModule::OnBuddyRemove(IRTXCRTXGroup* RTXCRTXGroup, IRTXCRTXBuddy* RTXCRTXBuddy)
{

}

void CPlugInYgNoticeModule::OnPreTranslateMessage(long MSGPointer, VARIANT_BOOL* Handled)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	*Handled = ((CPlugInYgNoticeApp*)AfxGetApp())->PreTranslateMessage((MSG*)MSGPointer) ? VARIANT_TRUE : VARIANT_FALSE;
}

void CPlugInYgNoticeModule::OnIdle(long Count)
{

}

CString CPlugInYgNoticeModule::GetStructUser(VARIANT Parameter)
{
	CString strUser=_T("");
	
	if(Parameter.vt == VT_DISPATCH)
	{
		IRTXCDataCollectionPtr ptrReceivers = Parameter.pdispVal;
		

		int nCount = ptrReceivers->Count;
		_trace(_T("PlugInYgNotice::GetStructUser:nCount[%d]"),nCount);
		for(int i=0;i<nCount;i++)
		{
			IRTXCDataPtr pstrRtxData=ptrReceivers->GetItem(i+1);
			long nType=pstrRtxData->GetLong(RDK_TYPE);
			_trace(_T("PlugInYgNotice::GetStructUser:nType[%d]"),nType);
			if( nType == OBJECT_RTX_BUDDY)
			{
				_bstr_t bstrUserName=pstrRtxData->GetString(RDK_VALUE);
				strUser+=OLE2T(bstrUserName);	//得到接收用户名
				strUser+=CString(_T(";"));					
			}	
			else if( nType == OBJECT_RTX_GROUP)
			{
				//_bstr_t bstrXML=pstrRtxData->GetXML();
				//CString csShow=OLE2T(bstrXML);
				//_trace(_T("PlugInYgNotice::GetStructUser:bstrXML[%s]"),csShow);
				long groupId=pstrRtxData->GetLong(RDK_VALUE);
				if (m_ptrRoot != NULL)
				{
					IRTXCRTXGroupManagerPtr pGroupmgr=m_ptrRoot->GetRTXGroupManager();
					if(pGroupmgr != NULL)
					{
						IRTXCRTXGroupPtr pGroup=pGroupmgr->GetGroup(groupId);
						if(pGroup != NULL)
						{
							//_bstr_t bstrGroup=pGroup->GetName();
							//CString csShow=OLE2T(bstrGroup);
							//_trace(_T("PlugInYgNotice::GetStructUser:bstrGroup[%s]"),csShow);
							IRTXCRTXBuddyCollectionPtr ptrBuddys =pGroup->GetBuddies();
							int iCount = ptrBuddys->GetCount();
							for(int n=0;n<iCount;n++)
							{
								IRTXCRTXBuddyPtr pBuddy=ptrBuddys->GetItem(n);
								_bstr_t bstrAccount=pBuddy->GetAccount();
								strUser+=OLE2T(bstrAccount);	//得到接收用户名
								strUser+=CString(_T(";"));			
							}
						}
					}
				}
			}
		}
	}
	else if(Parameter.vt == VT_BSTR)
	{
		_trace(_T("PlugInYgNotice::GetStructUser:VT_BSTR"));
		_bstr_t bstrUserName= Parameter.bstrVal;
		strUser.Format(_T("%s"),(LPCTSTR)bstrUserName);
	}
	
	return strUser;
}

CString CPlugInYgNoticeModule::GetIMThirdUser(VARIANT Parameter)
{
	CString strUser,str ; 
	
	IRTXCSessionPtr ptrSession = Parameter.pdispVal;
	
	_bstr_t bstrParticipants = ptrSession->Participant;
	// str = _com_util::ConvertBSTRToString(bstrParticipants);   
	str.Format(_T("%s"),(LPCTSTR)bstrParticipants);
	_trace(_T("PlugInYgNotice::GetIMThirdUser:str[%s]"),str);

	strUser = str;
	
	return strUser;
}

HRESULT CPlugInYgNoticeModule::MenuOnInvoke(enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter)
{
	_trace(_T("PlugInYgNotice::MenuOnInvoke:Type[%d]-Id[%d]"),Type,Id);
	if (Type != RTXC_UI_TYPE_BUDDY_SUBITEM)
	{
		if (Id == IDM_START_TAB_FLASH)
		{
			CString strAllAccounts=_T("");


			if (Type != RTXC_UI_TYPE_IM_THIRDPARTY) {
				strAllAccounts = GetStructUser(Parameter);
				//SendData(strAllAccounts);
			}
			else{
				strAllAccounts = GetIMThirdUser(Parameter);
				//SendData(strAllAccounts);
			}
			_trace(_T("PlugInYgNotice::MenuOnInvoke:strAllAccounts[%s]"),strAllAccounts);
			/*
			IRTXCDataCollectionPtr ptrReceivers = Parameter.pdispVal;
			int nCount = ptrReceivers->Count;
			int n=nCount-1;
			for(int i=0;i<nCount;i++)
			{
				IRTXCDataPtr pstrRtxData=ptrReceivers->GetItem(i+1);
				long nType=pstrRtxData->GetLong(RDK_TYPE);
				if(nType==OBJECT_RTX_BUDDY || nType==OBJECT_RTX_GROUP)
				{
					_bstr_t bstrUserName=pstrRtxData->GetString(RDK_VALUE);
					strAllAccounts+=OLE2T(bstrUserName);	//得到接收用户名
					strAllAccounts+=CString(_T(";"));					
				}	
			}*/

			/*
			IRTXCDataPtr& ptrData = m_ptrRoot->CreateRTXCData();
			ptrData->SetString(_bstr_t(RDK_KEY), _bstr_t(BuildGUID()));
			m_ptrModuleSite->SendData(_bstr_t((LPCTSTR)strAllAccounts), ptrData, 
				RTXC_SEND_DATA_FLAG_FILTERING_IS_FORBIDDEN);
			*/			
				//// 测试事件触发函数
			if (m_ptrEvent)
			{				
				//int index=strAllAccounts.ReverseFind(_T(';'));
			//	if(index != -1)
				//{
				//	strAllAccounts=strAllAccounts.Left(index);
				//}
				CString csEvent="RECEIVER|"+strAllAccounts;
				CComBSTR bstrMsg = (BSTR)_bstr_t((LPCTSTR)csEvent);
				m_ptrEvent->OnEvent(bstrMsg);
				if (m_ptrRoot != NULL)
				{
				
					//// Tab的CLSID
					LPOLESTR pstr=NULL;
					StringFromCLSID(CLSID_YgTabFlash, &pstr);
					m_ptrRoot->ShowTabs(_bstr_t(pstr));
					
				}
			}
		}
	}
	
	return S_OK;
}

CString CPlugInYgNoticeModule::BuildGUID()
{
	_trace(_T("PlugInYgNotice:BuildGUID"));
	GUID guid = {0};
	::CoCreateGuid(&guid);
	
	USES_CONVERSION;
	
	LPTSTR lpszClassID = NULL;
	LPOLESTR lpOleStr = NULL;
	
	::StringFromCLSID(guid, &lpOleStr);
	
	if (lpOleStr == NULL)
	{
		ASSERT(FALSE);
		
		return _T("");
	}
	
	lpszClassID = W2T(lpOleStr);	
	
	if (lpszClassID == NULL)
	{
		ASSERT(FALSE);
		
		::CoTaskMemFree(lpOleStr);
		return _T("");
	}	
	
	CString str(lpszClassID);
	
	::CoTaskMemFree(lpOleStr);
	
	return str;
}

HRESULT CPlugInYgNoticeModule::XMenuSink::OnInvoke(enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter)
{	
	METHOD_PROLOGUE(CPlugInYgNoticeModule, MenuSink)
		pThis->MenuOnInvoke(Type, Id, Parameter);
	
	return S_OK;	
}

CString CPlugInYgNoticeModule::GetStructUserToMenu(VARIANT Parameter)
{
	CString strUser;
	_trace(_T("PlugInYgNotice::GetStructUserToMenu"));
	if(Parameter.vt == VT_DISPATCH)
	{
		IRTXCDataCollectionPtr ptrReceivers = Parameter.pdispVal;
		int nCount = ptrReceivers->Count;	
		_trace(_T("PlugInYgNotice::GetStructUserToMenu-Count[%d]"),nCount);
		if(nCount > 0)
		{
			IRTXCDataPtr pstrRtxData=ptrReceivers->GetItem(1);
			long nType=pstrRtxData->GetLong(RDK_TYPE);
			if(nType==OBJECT_RTX_BUDDY)
			{
				_bstr_t bstrUserName=pstrRtxData->GetString(RDK_VALUE);
				//_bstr_t bstrUserName = "test";
				strUser.Format(_T("%s"),(LPCTSTR)bstrUserName);
				
			}
		}
	}
	else if(Parameter.vt == VT_BSTR)
	{
		_bstr_t bstrUserName= Parameter. bstrVal;
		strUser.Format(_T("%s"),(LPCTSTR)bstrUserName);
	}
	
	return strUser;
}

CString CPlugInYgNoticeModule::GetIMThirdUserToMenu(VARIANT Parameter)
{
	CString strUser,str ; 
	
	IRTXCSessionPtr ptrSession = Parameter.pdispVal;
	
	_bstr_t bstrParticipants = ptrSession->Participant;
	// str = _com_util::ConvertBSTRToString(bstrParticipants);   
	str.Format(_T("%s"),(LPCTSTR)bstrParticipants);
	
	_trace(_T("PlugInYgNotice::GetIMThirdUserToMenu:str[%s]"),str);
	
	strUser = str;
	
	return strUser;
}

HRESULT CPlugInYgNoticeModule::XMenuSink::OnQueryState(enum RTXC_UI_TYPE Type, long Id, VARIANT Parameter,
												 BSTR * bstrText,
												 enum RTXC_UI_ITEM_STATE * State )
{
	METHOD_PROLOGUE(CPlugInYgNoticeModule, MenuSink)
	_trace(_T("PlugInYgNotice::XMenuSink::OnQueryState-Id[%d]-Type[%d]"),Id,Type);
		if (Id == IDM_START_TAB_FLASH )
		{
			CString strSelectName = _T("");
			
			switch(Type)
			{
			case RTXC_UI_TYPE_ORG_STRUCT_GROUP:
			case RTXC_UI_TYPE_ORG_STRUCT_USER:
			case RTXC_UI_TYPE_MYCONTACTS_USERDEFINEDGROUP_USER:
			case RTXC_UI_TYPE_RECENTCONTACTS_SESSIONS_USER:
			case RTXC_UI_TYPE_MAINFRAME_ACTION:
				{
					
					strSelectName = pThis->GetStructUserToMenu(Parameter);
					break;
				}
				
			case RTXC_UI_TYPE_IM_THIRDPARTY:
				{
					strSelectName = pThis->GetIMThirdUserToMenu(Parameter);
					break;
				}
				
			default:
				break;
				
			}
			_trace(_T("PlugInYgNotice::XMenuSink::OnQueryState-strSelectName[%s]"),strSelectName);
			int nfind=strSelectName.Find(_T(";"));
			if ((strSelectName != _T("")) && (nfind == -1))
			{
				if ( RTX_PRESENCE_OFFLINE == 
					pThis->m_ptrRoot->Presence->RTXPresence[_bstr_t(strSelectName)] 
					)
				{
					// 选中的用户离线，菜单设置为Disable状态
					*State = RTXC_UI_ITEM_STATE_DISABLED;
					return S_OK;
				}
			}
			
		}
	
		return S_OK;
}

CComObject<CRTXEvent>* CPlugInYgNoticeModule::_CreateEvent()
{
	IRTXEvent* ptrRTXEvent = NULL;
	CComObject<CRTXEvent>* p = NULL;
	RTX_TRY
	{
		ATLTRY(p = new CComObject<CRTXEvent>(NULL))
			p->SetVoid(NULL);
		
		HRESULT hr = E_OUTOFMEMORY;
		
		p->InternalFinalConstructAddRef();
		hr = p->FinalConstruct();
		p->InternalFinalConstructRelease();
		
		if (SUCCEEDED(hr))
		{
			hr = p->QueryInterface(IID_IRTXEvent, (void**)&ptrRTXEvent);
		}
		
		if (FAILED(hr) || ptrRTXEvent == NULL)
		{
			if (p != NULL)
			{
				delete p;
				p = NULL;
			}
			
			return NULL;
		}
	}
	RTX_CATCH_ALL(ASSERT(FALSE);return NULL)
		
		return p;
}

