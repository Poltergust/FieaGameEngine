#pragma once

#include <cstdint>
#include <iostream>
#include <exception>

namespace Library
{
	/**
	 * A class for singly-linked lists.
	 */
	template <typename T>
	class SList
	{
	private:
		/**
		 * A nested class for the nodes within a singly-linked list.
		 */
		class Node
		{
		public:
			T mData; /**< The data stored within the node. */
			Node* mNext; /**< Pointer to the next node in the linked list. */

			/**
			 * The constructor.
			 * @param data	the data to be stored within the node
			 * @param next	pointer to the next node in the linked list, defaulted to nullptr
			 */
			Node(const T& data, Node* next = nullptr);

		private:
			/**
			 * The copy constructor. Unused.
			 * @param rhs	the node to copy
			 */
			Node(const Node& rhs) = delete;

			/**
			 * The assignment operator. Unused.
			 * @param rhs	the node to copy
			 * @return A reference to the newly copied node
			 */
			Node& operator=(const Node& rhs) = delete;
		};

	public:
		/**
		 * A nested class for the iterator of the linked list.
		 */
		class Iterator
		{
			/**
			 * SList should have access to Iterator's private members.
			 */
			friend class SList;

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
			 * @return A reference to the newlly copied iterator
			 */
			Iterator& operator=(const Iterator& rhs);

			/**
			 * The dereference operator.
			 * @throws  an error statement if mNode is null
			 * @return	A reference to the data that was dereferenced from the iterator
			 */
			T& operator*() const;

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
			 * @return A reference to the incremented iterator
			 */
			Iterator& operator++();

			/**
			 * The increment operator. Postfix version.
			 * @return A copy to the iterator that will then be incremented
			 */
			Iterator operator++(int);

		private:
			SList* mOwner; /**< The singly-linked list the iterator belongs to. */
			Node* mNode; /**< The node that the iterator is pointing to. */

			/** The constructor. Accepts values for arguments.
			 * @param list	the singly-linked list the iterator will be assigned to
			 * @param node	the node the iterator will initially point to
			 */
			Iterator(SList* list, Node* node);
		};

	public:
		/**
		 * The constructor.
		 */
		SList();

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the linked list to copy
		 */
		SList(const SList<T>& rhs);

		/** 
		 * The assignment operator. Performs a deep copy.
		 * @param rhs	the linked list to copy
		 * @return A reference to the newly copied linked list
		 */
		SList<T>& operator=(const SList<T>& rhs);

		/**
		 * The destructor.
		 */
		~SList();

		/**
		 * Inserts data to the front of the linked list.
		 * @param data	the data to be inserted
		 */
		void PushFront(const T& data);

		/**
		 * Removes a node from the front of the linked list.
		 */
		void PopFront();

		/**
		 * Appends data to the back of the linked list.
		 * @param data	the data to be appended
		 */
		void PushBack(const T& data);

		/**
		 * Determines whether the linked list is empty or not.
		 * @return true if the linked list is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Gets the data from the front of the linked list.
		 * @throws an error statement if the linked list is empty
		 * @return The data from the front of the linked list
		 */
		T& Front() const;

		/**
		 * Gets the data from the back of the linked list.
		 * @throws an error statement if the linked list is empty
		 * @return The data from the back of the linked list
		 */
		T& Back() const;

		/**
		 * Gets the size of the linked list.
		 * @return the size of the list
		 */
		std::uint32_t Size() const;

		/**
		 * Clears the entire linked list.
		 */
		void Clear();

		/**
		 * Returns an iterator to the front of the linked list.
		 * @return an iterator to the front of the linked list
		 */
		Iterator Begin() const;

		/**
		* Returns an iterator to the point after the last item in the list.
		* @return an iterator to the point after the last item in the list
		*/
		Iterator End() const;

		/**
		 * Inserts data into the list after the specified node provided in the iterator.
		 * @param data	the data to be inserted
		 * @param iterator	contains the node where the data is inserted after it
		 */
		void InsertAfter(const T& data, const Iterator& iterator);

		/**
		 * Finds the first instance of some data and returns an iterator to its location in the linked list
		 * @param data	the data to be found in the linked list
		 * @return an iterator to the first instance of the given data
		 */
		Iterator Find(const T& data) const;

		/**
		 * Finds the first instance of some data and removes it from the linked list.
		 * @param data	the data to be removed from the linked list
		 */
		void Remove(const T& data);

	private:
		Node* mFront; /**< The pointer to the node in the front of the linked list. Initialized to nullptr. */
		Node* mBack; /**< The pointer to the node in the back of the linked list. Initialized to nullptr. */
		std::uint32_t mSize; /**< The number of nodes in the linked list. Initialized to 0. */
	};

}

#include "SList.inl"