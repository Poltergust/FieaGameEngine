#pragma once

#include "World.h"

namespace Library
{
	/**
	 * A class for attributed event messages.
	 */
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)

	public:
		/**
		 * The constructor.
		 * @param the subtype this event will correspond to
		 * @param the world pointer
		 */
		explicit EventMessageAttributed(int subtype = 0, World* world = nullptr);

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs the EventMessageAttributed object to copy
		 */
		EventMessageAttributed(const EventMessageAttributed& rhs);

		/**
		 * The assignment operator. Performs a deep copy.
		 * @param rhs the EventMessageAttributed object to copy
		 * @return a reference to the newly copied EventMessageAttributed object
		 */
		EventMessageAttributed& operator=(const EventMessageAttributed& rhs);

		/**
		 * The virtual default destructor.
		 */
		virtual ~EventMessageAttributed() = default;

		/**
		 * Gets this message's subtype.
		 * @return this message's subtype.
		 */
		int GetSubtype() const;

		/**
		 * Sets this message's subtype.
		 * @param subtype the subtype to set
		 */
		void SetSubtype(int subtype);

		/**
		 * Gets the world pointer.
		 * @return the world pointer
		 */
		World* GetWorld() const;

		/**
		 * Sets the world pointer.
		 * @param world the world pointer
		 */
		void SetWorld(World* world);

	private:
		int mSubtype; /**< The int subtype. */
		World* mWorld; /**< The world pointer. */
	};
}