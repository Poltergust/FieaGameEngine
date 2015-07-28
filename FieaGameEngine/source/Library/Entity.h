#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Sector.h"
#include "Factory.h"

namespace Library
{
	/**
	 * Forward declaration of the Action class.
	 */
	class Action;

	/**
	 * A class for entities within a sector.
	 */
	class Entity : public Attributed
	{
		/**
		 * This is needed for the Sector class to be able to change a newly created Entity's name.
		 */
		friend class Sector;

		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		/**
		 * The constructor.
		 */
		explicit Entity();

		/**
		 * The deleted copy constructor.
		 */
		Entity(const Entity& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		Entity& operator=(const Entity& rhs) = delete;

		/**
		 * The default virtual destructor.
		 */
		virtual ~Entity() = default;

		/**
		 * Gets the name of this entity.
		 * @return the name of this entity
		 */
		const std::string& Name() const;

		/**
		* Returns a pointer to the scope containing all the actions
		* @return a pointer to the scope containing all the actions
		*/
		Scope* Actions() const;

		/**
		* Creates a new Action object within this scope. Uses a factory to do so.
		* @param className	the name of the concrete class to make an instance out of
		* @param instanceName	the name of the Action instance
		* @throws an exception if RTTI conversion fails
		* @return a pointer to the newly created action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		 * Gets the sector that this entity is contained in.
		 * @return a pointer to the sector that this entity is contained in
		 */
		Sector* GetSector() const;

		/**
		 * Adopts this entity into the specified sector.
		 * @param sector	the pointer of the sector for this entity to be adopted into
		 * @param index		the index into the entities scope for this entity to be inserted into
		 */
		void SetSector(Sector* sector, std::uint32_t index);

		/**
		* Updates this entity and all of its contained data.
		* @param worldState	the WorldState object
		*/
		void Update(WorldState& worldState);

	private:
		std::string mName; /**< The name of this sector. */
		Scope* mActions; /**< The scope containing all the actions for this entity. */
	};
}