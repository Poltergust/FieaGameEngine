#pragma once

#include "ActionList.h"

namespace Library
{
	/**
	 * A class for the if action.
	 */
	class ActionListIf : public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf, ActionList)

	public:
		/**
		 * The constructor.
		 */
		explicit ActionListIf();

		/**
		 * The deleted copy constructor.
		 */
		ActionListIf(const ActionListIf& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		ActionListIf& operator=(const ActionListIf& rhs) = delete;

		/**
		 * The default virtual destructor.
		 */
		virtual ~ActionListIf() = default;

		/**
		 * Gets the condition value of this if action.
		 * @return the condition value of this if action
		 */
		int Condition() const;

		/**
		 * Sets the condition value.
		 * @param condition the condition value to be set
		 */
		void SetCondition(int condition);

		/**
		 * Gets the then action list as a scope.
		 * @return the then action list
		 */
		Scope* ThenAction() const;

		/**
		 * Creates a then action.
		 * @param className the name of the action class
		 * @param instanceName the name of the instance
		 * @return the newly created Action
		 */
		Action* CreateThenAction(const std::string& className, const std::string& instanceName);

		/**
		 * Gets the else action list as a scope.
		 * @return the else action list
		 */
		Scope* ElseAction() const;

		/**
		* Creates an else action.
		* @param className the name of the action class
		* @param instanceName the name of the instance
		* @return the newly created Action
		*/
		Action* CreateElseAction(const std::string& className, const std::string& instanceName);

		/**
		 * Updates the world state.
		 * @param worldState the world state to update
		 */
		virtual void Update(WorldState& worldState);

		bool mEnteredThen; /**< A test variable that tells if the then action list was entered. This will not be an attribute. */
		bool mEnteredElse; /**< A test variable that tells if the else action list was entered. This will not be an attribute. */

	private:
		int mConditionValue; /**< The condition value. */
		Scope* mThenAction; /**< The then action list. */
		Scope* mElseAction; /**< The else action list. */

	public:
		ActionFactory(ActionListIf)
	};
}