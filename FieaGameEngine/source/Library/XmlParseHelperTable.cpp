#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(XmlParseHelperTable::SharedData)

	static const char* TypeStrings[] = { "Unknown", "Integer", "Float", "Vector", "Matrix", "Table", "String", "Pointer" };
#pragma region SharedData
	XmlParseHelperTable::SharedData::SharedData(Scope* scope) : mScope(scope), mGrandScope(scope), mAttributeKey(std::string()), mAttributeValue(std::string()), mCharData(std::string()),
																mStartCalls(0), mEndCalls(0), mMaxDepth(0) {}

	void XmlParseHelperTable::SharedData::Reset()
	{
		mGrandScope->Clear();
		mScope = mGrandScope;
		mAttributeKey = std::string();
		mAttributeValue = std::string();
		mCharData = std::string();
		mStartCalls = 0;
		mEndCalls = 0;
		mMaxDepth = 0;
	}

	XmlParseHelperTable::SharedData* XmlParseHelperTable::SharedData::Clone() const
	{
		return new SharedData(mGrandScope);
	}

	Scope* XmlParseHelperTable::SharedData::GetScopeData() const
	{
		return mScope;
	}

	Scope* XmlParseHelperTable::SharedData::GetGrandScope() const
	{
		return mGrandScope;
	}

	std::string XmlParseHelperTable::SharedData::GetAttributeKey() const
	{
		return mAttributeKey;
	}

	std::string XmlParseHelperTable::SharedData::GetAttributeValue() const
	{
		return mAttributeValue;
	}

	std::string XmlParseHelperTable::SharedData::GetCharData() const
	{
		return mCharData;
	}

	std::uint32_t XmlParseHelperTable::SharedData::GetNumStartCalls() const
	{
		return mStartCalls;
	}

	std::uint32_t XmlParseHelperTable::SharedData::GetNumEndCalls() const
	{
		return mEndCalls;
	}

	std::uint32_t XmlParseHelperTable::SharedData::GetMaxDepth() const
	{
		return mMaxDepth;
	}
#pragma endregion

#pragma region XmlParseHelperTable
	XmlParseHelperTable::XmlParseHelperTable() : mParsingType(Unknown) {}

	void XmlParseHelperTable::Initialize()
	{
		mParsingType = Unknown;
	}

	bool XmlParseHelperTable::StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		if (elementName == std::string("integer"))
			mParsingType = Integer;
		else if (elementName == std::string("float"))
			mParsingType = Float;
		else if (elementName == std::string("vector"))
			mParsingType = Vector;
		else if (elementName == std::string("matrix"))
			mParsingType = Matrix;
		else if (elementName == std::string("scope"))
			mParsingType = Table;
		else if (elementName == std::string("string"))
			mParsingType = String;
		else if (elementName == std::string("pointer"))
			mParsingType = Pointer;
		
		if (mParsingType == Unknown)
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

		if (mParsingType == Table)
		{
			Scope& s = (derivedSharedData->mAttributeKey == std::string()) ?
				derivedSharedData->mScope->AppendScope(std::string(TypeStrings[mParsingType])) : derivedSharedData->mScope->AppendScope(derivedSharedData->mAttributeKey);

			derivedSharedData->mScope = &s;
		}

		return true;
	}

	bool XmlParseHelperTable::EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		++derivedSharedData->mEndCalls;

		// unlike the other parsing types, scopes have variable length and get set in the begin handler, so all this should do is traverse through the nest since we reached the end of the scope
		if (elementName == std::string("scope"))
		{
			if (derivedSharedData->mScope->GetParent() != nullptr)
				derivedSharedData->mScope = derivedSharedData->mScope->GetParent();
		}
		else
		{
			Datum& d = (derivedSharedData->mAttributeKey == std::string()) ?
				derivedSharedData->mScope->Append(std::string(TypeStrings[mParsingType])) : derivedSharedData->mScope->Append(derivedSharedData->mAttributeKey);

			int index = 0;
			if (derivedSharedData->mAttributeValue != std::string() && IsStringNumber(derivedSharedData->mAttributeValue))
				index = atoi(derivedSharedData->mAttributeValue.c_str());
			
			d.SetType(static_cast<Datum::DatumType>(mParsingType));
			d.SetFromString(derivedSharedData->mCharData, index);
		}

		Initialize();

		return true;
	}

	bool XmlParseHelperTable::CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		SharedData* derivedSharedData = sharedData->As<SharedData>();

		if (derivedSharedData == nullptr)
			return false;

		std::string charData(s.c_str(), len);
		derivedSharedData->mCharData = charData;

		return true;
	}

	XmlParseHelperTable* XmlParseHelperTable::Clone() const
	{
		return new XmlParseHelperTable();
	}

	bool XmlParseHelperTable::IsStringNumber(const std::string& s) const
	{
		for (std::string::const_iterator iterator = s.begin(); iterator != s.end(); ++iterator)
		{
			if (!std::isdigit(*iterator))
				return false;
		}
		return true;
	}
#pragma endregion
}