#if !defined(AFX_STDAFX_H__3FCEACE5_816B_48FB_86EC_A8D10C6FA930__INCLUDED_)
#define AFX_STDAFX_H__3FCEACE5_816B_48FB_86EC_A8D10C6FA930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

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
//#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3FCEACE5_816B_48FB_86EC_A8D10C6FA930__INCLUDED_)
