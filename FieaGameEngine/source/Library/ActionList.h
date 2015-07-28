#pragma once

#include "Action.h"

namespace Library
{
	/**
	 * A class for action lists.
	 */
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

		/**
		 * The constructor.
		 */
		explicit ActionList();

		/**
		 * The deleted copy constructor.
		 */
		ActionList(const ActionList& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		ActionList& operator=(const ActionList& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~ActionList() = default;

		/**
		 * Gets the contained actions of this action list
		 * @return the contained actions
		 */
		Scope* ContainedActions() const;

		/**
		 * Creates an action and adds it to the list.
		 * @param className the name of the action class
		 * @param instanceName the name of the instance
		 * @throws an exception if RTTI conversion fails
		 * @return the newly created action
		 */
		Action* CreateActionForList(const std::string& className, const std::string& instanceName);

		/**
		 * Updates the world state.
		 * @param worldState the world state to update
		 */
		virtual void Update(WorldState& worldState);
	
	private:
		Scope* mContainedActions; /**< The actions this list contains (along with any other relevant attributes). */

	public:
		ActionFactory(ActionList)
	};
}