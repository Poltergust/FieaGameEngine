#include "pch.h"

namespace Library
{
	void IXmlParseHelper::Initialize() {}

	bool IXmlParseHelper::CharDataHandler(SharedData* sharedData, const std::string& s, std::uint32_t len)
	{
		return false;
	}
}