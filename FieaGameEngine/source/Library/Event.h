#pragma once

#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include "RTTI.h"
#include "SList.h"
#include "GameTime.h"

namespace Library
{
	/**
	 * Forward declaration of EventPublisher.
	 */
	class EventPublisher;

	/**
	 * An abstract class for event subscribers.
	 */
	class EventSubscriber
	{
	public:
		/**
		 * The default constructor.
		 */
		explicit EventSubscriber() = default;

		/**
		 * The deleted copy constructor.
		 * @param rhs the EventSubscriber object to copy
		 */
		EventSubscriber(const EventSubscriber& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 * @param rhs the EventSubscriber object to copy
		 * @return a reference to the newly copied EventSubscriber
		 */
		EventSubscriber& operator=(const EventSubscriber& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~EventSubscriber() = default;

		/**
		 * Handle the given event. Pure virtual.
		 * @param eventPublisher the event to be handled
		 */
		virtual void Notify(const EventPublisher* eventPublisher) = 0;
	};

	/**
	 * A class for publishing events.
	 */
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:
		typedef SList<EventSubscriber*>::Iterator Iterator; /**< Typedef for the SList iterator. */

		/**
		 * The constructor.
		 * @param subscribers the list of subscribers
		 * @param shouldDelete a boolean telling whether the event should be deleted or not after being published
		 */
		explicit EventPublisher(SList<EventSubscriber*>& subscribers, bool shouldDelete, std::mutex& mutex);

		/**
		 * The deleted copy constructor.
		 * @param rhs the EventPublisher object to copy
		 */
		EventPublisher(const EventPublisher& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 * @param rhs the EventPublisher object to copy
		 * @return a reference to the newly copied EventPublisher
		 */
		EventPublisher& operator=(const EventPublisher& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~EventPublisher() = default;

		/**
		 * Sets the time values of this event.
		 * @param currentTime the current point in time when this event is enqueued
		 * @param delay how many seconds to delay before this event should be published
		 */
		void SetTime(const GameTime& currentTime, float delay = 0.0f);

		/**
		 * Gets the point in time when this event was enqueued.
		 * @return the point in time when this event was enqueued
		 */
		const GameTime& TimeEnqueued() const;

		/**
		 * Gets the amount of seconds that this event has been delayed.
		 * @return the amount of seconds that this event has been delayed
		 */
		float Delay() const;

		/**
		 * Tells whether this event is expired or not based on the current time
		 * @param currentTime the current point in time
		 * @return true if the event is expired, false otherwise
		 */
		bool IsExpired(const GameTime& currentTime) const;

		/**
		 * Publishes the event to all listed subscribers.
		 */
		void Deliver();

		/**
		 * Tells whether this event should be deleted after being published.
		 * @return true if the event should be deleted, false otherwise
		 */
		bool DeleteAfterPublishing() const;

	private:
		SList<EventSubscriber*>& mSubscribersReference; /**< The reference to the static subscribers list. */
		bool mShouldDelete; /**< Tells whether this event should be deleted after being published. */
		GameTime mTimeEnqueued; /**< The point in time that this event was enqueued. */
		float mDelay; /**< The amount of time in seconds that this event will be delayed before being published. */
		GameTime::Milliseconds mExpirationTime; /**< The time duration of this event before it expires, in milliseconds. */
		mutable std::mutex mTimeMutex; /**< This event publisher's mutex for its time method. */
		mutable std::mutex& mEventMutexReference; /**< The reference to the static event mutex. */
	};

	/**
	 * A class for events.
	 */
	template <typename ConcreteMessageType>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<ConcreteMessageType>, EventPublisher)

	public:
		/**
		 * The constructor.
		 * @param message the message object that this event will hold
		 * @param shouldDelete a boolean telling whether the event should be deleted or not after being published
		 */
		explicit Event(const ConcreteMessageType& message, bool shouldDelete);

		/**
		* The deleted copy constructor.
		* @param rhs the Event object to copy
		*/
		Event(const Event& rhs) = delete;

		/**
		* The deleted assignment operator.
		* @param rhs the Event object to copy
		* @return a reference to the newly copied Event
		*/
		Event& operator=(const Event& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~Event() = default;

		/**
		 * Pushes the specified event subscriber onto the static event subscriber list so that they will be notified of events.
		 * @param eventSubscriber the event subscriber to push
		 */
		static void Subscribe(EventSubscriber& eventSubscriber);

		/**
		 * Removes the specified event subscriber from the static event subscriber list.
		 * @param eventSubscriber the event subscriber to remove
		 */
		static void Unsubscribe(EventSubscriber& eventSubscriber);
		
		/**
		 * Removes all event subscribers from the static event subscriber list.
		 */
		static void UnsubscribeAll();

		/**
		 * Gets this event's message.
		 * @return the message object
		 */
		const ConcreteMessageType& Message() const;

	private:
		ConcreteMessageType mMessage; /**< The templated message object. */
		static SList<EventSubscriber*> sSubscribers; /**< The static event subscribers list. */
		static std::mutex sMutex; /**< The static mutex. */
	};

	/**
	 * A class for queueing events.
	 */
	class EventQueue
	{
	public:
		typedef SList<EventPublisher*>::Iterator Iterator; /**< Typedef for the SList iterator. */

		/**
		 * The constructor.
		 */
		explicit EventQueue();

		/**
		 * The deleted copy constructor.
		 * @param rhs the eventQueue object to copy
		 */
		EventQueue(const EventQueue& rhs) = delete;

		/**
		* The deleted assignment operator.
		* @param rhs the EventQueue object to copy
		* @return a reference to the newly copied EventQueue
		*/
		EventQueue& operator=(const EventQueue& rhs) = delete;

		/**
		 * The default destructor.
		 */
		~EventQueue() = default;

		/**
		 * Enqueue an event, or send it immediately if there is no delay.
		 * @param eventPublisher the event to push onto the queue, or send if there is no delay
		 * @param currentTime the current point in time
		 * @param delay the amount of time in seconds that this event should be delayed before sending
		 */
		void Enqueue(EventPublisher* eventPublisher, const GameTime& currentTime, float delay = 0.0f);

		/**
		 * Publish the specified event.
		 * @param eventPublisher the event to publish
		 * @param storeEvent a boolean telling whether to store this event within mEventsToBeRemoved
		 */
		void Send(EventPublisher* eventPublisher, bool storeEvent);

		/**
		 * Updates all events within the queue and publishes the ones that have expired.
		 * @param currentTime the current point in time
		 */
		void Update(const GameTime& currentTime);

		/**
		 * Publishes all expired events, then empties the event queue.
		 * @param currentTime the current point in time
		 */
		void Clear(const GameTime& currentTime);

		/**
		 * Tells if the event queue is empty.
		 * @return true if the event queue is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Gets the number of events in the event queue.
		 * @return the number of events in the event queue
		 */
		std::uint32_t Count() const;

		/**
		 * Gets whether this event queue is in the middle of updating or not.
		 * @return true if the event queue is updating, false otherwise
		 */
		bool IsUpdating() const;

	private:
		SList<EventPublisher*> mEvents; /**< The list of events to update on. */
		SList<EventPublisher*> mEventsToBeRemoved; /**< The list of events to be removed from mEvents. */
		std::atomic<bool> mIsUpdating; /**< Boolean telling if we have finished updating or not. */
		mutable std::recursive_mutex mMutex; /**< EventQueue's mutex. */
	};
}

#include "Event.inl"