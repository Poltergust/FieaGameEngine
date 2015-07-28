#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionPrint)

	ActionPrint::ActionPrint() : mString(std::string())
	{
		EXTERNAL_ATTRIBUTE(std::string("string"), Datum::String, 1, &mString);
		Populate();
	}

	const std::string& ActionPrint::String() const
	{
		return mString;
	}

	void ActionPrint::SetString(const std::string& string)
	{
		mString = string;
	}

	void ActionPrint::Update(WorldState& worldState)
	{
		worldState.mAction = this;
		
		std::cout << mString << std::endl;
	}
}