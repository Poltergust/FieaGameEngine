#include "Stack.h"

namespace Library
{
#pragma region Stack
	template <typename T>
	Stack<T>::Stack() {}

	template <typename T>
	Stack<T>::Stack(const Stack<T>& rhs) : mVector(rhs.mVector) {}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
	{
		if (this != &rhs)
		{
			mVector = rhs.mVector;
		}
		return *this;
	}

	template <typename T>
	Stack<T>::~Stack()
	{
		Clear();
	}

	template <typename T>
	void Stack<T>::Push(const T& item)
	{
		mVector.PushBack(item);
	}

	template <typename T>
	void Stack<T>::Pop()
	{
		mVector.PopBack();
	}

	template <typename T>
	T& Stack<T>::Top()
	{
		if (IsEmpty())
			throw std::exception("The stack is empty!");

		return mVector.Back();
	}

	template <typename T>
	const T& Stack<T>::Top() const
	{
		if (IsEmpty())
			throw std::exception("The stack is empty!");

		return mVector.Back();
	}

	template <typename T>
	std::uint32_t Stack<T>::Size() const
	{
		return mVector.Size();
	}

	template <typename T>
	bool Stack<T>::IsEmpty() const
	{
		return mVector.IsEmpty();
	}

	template <typename T>
	void Stack<T>::Clear()
	{
		mVector.Clear();
	}
#pragma endregion
}