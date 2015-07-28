#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Entity.h"
#include "Factory.h"

namespace Library
{
	/**
	 * Forward declaration of the ActionList class, as this action may be contained within an ActionList instead of an Entity.
	 */
	class ActionList;

	/**
	 * A class for actions.
	 */
	class Action : public Attributed
	{
		/**
		 * Entity would benefit from having access to Action's private members.
		 */
		friend class Entity;

		RTTI_DECLARATIONS(Action, Attributed)

	public:
		/**
		 * The constructor.
		 */
		explicit Action();

		/**
		 * The deleted copy constructor.
		 */
		Action(const Action& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		Action& operator=(const Action& rhs) = delete;

		/**
		 * The virtual default destructor.
		 */
		virtual ~Action() = default;

		/**
		 * Gets the name of this action.
		 * @return the name of this action
		 */
		const std::string& Name() const;

		/**
		 * Sets the name of this action.
		 * @param the name of this action
		 */
		void SetName(const std::string& name);

		/**
		 * Gets the entity this action is contained in (if applicable).
		 * @return the address of the entity that contains this action, or nullptr if it is not contained in any entity (which is possible if I wish to extend the functionality of actions in the future)
		 */
		Entity* GetEntity() const;

		/**
		 * Gets the action list that contains this action (if applicable).
		 * @returns the address of the action list that contains this action, or nullptr if it is not contained in any action list
		 */
		ActionList* GetContainingAction() const;

		/**
		 * Adopts this action into the specified entity
		 * @param entity the pointer to the entity that will adopt this action
		 * @param index	the index to adopt this action to
		 */
		void SetEntity(Entity* entity, std::uint32_t index);

		/**
		* Adopts this action into the specified action list
		* @param entity the pointer to the action list that will adopt this action
		* @param index	the index to adopt this action to
		*/
		void SetActionList(ActionList* action, std::uint32_t index);

		/**
		 * Update the world state. Pure virtual.
		 * @param worldState the world state to update
		 */
		virtual void Update(WorldState& worldState) = 0;

	private:
		std::string mName; /**< The name of this action. */

	public:
		#define ActionFactory(ConcreteProductType) ConcreteFactory(ConcreteProductType, Action)
	};
}