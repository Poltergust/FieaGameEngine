#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include "ActionPrint.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "Event.h"
#include "GameClock.h"

namespace Library
{
	/**
	 * Forward declaration of the Sector class.
	 */
	class Sector;

	/**
	 * A class for the game world.
	 */
	class World : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		/**
		 * The constructor.
		 * @param name	the name of the world
		 */
		explicit World(const std::string& name);

		/**
		 * The deleted copy constructor.
		 */
		World(const World& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		World& operator=(const World& rhs) = delete;

		/**
		 * The default virtual destructor.
		 */
		virtual ~World();

		/**
		 * Returns the name of the world.
		 * @return the name of the world
		 */
		const std::string& Name() const;

		/**
		 * Sets the name of the world.
		 * @param name	the new name of the world
		 */
		void SetName(const std::string& name);

		/**
		 * Returns a pointer to the scope containing all the sectors.
		 * @return a pointer to the scope containing all the sectors
		 */
		Scope* Sectors() const;

		/**
		 * Creates a new sector within this world.
		 * @param sectorName	the name of the sector
		 * @throws an exception if RTTI conversion fails
		 * @return a pointer to the newly created sector
		 */
		Sector* CreateSector(const std::string& sectorName);

		/**
		 * Updates this world and all of its contained data.
		 * @param worldState	the WorldState object
		 */
		void Update();

		/**
		 * Gets this world's state.
		 * @return the world state
		 */
		WorldState* GetWorldState() const;

		/**
		 * Gets this world's event queue.
		 * @return this world's event queue
		 */
		EventQueue* GetEventQueue() const;

		ActionList::ActionListFactory mActionListFactory;
		ActionListIf::ActionListIfFactory mActionListIfFactory;
		ActionPrint::ActionPrintFactory mActionPrintFactory;
		ReactionAttributed::ReactionAttributedFactory mReactionAttributedFactory;
		ActionEvent::ActionEventFactory mActionEventFactory;

	private:
		std::string mName; /**< The name of the world. */
		Scope* mSectors; /**< The scope pointer containing all the sectors. */
		WorldState* mWorldState; /**< The world state. */
		EventQueue* mEventQueue; /**< The event queue. */
		GameClock* mGameClock; /**< The game clock that will update the world state. */
	};
}