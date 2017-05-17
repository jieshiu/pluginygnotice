// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "RTXCModuleInterface.tlb" no_namespace named_guids raw_interfaces_only

#import "../../../tlb/ClientObjects.tlb" no_namespace named_guids raw_interfaces_only
#import "../../../tlb/action.tlb" no_namespace named_guids

#import "../YgTabFlash/Debug/YgTabFlash.tlb" no_namespace named_guids raw_interfaces_only

#include "mfcdual.h"

#include "RTXCMisc.h"
#include "RTXCAPIInc.h"

#include "../../../include/ClientObjectsEventSinkInc.h"
#include "../../../include/RTXCModuleIds.h"
#include "../../../include/RTXCDataKeys.h"
#include "../../../include/APIShare.h"

#define RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE						_T("Tencent.RTX.PlugInYgNotice")
#define RTX_MODULE_NAME_PLUGINYGNOTICE							_T("超级RTX公告")
#define RTX_MODULE_DESCRIPTION_PLUGINYGNOTICE						_T("公告信息发布  written by jie")
#define RTX_APP_NAME_PLUGINYGNOTICE								_T("PlugInYgNoticeApp")

#define ENTER_TAB_EVENT _T("EnterExtTabEvent")
#define LEAVE_TAB_EVENT _T("LeaveExtTabEvent")
#define YGTEST_EVENT _T("YgTestEvent")

#define IDM_START_TAB_FLASH 88882
#define RDK_TYPE _T("Type")
#define RDK_VALUE _T("Value")
#define RDK_KEY _T("Key")

extern HMODULE g_hPlugInYgNoticeModule;
inline CString GetPlugInYgNoticeModulePath()
{
	static CString strPath;

	if (strPath == _T(""))
	{
		ASSERT(g_hPlugInYgNoticeModule != NULL);
		strPath = GetModulePath(g_hPlugInYgNoticeModule);
	}

	return strPath;
}

//#ifdef _DEBUG
inline void _trace(TCHAR *fmt, ...)
{   
   TCHAR out[1024];
    va_list body;
    va_start(body, fmt);
    _vstprintf(out, fmt, body);    // 译注：格式化输入的字符串 fmtt
    va_end(body);                 //       到输出字符串 ou
    OutputDebugString(out);       // 译注：输出格式化后的字符串到调试器    
}
	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

