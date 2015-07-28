#pragma once

#include <cstdint>
#include <iostream>
#include <exception>
#include "SList.h"
#include "Vector.h"

// vector<SList<std::pair<TKey, TData> > >

namespace Library
{
	const std::uint32_t hashPrime = 17;  /**< An arbitrarily chosen prime number for the hash functor. */

	/**
	 * A functor for hashing.
	 */
	template <typename T>
	class DefaultHash
	{
	public:
		/**
		 * The function operator. Performs a hash based on a key.
		 * @param key	the key to hash
		 * @return A hash for the key 
		 */
		std::uint32_t operator()(const T& key) const;
	};

	/**
	 * A class for hash maps.
	 */
	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class HashMap
	{
	public:
		typedef std::pair<TKey, TData> PairType;  /**< A pair type that holds keys and data. */
	private:
		typedef SList<PairType> ChainType;  /**< A chain type that will hold the key/value pairs. */
		typedef Vector<ChainType> BucketType; /**< A bucket type that will hold all the chains. */
		typedef typename SList<PairType>::Iterator ChainIterator;  /**< A typedef for the chain iterator. */
	public:
		/**
		* A nested class for the iterator of the hash map.
		*/
		class Iterator
		{
			/**
			* HashMap should have access to Iterator's private members.
			*/
			friend class HashMap;
		public:
			/**
			* The constructor.
			*/
			Iterator();

			/**
			* The copy constructor.
			* @param rhs	the iterator to copy
			*/
			Iterator(const Iterator& rhs);

			/**
			* The assignment operator.
			* @param rhs	the iterator to copy
			* @return A reference to the newly copied iterator
			*/
			Iterator& operator=(const Iterator& rhs);

			/**
			* The dereference operator.
			* @throws	an exception if mOwner is null
			* @throws	an exception if mBucketIndex is greater than or equal to the hash map size
			* @return	A reference to the data that was dereferenced from the iterator
			*/
			PairType& operator*();

			/**
			* The dereference operator.
			* @throws	an exception if mOwner is null
			* @throws	an exception if mBucketIndex is greater than or equal to the hash map size
			* @return	A pointer to the data that was dereferenced from the iterator
			*/
			PairType* operator->();

			/**
			* The comparison operator. Compares equality.
			* @param rhs	the iterator to compare to
			* @return true if the iterators are equal, false otherwise
			*/
			bool operator==(const Iterator& rhs) const;

			/**
			* The comparison operator. Compares non-equality.
			* @param rhs	the iterator to compare to
			* @return true if the iterators are non-equal, false otherwise
			*/
			bool operator!=(const Iterator& rhs) const;

			/**
			* The increment operator. Prefix version.
			* @throws	An exception if mOwner is null
			* @return	A reference to the incremented iterator
			*/
			Iterator& operator++();

			/**
			* The increment operator. Postfix version.
			* @throws	An exception if mOwner is null
			* @return	A copy to the iterator that will then be incremented
			*/
			Iterator operator++(int);

		private:
			const HashMap* mOwner; /**< The hash map the iterator belongs to. */
			std::uint32_t mBucketIndex; /**< The index of the bucket in the hash map. */
			ChainIterator mChainIterator; /**< The iterator of the chain in the bucket. */
			bool mAtEnd;	 /**< A boolean telling whether the iterator has reached the end of the hash map or not. */

			/** 
			* The constructor for a hash map iterator. Accepts values for arguments.
			* @param hMap	the hash map the iterator will be assigned to
			* @param bucketIndex	the bucket index the iterator will store
			* @param chainIterator  the iterator to assign for the chain within the bucket
			* @param atEnd		sets whether the iterator will be able to increment or not
			*/
			Iterator(const HashMap* hMap, std::uint32_t bucketIndex, ChainIterator chainIterator, bool atEnd = false);
		};

	public:
		/**
		 * The constructor.
		 * @param size	the number of buckets in the hash map
		 * @throws an exception if mSize is initialized to 0
		 */
		explicit HashMap(std::uint32_t size = 1);

		/**
		* The copy constructor. Performs a deep copy.
		* @param rhs	the hash map to copy
		*/
		HashMap(const HashMap& rhs);

		/**
		* The assignment operator. Performs a deep copy.
		* @param rhs	the hash map to copy
		* @return a reference to the newly copied hash map
		*/
		HashMap& operator=(const HashMap& rhs);

		/**
		 * The destructor.
		 */
		~HashMap();

		/**
		 * The index operator. If no pair is found, a new pair is created.
		 * @param key	the key to the pair to find
		 * @return	A reference to the data in the found pair or, if none was found, a reference to the data in the newly created pair
		 */
		TData& operator[](const TKey& key);

		/**
		* The comparison operator. Tests for equality.
		* @param rhs the hash map to compare to
		* @return true if the hash maps are equal, false otherwise
		*/
		bool operator==(const HashMap& rhs) const;

		/**
		* The comparison operator. Tests for non-equality.
		* @param rhs the hash map to compare to
		* @return true if the hash maps are equal, false otherwise
		*/
		bool operator!=(const HashMap& rhs) const;

		/**
		 * Finds a pair and returns an iterator to it if it is found.
		 * @param key	the key to the pair to find
		 * @return An iterator to the found pair, or end() if no pair is found.
		 */
		Iterator Find(const TKey& key) const;

		/**
		 * Inserts a pair into the hash table. If the key to the pair already exists, nothing happens.
		 * @param pair	the pair to insert
		 * @return An iterator to the newly inserted pair or, if the pair already exists, an iterator to the existing pair
		 */
		Iterator Insert(const PairType& pair);

		/**
		 * Removes a pair from the hash table. If no pair is found, nothing happens.
		 * @param key	the key to find for removal
		 */
		void Remove(const TKey& key);

		/**
		 * Clears all the buckets within the hash map. Does not modify size.
		 */
		void Clear();

		/**
		 * Returns the number of pairs within the hash map.
		 * @return The number of pairs within the hash map
		 */
		std::uint32_t Size() const;

		/**
		 * Creates the buckets according to size. Should only be called when the hash map is empty.
		 * @param newSize	the new size of the hash map
		 */
		void Resize(std::uint32_t newSize);

		/**
		 * Checks if a key exists within the hash table.
		 * @param key	the key to check for
		 * @return true if the key is found, false otherwise
		 */
		bool ContainsKey(const TKey& key) const;

		/**
		 * Returns an iterator to the first pair in the hash map.
		 * @return an iterator to the first pair in the hash map.
		 */
		Iterator begin() const;

		/**
		* Returns an iterator to the end of the last chain in the hash map.
		* @return an iterator to the end of the last chain in the hash map.
		*/
		Iterator end() const;

	private:
		BucketType mBucket;  /**< Holds all of the buckets in the hash map. */
		std::uint32_t mBeginBucketIndex;  /**< The index of the first bucket with a non-empty chain. */
		std::uint32_t mSize;  /**< The number of buckets in the hash map. */
		std::uint32_t mNumData;  /**< The number of pairs within the hash map. */
	};
}

#include "HashMap.inl"