#include "pch.h"

namespace Library
{
#pragma region XmlParseHelperWorld
	XmlParseHelperWorld::XmlParseHelperWorld() : mIndex(0) {} 

	void XmlParseHelperWorld::Initialize() {}

	bool XmlParseHelperWorld::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != std::string("world"))
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

		World* w = (derivedSharedData->mAttributeKey == std::string()) ?
			new World(std::string("World")) : new World(derivedSharedData->mAttributeKey);

		derivedSharedData->mScope->Adopt(*w, "Universe", mIndex++);
		derivedSharedData->mScope = w;

		return true;
	}

	bool XmlParseHelperWorld::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName != "world")
			return false;

		++derivedSharedData->mEndCalls;

		if (derivedSharedData->mScope->GetParent() != nullptr)
			derivedSharedData->mScope = derivedSharedData->mScope->GetParent();
		else
			return false;

		Initialize();

		return true;
	}

	bool XmlParseHelperWorld::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		return false;
	}

	XmlParseHelperWorld* XmlParseHelperWorld::Clone() const
	{
		return new XmlParseHelperWorld();
	}
#pragma endregion
}