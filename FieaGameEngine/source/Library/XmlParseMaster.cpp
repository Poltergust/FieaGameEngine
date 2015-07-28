#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

#pragma region SharedData
	XmlParseMaster::SharedData::SharedData() : mMaster(nullptr), mDepth(0) {}

	void XmlParseMaster::SharedData::Reset()
	{
		mDepth = 0;
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster* master)
	{
		mMaster = master;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
	{
		return mMaster;
	}

	void XmlParseMaster::SharedData::IncrementDepth()
	{
		++mDepth;
	}

	void XmlParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth <= 0)
			throw std::exception("Something went wrong with the decrementing. Depth should always be at least 1.");

		--mDepth;
	}

	std::uint32_t XmlParseMaster::SharedData::Depth() const
	{
		return mDepth;
	}
#pragma endregion

#pragma region XmlParseMaster
	XmlParseMaster::XmlParseMaster(SharedData& sharedData) : mParser(XML_ParserCreate("US-ASCII")), mSharedData(&sharedData), mHelpers(), mFile(), mIsClone(false)
	{
		mSharedData->SetXmlParseMaster(this);

		XML_SetElementHandler(mParser, reinterpret_cast<XML_StartElementHandler>(StartElementHandler), reinterpret_cast<XML_EndElementHandler>(EndElementHandler));
		XML_SetCharacterDataHandler(mParser, reinterpret_cast<XML_CharacterDataHandler>(CharDataHandler));
		XML_SetUserData(mParser, mSharedData);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mIsClone)
		{
			delete mSharedData;

			for (std::uint32_t i = 0; i < mHelpers.Size(); ++i)
				delete mHelpers[i];

		}
		XML_ParserFree(mParser);
	}

	void XmlParseMaster::ResetParser()
	{
		for (std::uint32_t i = 0; i < mHelpers.Size(); ++i)
			mHelpers[i]->Initialize();

		XML_ParserReset(mParser, nullptr);
		XML_SetElementHandler(mParser, reinterpret_cast<XML_StartElementHandler>(StartElementHandler), reinterpret_cast<XML_EndElementHandler>(EndElementHandler));
		XML_SetCharacterDataHandler(mParser, reinterpret_cast<XML_CharacterDataHandler>(CharDataHandler));
		XML_SetUserData(mParser, mSharedData);
		mFile.clear();
	}

	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster* clone = new XmlParseMaster(*mSharedData->Clone());

		for (std::uint32_t i = 0; i < mHelpers.Size(); ++i)
		{
			clone->mHelpers.PushBack(mHelpers[i]->Clone());
		}

		clone->mIsClone = true;
		return clone;
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		mHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		mHelpers.Remove(&helper);
	}

	void XmlParseMaster::Parse(const char* s, std::uint32_t len, bool isFinal)
	{
		XML_Status status = XML_Parse(mParser, s, len, isFinal);
		if (status == XML_STATUS_ERROR)
			throw std::exception("Error when parsing string.");
	}
	
	// will be refactored to read line by line once we get into nested XML statements
	void XmlParseMaster::ParseFromFile(const std::string& filename)
	{
		std::ifstream input(filename);
		mFile = filename;
		std::stringstream buffer;
		buffer << input.rdbuf();
		input.close();

		std::string inputString(buffer.str());
		Parse(inputString.c_str(), inputString.length(), true);
	}

	const std::string& XmlParseMaster::GetFileName() const
	{
		return mFile;
	}

	XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
	{
		return mSharedData;
	}

	void XmlParseMaster::SetSharedData(SharedData* sharedData)
	{
		if (sharedData != nullptr)
		{
			if (mSharedData != nullptr)
			{
				if (mIsClone)
					delete mSharedData;
				else
					mSharedData->SetXmlParseMaster(nullptr);
			}
			mSharedData = sharedData;
			mSharedData->SetXmlParseMaster(this);
			XML_SetUserData(mParser, mSharedData);
		}
	}

	void XmlParseMaster::StartElementHandler(void* userData, const XML_Char* elementName, const XML_Char** attributes)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* master = sharedData->GetXmlParseMaster();
		if (master == nullptr)
			return;

		HashMap<std::string, std::string> attHashMap(20);

		for (std::uint32_t i = 0; attributes[i] != nullptr; i += 2)
		{
			std::string key = attributes[i];
			std::string value = attributes[i + 1];
			attHashMap.Insert(std::pair<std::string, std::string>(key, value));
		}

		sharedData->IncrementDepth();

		for (std::uint32_t i = 0; i < master->mHelpers.Size(); ++i)
		{
			if (master->mHelpers[i]->StartElementHandler(sharedData, elementName, attHashMap))
				break;
		}
	}

	void XmlParseMaster::EndElementHandler(void* userData, const XML_Char* elementName)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* master = sharedData->GetXmlParseMaster();
		
		if (master == nullptr)
			return;

		sharedData->DecrementDepth();

		for (std::uint32_t i = 0; i < master->mHelpers.Size(); ++i)
		{
			if (master->mHelpers[i]->EndElementHandler(sharedData, elementName))
				break;
		}
	}

	void XmlParseMaster::CharDataHandler(void* userData, const XML_Char* s, std::uint32_t len)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* master = sharedData->GetXmlParseMaster();

		if (master == nullptr)
			return;

		for (std::uint32_t i = 0; i < master->mHelpers.Size(); ++i)
		{
			if (master->mHelpers[i]->CharDataHandler(sharedData, s, len))
				break;
		}
	}
#pragma endregion
}