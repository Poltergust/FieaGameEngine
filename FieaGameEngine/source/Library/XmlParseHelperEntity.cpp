#include "pch.h"

namespace Library
{
#pragma region XmlParseHelperEntity
	void XmlParseHelperEntity::Initialize() {}

	bool XmlParseHelperEntity::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != std::string("entity"))
			return false;

		Sector* s = derivedSharedData->mScope->As<Sector>();
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

		Entity* e = s->CreateEntity(className, instanceName);

		derivedSharedData->mScope = e;

		return true;
	}

	bool XmlParseHelperEntity::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != "entity")
			return false;

		++derivedSharedData->mEndCalls;

		if (derivedSharedData->mScope->As<Entity>()->GetSector() != nullptr)
			derivedSharedData->mScope = derivedSharedData->mScope->As<Entity>()->GetSector();
		else
			return false;

		Initialize();

		return true;
	}

	bool XmlParseHelperEntity::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		return false;
	}

	XmlParseHelperEntity* XmlParseHelperEntity::Clone() const
	{
		return new XmlParseHelperEntity();
	}
#pragma endregion
}