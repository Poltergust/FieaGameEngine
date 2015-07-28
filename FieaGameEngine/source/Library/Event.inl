#include "Event.h"

namespace Library
{
	template <typename ConcreteMessageType>
	RTTI_DEFINITIONS(Event<ConcreteMessageType>)

#pragma region Event
	template <typename ConcreteMessageType>
	SList<EventSubscriber*> Event<ConcreteMessageType>::sSubscribers;

	template <typename ConcreteMessageType>
	std::mutex Event<ConcreteMessageType>::sMutex;

	template <typename ConcreteMessageType>
	Event<ConcreteMessageType>::Event(const ConcreteMessageType& message, bool shouldDelete) : EventPublisher(sSubscribers, shouldDelete, sMutex), mMessage(message) {}

	template <typename ConcreteMessageType>
	void Event<ConcreteMessageType>::Subscribe(EventSubscriber& eventSubscriber)
	{
		std::unique_lock<std::mutex> lock(sMutex);
		if (sSubscribers.Find(&eventSubscriber) == sSubscribers.End())
			sSubscribers.PushBack(&eventSubscriber);
	}

	template <typename ConcreteMessageType>
	void Event<ConcreteMessageType>::Unsubscribe(EventSubscriber& eventSubscriber)
	{
		// this lock is broken for ReactionAttributed, for whatever reason
		//std::unique_lock<std::mutex> lock(sMutex);
		sSubscribers.Remove(&eventSubscriber);
	}

	template <typename ConcreteMessageType>
	void Event<ConcreteMessageType>::UnsubscribeAll()
	{
		std::unique_lock<std::mutex> lock(sMutex);
		sSubscribers.Clear();
	}

	template <typename ConcreteMessageType>
	const ConcreteMessageType& Event<ConcreteMessageType>::Message() const
	{
		return mMessage;
	}
#pragma endregion
}