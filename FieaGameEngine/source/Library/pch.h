// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here

#include <Windows.h>
#include <chrono>
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>

#include "Foo.h"
#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"
#include "Attributed.h"
#include "AttributedFoo.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "XmlParseHelperTable.h"
#include "Factory.h"
#include "Entity.h"
#include "Sector.h"
#include "WorldState.h"
#include "World.h"
#include "XmlParseHelperWorld.h"
#include "XmlParseHelperSector.h"
#include "XmlParseHelperEntity.h"
#include "XmlParseHelperAction.h"
#include "GameTime.h"
#include "GameClock.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include "ActionPrint.h"
#include "Event.h"
#include "Reaction.h"
#include "EventMessageAttributed.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"