#include "pch.h"

namespace Library
{
#pragma region XmlParseHelperAction
	void XmlParseHelperAction::Initialize() {}

	bool XmlParseHelperAction::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != std::string("action"))
			return false;

		Scope* s = nullptr;
		if (derivedSharedData->mScope->Is("Entity"))
			s = derivedSharedData->mScope->As<Entity>();
		else if (derivedSharedData->mScope->Is("ActionListIf"))
			s = derivedSharedData->mScope->As<ActionListIf>();
		else if (derivedSharedData->mScope->Is("ActionList"))
			s = derivedSharedData->mScope->As<ActionList>();

		if (s == nullptr)
			return false;

		HashMap<std::string, std::string>::Iterator iterator = attributes.begin();
		if (iterator != attributes.end())
		{
			std::pair<std::string, std::string> pair = *iterator;
			derivedSharedData->mAttributeKey = pair.first;
			derivedSharedData->mAttributeValue = pair.second;
		}
		else
		{
			return false;
		}

		std::string className = derivedSharedData->mAttributeValue;

		++iterator;
		if (iterator != attributes.end())
		{
			std::pair<std::string, std::string> pair = *iterator;
			derivedSharedData->mAttributeKey = pair.first;
			derivedSharedData->mAttributeValue = pair.second;
		}
		else
		{
			return false;
		}

		std::string instanceName = derivedSharedData->mAttributeValue;

		++derivedSharedData->mStartCalls;

		if (derivedSharedData->Depth() > derivedSharedData->mMaxDepth)
			derivedSharedData->mMaxDepth = derivedSharedData->Depth();

		Action* a = nullptr;
		if (s->Is("Entity"))
			a = s->As<Entity>()->CreateAction(className, instanceName);
		else
		{
			if (s->Is("ActionListIf"))
			{
				if (instanceName == "then")
					a = s->As<ActionListIf>()->CreateThenAction(className, instanceName);
				else
					a = s->As<ActionListIf>()->CreateElseAction(className, instanceName);
			}
			else
			{
				a = s->As<ActionList>()->CreateActionForList(className, instanceName);
			}
		}

		derivedSharedData->mScope = a;

		return true;
	}

	bool XmlParseHelperAction::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != "action")
			return false;

		++derivedSharedData->mEndCalls;

		if (derivedSharedData->mScope->Is("ActionPrint"))
			derivedSharedData->mScope->As<ActionPrint>()->SetString(derivedSharedData->mCharData);

		if (derivedSharedData->mScope->As<Action>()->GetContainingAction() != nullptr)
			derivedSharedData->mScope = derivedSharedData->mScope->As<Action>()->GetContainingAction();
		else if (derivedSharedData->mScope->As<Action>()->GetEntity() != nullptr)
			derivedSharedData->mScope = derivedSharedData->mScope->As<Action>()->GetEntity();
		else
			return false;

		Initialize();

		return true;
	}

	bool XmlParseHelperAction::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		return false;
	}

	XmlParseHelperAction* XmlParseHelperAction::Clone() const
	{
		return new XmlParseHelperAction();
	}
#pragma endregion
}