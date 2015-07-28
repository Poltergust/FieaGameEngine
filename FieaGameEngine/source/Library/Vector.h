#pragma once

#include <cstdint>
#include <iostream>
#include <exception>

namespace Library
{
	/**
	* A class for vectors.
	*/
	template <typename T>
	class Vector
	{
	public:
		/**
		* A nested class for the iterator of the vector.
		*/
		class Iterator
		{
			/**
			* Vector should have access to Iterator's private members.
			*/
			friend class Vector;
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
			* @throws	an exception if mIndex is greater than or equal to the vector capacity
			* @throws	an exception if mIndex is greater than or equal to the vector size
			* @return	A reference to the data that was dereferenced from the iterator
			*/
			T& operator*();

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
			const Vector* mOwner; /**< The vector the iterator belongs to. */
			std::uint32_t mIndex; /**< The index of the data stored in the vector. */

			/** The constructor. Accepts values for arguments.
			* @param vec	the vector the iterator will be assigned to
			* @param index	the index the iterator will store
			*/
			Iterator(const Vector* vec, std::uint32_t index);
		};

	public:
		/**
		 * The constructor. Sets default values for all data members.
		 */
		Vector(std::uint32_t size = 10);

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the vector to copy
		 */
		Vector(const Vector<T>& rhs);

		/**
		 * The assignment operator. Performs a deep copy.
		 * @param rhs	the vector to copy
		 * @return A reference to the newly copied vector
		 */
		Vector<T>& operator=(const Vector<T>& rhs);

		/**
		 * The destructor.
		 */
		~Vector();

		/**
		 * The index operator. Non-const version.
		 * @param index	the index into the vector
		 * @throws an exception if the index is greater than or equal to the capacity
		 * @throws an exception if the index is greater than or equal to the size
		 * @return A reference to the data at the given index
		 */
		T& operator[](std::uint32_t index);

		/**
		* The index operator. Const version.
		* @param index	the index into the vector
		* @throws an exception if the index is greater than or equal to the capacity
		* @throws an exception if the index is greater than or equal to the size
		* @return A reference to the data at the given index
		*/
		const T& operator[](std::uint32_t index) const;

		/** 
		 * The comparison operator. Tests for equality.
		 * @param rhs the vector to compare to
		 * @return true if the vectors are equal, false otherwise
		 */
		bool operator==(const Vector<T>& rhs) const;

		/**
		* The comparison operator. Tests for non-equality.
		* @param rhs the vector to compare to
		* @return true if the vectors are equal, false otherwise
		*/
		bool operator!=(const Vector<T>& rhs) const;

		/**
		 * Appends data to the back of the vector.
		 * @param data	the data to be appended
		 */
		void PushBack(const T& data);

		/**
		 * Removes the last item in the vector.
		 */
		void PopBack();

		/**
		 * Determines whether the vector is empty or not.
		 * @return true if the vector is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Gets the data from the front of the vector. Non-const version.
		 * @throws an exception if there is no space allocated for the vector
		 * @throws an exception if the vector is empty
		 * @return The data from the front of the vector
		 */
		T& Front();

		/**
		 * Gets the data from the front of the vector. Const version.
		 * @throws an exception if there is no space allocated for the vector
		 * @throws an exception if the vector is empty
		 * @return The data from the front of the vector
		 */
		const T& Front() const;

		/**
		 * Gets the data from the back of the vector. Non-const version.
		 * @throws an exception if there is no space allocated for the vector
		 * @throws an exception if the vector is empty
		 * @return The data from the back of the vector
		 */
		T& Back();

		/**
		 * Gets the data from the back of the vector. Const version.
		 * @throws an exception if there is no space allocated for the vector
		 * @throws an exception if the vector is empty
		 * @return The data from the back of the vector
		 */
		const T& Back() const;

		/**
		 * Gets the size of the vector.
		 * @return the size of the vector
		*/
		std::uint32_t Size() const;

		/**
		 * Returns an iterator to the front of the vector.
		 * @return an iterator to the front of the vector
		 */
		Iterator begin() const;

		/**
		* Returns an iterator to the point after the last item in the vector.
		* @return an iterator to the point after the last item in the vector
		*/
		Iterator end() const;

		/**
		 * Returns a reference to the data at the given index. If the index is greater than the size, the size of the vector gets increased to it.
		 * @param index the index into the vector for the data to return
		 * @throws an exception if the index is greater than or equal to the capacity of the vector
		 * @return a reference to the data at the given index
		 */
		T& At(std::uint32_t index);

		/**
		 * Increases the capacity and allocates additional memory for the vector. If the given capacity is less the current capacity, nothing happens.
		 * @param newCapacity	the amount to increase the capacity to
		 */
		void Reserve(std::uint32_t newCapacity);

		/**
		 * Finds the first instance of some data and returns an iterator to its location in the vector
		 * @param data	the data to be found in the vector
		 * @return an iterator to the first instance of the given data, or an iterator referring to null data if the data was not found
		 */
		Iterator Find(const T& data) const;

		/**
		 * Removes an element from the vector and reorganizes the vector accordingly
		 * @param data	the data to be removed from the vector
		 * @return true if the data was removed, false otherwise
		 */
		bool Remove(const T& data);

		/**
		 * Clears the entire vector.
		 */
		void Clear();

	private:
		T* mArray; /**< The array for the vector. Initialized to nullptr, but is then given a value with malloc within the constructor. */
		std::uint32_t mSize; /**< The amount of data in the vector. Initialized to 0. */
		std::uint32_t mCapacity; /**< The total capacity of the vector. Initialized to 0. */
	};
}

#include "Vector.inl"