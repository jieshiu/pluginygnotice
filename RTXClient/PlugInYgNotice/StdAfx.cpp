// stdafx.cpp : source file that includes just the standard includes
//	PlugInYgNotice.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include "RTXCEventSinkImp.h"
#include "ClientObjectsEventSinkImp.h"

HMODULE g_hPlugInYgNoticeModule = NULL;



	#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif
#include <atlimpl.cpp>

