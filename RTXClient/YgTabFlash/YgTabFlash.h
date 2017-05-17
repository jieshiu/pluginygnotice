#if !defined(AFX_YGTABFLASH_H__A9F9E26E_69C0_4996_ACFE_1DBAF871C85A__INCLUDED_)
#define AFX_YGTABFLASH_H__A9F9E26E_69C0_4996_ACFE_1DBAF871C85A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// YgTabFlash.h : main header file for YGTABFLASH.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashApp : See YgTabFlash.cpp for implementation.

class CYgTabFlashApp : public COleControlModule
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

#endif // !defined(AFX_YGTABFLASH_H__A9F9E26E_69C0_4996_ACFE_1DBAF871C85A__INCLUDED)
