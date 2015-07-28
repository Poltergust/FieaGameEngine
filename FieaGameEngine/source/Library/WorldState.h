#pragma once

namespace Library
{
	/**
	 * Forward declaration of the GameTime class.
	 */
	class GameTime;

	/**
	 * A class for holding information on the state of the world.
	 */
	class WorldState
	{
	public:
		class Entity* mEntity; /**< Address of the Entity currently being processed. */
		class Sector* mSector; /**< Address of the Sector currently being processed. */
		class World* mWorld; /**< Address of the World currently being processed. */
		class Action* mAction; /**< Address of the Action currently being processed. */

		/**
		 * The constructor.
		 */
		explicit WorldState();

		/**
		 * The destructor.
		 */
		~WorldState();

		/**
		 * Gets the current game time.
		 * @return the current game time
		 */
		GameTime& GetGameTime() const;

		/**
		 * Sets the game time to the given time.
		 * @param gameTime	the time to set the game time to
		 */
		void SetGameTime(GameTime& gameTime);

	private:
		GameTime* mGameTime; /**< The GameTime object that will hold relevant information on the game time. */
	};
}