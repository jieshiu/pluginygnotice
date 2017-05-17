#if !defined(AFX_YGMSGMGROCX_H__483DC726_9030_4051_BEE2_CAA15D65283A__INCLUDED_)
#define AFX_YGMSGMGROCX_H__483DC726_9030_4051_BEE2_CAA15D65283A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// YgMsgMgrOcx.h : main header file for YGMSGMGROCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxApp : See YgMsgMgrOcx.cpp for implementation.

class CYgMsgMgrOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGMSGMGROCX_H__483DC726_9030_4051_BEE2_CAA15D65283A__INCLUDED)
