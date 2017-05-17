#pragma once

#include "..\..\..\Include\RTXCEventSink.cpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_IMPLEMENT_EVENT_SINK(RTXEvent, DIID__IRTXEventEvents)
IMPLEMENT_EVENT(RTXEvent, 1, OnModuleEvent, "OnModuleEvent", VT_EMPTY, VTS_BSTR)	
END_IMPLEMENT_EVENT_SINK()