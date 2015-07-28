#pragma once

#include "Action.h"

namespace Library
{
	/**
	 * A class for event actions.
	 */
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)

	public:
		/**
		 * The constructor.
		 */
		explicit ActionEvent();

		/**
		 * The deleted copy constructor.
		 */
		ActionEvent(const ActionEvent& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		ActionEvent& operator=(const ActionEvent& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~ActionEvent() = default;

		/**
		 * Gets the subtype of this event.
		 * @return this event's subtype
		 */
		int GetSubtype() const;

		/**
		 * Sets this event's subtype.
		 * @param subtype the subtype to set
		 */
		void SetSubtype(int subtype);

		/**
		 * Gets the delay of this event, in seconds.
		 * @return this event's delay
		 */
		float GetDelay() const;

		/**
		 * Sets the delay of this event, in seconds.
		 * @param delay the amount of delay to set for this event
		 */
		void SetDelay(float delay);

		/**
		 * Updates the world state.
		 * @param worldState the world state to update
		 */
		virtual void Update(WorldState& worldState);

	private:
		int mSubtype; /**< The subtype of this event. */
		float mDelay; /**< The delay of this event. */

	public:
		ActionFactory(ActionEvent)
	};
}