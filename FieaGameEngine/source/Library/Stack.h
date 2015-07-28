#pragma once

#include <cstdint>
#include <iostream>
#include <exception>
#include "Vector.h"

namespace Library
{
	/**
	 * A class for stacks.
	 */
	template <typename T>
	class Stack
	{
	public:
		/**
		 * The constructor.
		 */
		Stack();

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the stack to copy
		 */
		Stack(const Stack<T>& rhs);

		/**
		 * The assignment operator. Performs a deep copy.
		 * @param rhs	the stack to copy
		 * @return A reference to the newly copied stack
		 */
		Stack<T>& operator=(const Stack<T>& rhs);

		/**
		 * The destructor.
		 */
		~Stack();

		/**
		 * Pushes an item to the top of the stack.
		 * @param item	the item to push
		 */
		void Push(const T& item);

		/**
		 * Pops an item from the top of the stack.
		 */
		void Pop();

		/**
		 * Gets the item from the top of the stack. Non-const version.
		 * @throws an exception if the stack is empty
		 * @return the item from the top of the stack
		 */
		T& Top();

		/**
		* Gets the item from the top of the stack. Const version.
		* @throws an exception if the stack is empty
		* @return the item from the top of the stack
		*/
		const T& Top() const;

		/**
		 * Gets the number of items in the stack.
		 * @return the number of items in the stack
		 */
		std::uint32_t Size() const;

		/**
		 * Gets whether the stack is empty or not.
		 * @return true if the stack is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Clears the entire stack.
		 */
		void Clear();

	private:
		Vector<T> mVector; /**< A vector that will be used to store the items of the stack. The stack will use its interface to perform its operations. */
	};
}

#include "Stack.inl"