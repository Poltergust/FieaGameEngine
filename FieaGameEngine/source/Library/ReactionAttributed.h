#pragma once

#include "Reaction.h"

namespace Library
{
	/**
	 * A class for attributed reactions.
	 */
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)

	public:
		/**
		 * The constructor.
		 * @param subtypeSize the size of the array of subtypes
		 */
		explicit ReactionAttributed(std::uint32_t subtypeSize = 10);

		/**
		 * The deleted copy constructor.
		 */
		ReactionAttributed(const ReactionAttributed& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		ReactionAttributed& operator=(const ReactionAttributed& rhs) = delete;

		/**
		 * The virtual destructor.
		 */
		virtual ~ReactionAttributed();

		/**
		 * Gets this attributed reaction's subtype at a specified index.
		 * @param index	the index into the subtype array
		 * @return the subtype at the specified index
		 */
		int GetSubtype(std::uint32_t index) const;

		/**
		 * Sets the subtype to the specified value at the specified index.
		 * @param subtype	the subtype to set
		 * @param index	the index into the subtype array
		 * @throws an exception if the index is greater than the subtype array size
		 */
		void SetSubtype(int subtype, std::uint32_t index);

		/**
		 * Handles the given event.
		 * @param eventPublisher the event to handle
		 */
		virtual void Notify(const EventPublisher* eventPublisher) override;

	private:
		int* mSubtype; /**< The subtype array of ints. */
		std::uint32_t mNumSubtypes; /**< The size of the subtype array. */

	public:
		ActionFactory(ReactionAttributed)
	};
}