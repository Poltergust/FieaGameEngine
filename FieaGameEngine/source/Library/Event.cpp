#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

#pragma region EventPublisher
	EventPublisher::EventPublisher(SList<EventSubscriber*>& subscribers, bool shouldDelete, std::mutex& mutex) : mSubscribersReference(subscribers), mShouldDelete(shouldDelete), mTimeEnqueued(), mDelay(0.0), mExpirationTime(), mTimeMutex(), mEventMutexReference(mutex) {}

	void EventPublisher::SetTime(const GameTime& currentTime, float delay)
	{
		std::unique_lock<std::mutex> lock(mTimeMutex);
		mTimeEnqueued = currentTime;
		mDelay = delay;
		mExpirationTime = mTimeEnqueued.TotalGameTime() + GameTime::Milliseconds(std::lround(mDelay * 1000));
	}

	const GameTime& EventPublisher::TimeEnqueued() const
	{
		std::unique_lock<std::mutex> lock(mTimeMutex);
		return mTimeEnqueued;
	}

	float EventPublisher::Delay() const
	{
		std::unique_lock<std::mutex> lock(mTimeMutex);
		return mDelay;
	}

	bool EventPublisher::IsExpired(const GameTime& currentTime) const
	{
		std::unique_lock<std::mutex> lock(mTimeMutex);
		if (currentTime.TotalGameTime() >= mExpirationTime)
		{
			return true;
		}
		return false;
	}

	void EventPublisher::Deliver()
	{
		std::vector<std::future<void>> futures;
		{
			std::unique_lock<std::mutex> lock(mEventMutexReference);
			for (Iterator iterator = mSubscribersReference.Begin(); iterator != mSubscribersReference.End(); ++iterator)
			{
				futures.emplace_back(std::async(std::launch::async, [](Iterator& iterator, EventPublisher* eventPublisher)
				{
					(*iterator)->Notify(eventPublisher);
				}, iterator, this));
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}
	}

	bool EventPublisher::DeleteAfterPublishing() const
	{
		return mShouldDelete;
	}
#pragma endregion

#pragma region EventQueue
	EventQueue::EventQueue() : mEvents(), mEventsToBeRemoved(), mIsUpdating(false), mMutex() {}

	void EventQueue::Enqueue(EventPublisher* eventPublisher, const GameTime& currentTime, float delay)
	{
		if (delay == 0.0f)
		{
			Send(eventPublisher, false);
			if (eventPublisher->DeleteAfterPublishing())
				delete eventPublisher;
		}
		else
		{
			// this method will need a lock since multiple Subscribers could be calling Enqueue at the same time
			std::unique_lock<std::recursive_mutex> lock(mMutex);

			eventPublisher->SetTime(currentTime, delay);
			mEvents.PushBack(eventPublisher);
		}
	}

	void EventQueue::Send(EventPublisher* eventPublisher, bool storeEvent)
	{
		eventPublisher->Deliver();

		// the reason this is a recursive mutex is due to the lock possibly being passed from Enqueue
		if (storeEvent)
		{
			std::unique_lock<std::recursive_mutex> lock(mMutex);
			mEventsToBeRemoved.PushBack(eventPublisher);
		}
	}

	void EventQueue::Update(const GameTime& currentTime)
	{
		std::vector<std::future<void>> futures;

		{
			if (mIsUpdating.exchange(true))
				return;

			std::unique_lock<std::recursive_mutex> lock(mMutex);
			
			for (Iterator iterator = mEvents.Begin(); iterator != mEvents.End(); ++iterator)
			{
				if ((*iterator)->IsExpired(currentTime))
					futures.emplace_back(std::async(std::launch::async, [this](Iterator& iterator)
				{
					Send(*iterator, true);
				}, iterator));
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}

		{
			std::unique_lock<std::recursive_mutex> lock(mMutex);
			for (Iterator iterator = mEventsToBeRemoved.Begin(); iterator != mEventsToBeRemoved.End(); ++iterator)
			{
				mEvents.Remove(*iterator);
				if ((*iterator)->DeleteAfterPublishing())
					delete *iterator;
			}
			mEventsToBeRemoved.Clear();

			mIsUpdating = false;
		}
	}

	void EventQueue::Clear(const GameTime& currentTime)
	{
		Update(currentTime);

		std::unique_lock<std::recursive_mutex> lock(mMutex);
		mEvents.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		std::unique_lock<std::recursive_mutex> lock(mMutex);
		return mEvents.IsEmpty();
	}

	std::uint32_t EventQueue::Count() const
	{
		std::unique_lock<std::recursive_mutex> lock(mMutex);
		return mEvents.Size();
	}

	bool EventQueue::IsUpdating() const
	{
		return mIsUpdating;
	}
#pragma endregion
}