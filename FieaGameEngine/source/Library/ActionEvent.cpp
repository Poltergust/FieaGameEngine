#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionEvent)

	ActionEvent::ActionEvent() : mSubtype(0), mDelay(0)
	{
		EXTERNAL_ATTRIBUTE(std::string("subtype"), Datum::Integer, 1, &mSubtype);
		EXTERNAL_ATTRIBUTE(std::string("delay"), Datum::Float, 1, &mDelay);
		Populate();
	}

	int ActionEvent::GetSubtype() const
	{
		return mSubtype;
	}

	void ActionEvent::SetSubtype(int subtype)
	{
		mSubtype = subtype;
	}

	float ActionEvent::GetDelay() const
	{
		return mDelay;
	}

	void ActionEvent::SetDelay(float delay)
	{
		mDelay = delay;
	}

	void ActionEvent::Update(WorldState& worldState)
	{
		EventMessageAttributed e(mSubtype, worldState.mWorld);
		
		Iterator iterator = begin();
		for (std::uint32_t counterToAuxiliaryBegin = 0; counterToAuxiliaryBegin != AuxiliaryBegin(); ++counterToAuxiliaryBegin)
		{
			++iterator;
		}

		while (iterator != end())
		{
			e.AppendAuxiliaryAttribute((*iterator)->first) = (*iterator)->second;
			++iterator;
		}
		Event<EventMessageAttributed>* newEvent = new Event<EventMessageAttributed>(e, true);

		worldState.mWorld->GetEventQueue()->Enqueue(newEvent, worldState.GetGameTime(), mDelay);
	}
}