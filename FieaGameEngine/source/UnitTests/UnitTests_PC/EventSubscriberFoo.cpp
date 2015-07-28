#include "pch.h"
#include "EventSubscriberFoo.h"

namespace Library
{
	EventSubscriberFoo::EventSubscriberFoo(std::uint32_t number) : mNumber(number) {}

	std::uint32_t EventSubscriberFoo::GetNumber() const
	{
		return mNumber;
	}

	void EventSubscriberFoo::Notify(const EventPublisher* eventPublisher)
	{
		Event<std::uint32_t>* e = eventPublisher->As<Event<std::uint32_t>>();
		if (e != nullptr)
		{
			mNumber = e->Message();
		}
	}
}