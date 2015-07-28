#include "pch.h"
#include "XmlParseHelperFoo.h"

namespace Library
{
	RTTI_DEFINITIONS(XmlParseHelperFoo::SharedData)

#pragma region SharedData
	XmlParseHelperFoo::SharedData::SharedData() 
		: mIntData(0), mStartElementName(std::string()), mEndElementName(std::string()), mAttributeKey(std::string()), mAttributeValue(std::string()), mStartCalls(0), mEndCalls(0), mMaxDepth(0) {}

	void XmlParseHelperFoo::SharedData::Reset()
	{
		mIntData = 0;
		mStartElementName = std::string();
		mEndElementName = std::string();
		mAttributeKey = std::string();
		mAttributeValue = std::string();
		mStartCalls = 0;
		mEndCalls = 0;
		mMaxDepth = 0;
	}

	XmlParseHelperFoo::SharedData* XmlParseHelperFoo::SharedData::Clone() const
	{
		SharedData* clone = new SharedData();
		return clone;
	}

	int XmlParseHelperFoo::SharedData::GetIntData() const
	{
		return mIntData;
	}

	std::string XmlParseHelperFoo::SharedData::GetStartElementName() const
	{
		return mStartElementName;
	}

	std::string XmlParseHelperFoo::SharedData::GetEndElementName() const
	{
		return mEndElementName;
	}

	std::string XmlParseHelperFoo::SharedData::GetAttributeKey() const
	{
		return mAttributeKey;
	}

	std::string XmlParseHelperFoo::SharedData::GetAttributeValue() const
	{
		return mAttributeValue;
	}

	std::uint32_t XmlParseHelperFoo::SharedData::GetNumStartCalls() const
	{
		return mStartCalls;
	}

	std::uint32_t XmlParseHelperFoo::SharedData::GetNumEndCalls() const
	{
		return mEndCalls;
	}

	std::uint32_t XmlParseHelperFoo::SharedData::GetMaxDepth() const
	{
		return mMaxDepth;
	}
#pragma endregion

#pragma region XmlParseHelperFoo
	void XmlParseHelperFoo::Initialize() 
	{
		mStringHelperData.clear();
	}

	bool XmlParseHelperFoo::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr || elementName != std::string("integer"))
			return false;

		++derivedSharedData->mStartCalls;

		derivedSharedData->mStartElementName = elementName;

		// the data I'm passing in for tests will only contain up to one pair for now, so I'm just using begin() to get the iterator and then dereferencing it
		HashMap<std::string, std::string>::Iterator iterator = attributes.begin();
		if (iterator != attributes.end())
		{
			std::pair<std::string, std::string> pair = *iterator;
			derivedSharedData->mAttributeKey = pair.first;
			derivedSharedData->mAttributeValue = pair.second;
		}

		if (derivedSharedData->Depth() > derivedSharedData->mMaxDepth)
			derivedSharedData->mMaxDepth = derivedSharedData->Depth();

		return true;
	}

	bool XmlParseHelperFoo::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		++derivedSharedData->mEndCalls;

		derivedSharedData->mEndElementName = elementName;

		if (derivedSharedData->mStartElementName != derivedSharedData->mEndElementName)
			throw std::exception("Incorrect element names. Reformat your XML code.");

		int value = atoi(mStringHelperData.c_str());
		derivedSharedData->mIntData = value;

		return true;
	}

	bool XmlParseHelperFoo::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		mStringHelperData.append(s);

		return true;
	}

	XmlParseHelperFoo* XmlParseHelperFoo::Clone() const
	{
		XmlParseHelperFoo* clone = new XmlParseHelperFoo();
		return clone;
	}
#pragma endregion
}