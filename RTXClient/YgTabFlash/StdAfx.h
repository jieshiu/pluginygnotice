#if !defined(AFX_STDAFX_H__D858B409_EFD1_45A0_BC66_14C9843459CA__INCLUDED_)
#define AFX_STDAFX_H__D858B409_EFD1_45A0_BC66_14C9843459CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define ENTER_TAB_EVENT _T("EnterExtTabEvent")
#define LEAVE_TAB_EVENT _T("LeaveExtTabEvent")
#define YGTEST_EVENT _T("YgTestEvent")
#define RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE						_T("Tencent.RTX.PlugInYgNotice")

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes

#import "../../../tlb/RTXCModuleInterface.tlb" no_namespace named_guids raw_interfaces_only
#import "../../../tlb/RTXCAPI.tlb" no_namespace named_guids 
#import "..\..\..\tlb\ClientObjects.tlb" no_namespace named_guids raw_interfaces_only
#import "..\PlugInYgNotice\Release\PlugInYgNotice.tlb" no_namespace named_guids


#include "../../../include/RTXCModuleIds.h"


#define RTX_EVENT_GET_INTERFACE			1
#define _RTXC_LOAD_MODULE_TIMER			100

#include "EventSinkInc.h"

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
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
//#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D858B409_EFD1_45A0_BC66_14C9843459CA__INCLUDED_)
