// RTXEvent.cpp : Implementation of CRTXEvent
#include "stdafx.h"
#include "PlugInYgNotice.h"
#include "RTXEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CRTXEvent

STDMETHODIMP CRTXEvent::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRTXEvent
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CRTXEvent::OnEvent(BSTR recdata)
{
	Fire_OnModuleEvent(recdata);
}
