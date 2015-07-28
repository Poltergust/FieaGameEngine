#pragma once

#include "ActionList.h"
#include "Event.h"

namespace Library
{
	/**
	 * A class for reactions.
	 */
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:
		/**
		 * The default constructor.
		 */
		explicit Reaction() = default;

		/**
		 * The deleted copy constructor.
		 */
		Reaction(const Reaction& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		Reaction& operator=(const Reaction& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~Reaction() = default;

		/**
		 * Handle the specified event. Pure virtual.
		 * @param eventPublisher the event to handle
		 */
		virtual void Notify(const EventPublisher* eventPublisher) = 0;
	};
}