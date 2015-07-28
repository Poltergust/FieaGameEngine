#pragma once

#include "Attributed.h"
#include "World.h"
#include "WorldState.h"

namespace Library
{
	/**
	 * Forward declaration of the Entity class.
	 */
	class Entity;

	/**
	 * A class for sectors within a world.
	 */
	class Sector : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		/**
		 * The constructor.
		 * @param name	the name of the sector
		 */
		explicit Sector(const std::string& name);

		/**
		 * The deleted copy constructor.
		 */
		Sector(const Sector& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		Sector& operator=(const Sector& rhs) = delete;

		/**
		 * The default virtual destructor.
		 */
		virtual ~Sector() = default;

		/**
		 * Returns the name of this sector.
		 * @return the name of this sector
		 */
		const std::string& Name() const;

		/**
		 * Returns a pointer to the scope containing all the entities
		 * @return a pointer to the scope containing all the entities
		 */
		Scope* Entities() const;

		/**
		 * Creates a new Entity object within this scope. Uses a factory to do so.
		 * @param className	the name of the concrete class to make an instance out of
		 * @param instanceName	the name of the Entity instance
		 * @throws an exception if RTTI conversion fails
		 * @return a pointer to the newly created entity
		 */
		Entity* CreateEntity(const std::string& className, const std::string& instanceName);

		/**
		 * Gets the world this sector is contained in
		 * @return a pointer to the world that contains this sector
		 */
		World* GetWorld() const;

		/**
		 * Adopts this sector into the given world.
		 * @param world	the pointer of the world for this sector to be adopted into
		 * @param index	the index into the sectors scope for this sector to be inserted into
		 */
		void SetWorld(World* world, std::uint32_t index);

		/**
		* Updates this sector and all of its contained data.
		* @param worldState	the WorldState object
		*/
		void Update(WorldState& worldState);

	private:
		std::string mName; /**< The name of this sector. */
		Scope* mEntities; /**< The scope containing all the entities for this sector. */
	};
}