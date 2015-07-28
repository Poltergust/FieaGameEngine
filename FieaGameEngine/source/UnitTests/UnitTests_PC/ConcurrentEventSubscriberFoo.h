#pragma once

#include "Event.h"

namespace Library
{
	class ConcurrentEventSubscriberFoo : public EventSubscriber
	{
	public:
		explicit ConcurrentEventSubscriberFoo(EventQueue* eventQueue, GameTime* gameTime, std::uint32_t mNumber = 0);
		ConcurrentEventSubscriberFoo(const ConcurrentEventSubscriberFoo& rhs) = delete;
		ConcurrentEventSubscriberFoo& operator=(const ConcurrentEventSubscriberFoo& rhs) = delete;
		virtual ~ConcurrentEventSubscriberFoo() = default;

		std::uint32_t GetNumber() const;
		virtual void Notify(const EventPublisher* eventPublisher);

	private:
		EventQueue* mEventQueue;
		GameTime* mGameTime;
		std::uint32_t mNumber;
		std::mutex mMutex;
	};
}