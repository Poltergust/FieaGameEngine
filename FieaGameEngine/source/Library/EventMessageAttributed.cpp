#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(EventMessageAttributed)

	EventMessageAttributed::EventMessageAttributed(int subtype, World* world) : mSubtype(subtype), mWorld(world) {}

	EventMessageAttributed::EventMessageAttributed(const EventMessageAttributed& rhs) : mSubtype(0), mWorld(nullptr)
	{
		operator=(rhs);
	}

	EventMessageAttributed& EventMessageAttributed::operator=(const EventMessageAttributed& rhs)
	{
		if (this != &rhs)
		{
			Attributed::operator=(rhs);
			mSubtype = rhs.mSubtype;
			mWorld = rhs.mWorld;
		}
		return *this;
	}

	int EventMessageAttributed::GetSubtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::SetSubtype(int subtype)
	{
		mSubtype = subtype;
	}

	World* EventMessageAttributed::GetWorld() const
	{
		return mWorld;
	}

	void EventMessageAttributed::SetWorld(World* world)
	{
		mWorld = world;
	}
}