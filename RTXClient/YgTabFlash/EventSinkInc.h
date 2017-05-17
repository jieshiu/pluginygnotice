#pragma once

#include "..\..\..\Include\RTXCEventSink.h"

BEGIN_EVENT_SINK(RTXEvent)
_EVENT_(OnModuleEvent, (BSTR bstrdata), (bstrdata));
END_EVENT_SINK()
