#include "pch.h"
#include "ConcurrentEventSubscriberFoo.h"

namespace Library
{
	ConcurrentEventSubscriberFoo::ConcurrentEventSubscriberFoo(EventQueue* eventQueue, GameTime* gameTime, std::uint32_t number) : mEventQueue(eventQueue), mGameTime(gameTime), mNumber(number), mMutex() {}

	std::uint32_t ConcurrentEventSubscriberFoo::GetNumber() const
	{
		return mNumber;
	}

	void ConcurrentEventSubscriberFoo::Notify(const EventPublisher* eventPublisher)
	{
		std::unique_lock<std::mutex> lock(mMutex);
		Event<std::uint32_t>* e = eventPublisher->As<Event<std::uint32_t>>();
		if (e != nullptr)
		{
			mNumber = e->Message();

			// enqueue another event once event queue is finished updating
			Event<std::uint32_t>* newEvent = new Event<std::uint32_t>(mNumber + 1, true);
			mEventQueue->Enqueue(newEvent, *mGameTime, 0.2f);
		}
	}
}