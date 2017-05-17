// PlugInYgNotice.h : main header file for the PLUGINYGNOTICE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "PlugInYgNotice_i.h"

/////////////////////////////////////////////////////////////////////////////
// CPlugInYgNoticeApp
// See PlugInYgNotice.cpp for the implementation of this class
//

class CPlugInYgNoticeApp : public CWinApp
{
public:
	CPlugInYgNoticeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlugInYgNoticeApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPlugInYgNoticeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
