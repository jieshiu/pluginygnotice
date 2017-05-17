// RTXEvent.h : Declaration of the CRTXEvent

#ifndef __RTXEVENT_H_
#define __RTXEVENT_H_

#include "resource.h"       // main symbols
#include "PlugInYgNoticeCP.h"

/////////////////////////////////////////////////////////////////////////////
// CRTXEvent
class ATL_NO_VTABLE CRTXEvent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTXEvent, &CLSID_RTXEvent>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CRTXEvent>,
	public IDispatchImpl<IRTXEvent, &IID_IRTXEvent, &LIBID_PlugInYgNotice>,
	public CProxy_IRTXEventEvents< CRTXEvent >
{
public:
	CRTXEvent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RTXEVENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRTXEvent)
	COM_INTERFACE_ENTRY(IRTXEvent)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CRTXEvent)
CONNECTION_POINT_ENTRY(DIID__IRTXEventEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRTXEvent
public:
	void OnEvent(BSTR recdata);
};

#endif //__RTXEVENT_H_
