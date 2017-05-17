// YgTabFlash.cpp : Implementation of CYgTabFlashApp and DLL registration.

#include "stdafx.h"
#include "YgTabFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CYgTabFlashApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xf27c1818, 0xd0a6, 0x4e4e, { 0xb4, 0x27, 0xa5, 0x1f, 0x77, 0xae, 0x3c, 0xd7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CYgTabFlashApp::InitInstance - DLL initialization

BOOL CYgTabFlashApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CYgTabFlashApp::ExitInstance - DLL termination

int CYgTabFlashApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
	_trace(_T("YgTabFlash:DllRegisterServer"));
	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	_trace(_T("YgTabFlash:DllUnregisterServer"));
	return NOERROR;
}
