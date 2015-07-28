#pragma once

#include "Action.h"
#include <iostream>

namespace Library
{
	/**
	 * A class for the print action.
	 */
	class ActionPrint : public Action
	{
		RTTI_DECLARATIONS(ActionPrint, Action)

	public:

		/**
		 * The constructor.
		 */
		explicit ActionPrint();

		/**
		 * The deleted copy constructor.
		 */
		ActionPrint(const ActionPrint& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		ActionPrint& operator=(const ActionPrint& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~ActionPrint() = default;

		/**
		 * Returns the string of this action.
		 * @return the string of this action
		 */
		const std::string& String() const;

		/**
		 * Sets the string of this action.
		 * @param string the string to be set
		 */
		void SetString(const std::string& string);

		/**
		 * Updates the world state.
		 * @param worldState the worldState to update
		 */
		virtual void Update(WorldState& worldState);

	private:
		std::string mString;  /**< This action's string. */

	public:
		ActionFactory(ActionPrint)
	};
}