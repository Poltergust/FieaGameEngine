#include "pch.h"

namespace Library
{
#pragma region XmlParseHelperSector
	void XmlParseHelperSector::Initialize() {}

	bool XmlParseHelperSector::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != std::string("sector"))
			return false;

		World* w = derivedSharedData->mScope->As<World>();
		if (w == nullptr)
			return false;

		++derivedSharedData->mStartCalls;

		// the data I'm passing in for tests will only contain up to one pair for now, so I'm just using begin() to get the iterator and then dereferencing it
		HashMap<std::string, std::string>::Iterator iterator = attributes.begin();
		if (iterator != attributes.end())
		{
			std::pair<std::string, std::string> pair = *iterator;
			derivedSharedData->mAttributeKey = pair.first;
			derivedSharedData->mAttributeValue = pair.second;
		}
		else
		{
			derivedSharedData->mAttributeKey = std::string();
			derivedSharedData->mAttributeValue = std::string();
		}

		if (derivedSharedData->Depth() > derivedSharedData->mMaxDepth)
			derivedSharedData->mMaxDepth = derivedSharedData->Depth();

		Sector* s = (derivedSharedData->mAttributeKey == std::string()) ?
			w->CreateSector(std::string("Sector")) : w->CreateSector(derivedSharedData->mAttributeKey);

		derivedSharedData->mScope = s;

		return true;
	}

	bool XmlParseHelperSector::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != "sector")
			return false;

		++derivedSharedData->mEndCalls;

		if (derivedSharedData->mScope->As<Sector>()->GetWorld() != nullptr)
			derivedSharedData->mScope = derivedSharedData->mScope->As<Sector>()->GetWorld();
		else
			return false;

		Initialize();

		return true;
	}

	bool XmlParseHelperSector::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		return false;
	}

	XmlParseHelperSector* XmlParseHelperSector::Clone() const
	{
		return new XmlParseHelperSector();
	}
#pragma endregion
}