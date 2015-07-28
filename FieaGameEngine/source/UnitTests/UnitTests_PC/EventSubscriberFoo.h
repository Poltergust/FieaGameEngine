#pragma once

#include "Event.h"

namespace Library
{
	class EventSubscriberFoo : public EventSubscriber
	{
	public:
		explicit EventSubscriberFoo(std::uint32_t number = 0);
		EventSubscriberFoo(const EventSubscriberFoo& rhs) = delete;
		EventSubscriberFoo& operator=(const EventSubscriberFoo& rhs) = delete;
		virtual ~EventSubscriberFoo() = default;

		virtual void Notify(const EventPublisher* eventPublisher);
		std::uint32_t GetNumber() const;

	private:
		std::uint32_t mNumber;
	};
}