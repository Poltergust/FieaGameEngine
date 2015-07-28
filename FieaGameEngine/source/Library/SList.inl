#include "SList.h"

namespace Library
{
#pragma region Node
	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next) : mData(data), mNext(next) {}
#pragma endregion

#pragma region Iterator
	template <typename T>
	SList<T>::Iterator::Iterator() : mOwner(nullptr), mNode(nullptr) {}

	template <typename T>
	SList<T>::Iterator::Iterator(SList* list, Node* node) : mOwner(list), mNode(node) {}

	template <typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs)
	{
		operator=(rhs);
	}
	
	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mNode = rhs.mNode;
		}

		return *this;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
			throw std::exception("This iterator does not have a Node attached to it!");
		return mNode->mData;
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mNode == rhs.mNode);
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return (mOwner != rhs.mOwner || mNode != rhs.mNode);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->mNext;
		}

		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator copy = *this;
		operator++();
		return copy;
	}
#pragma endregion

#pragma region SList
	template <typename T>
	SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0) {}

	template <typename T>
	SList<T>::SList(const SList<T>& rhs) : mFront(nullptr), mBack(nullptr), mSize(0)
	{
		operator=(rhs);
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList<T>& rhs)
	{
		if (this != &rhs) 
		{
			Iterator iterator;
			Clear();

			for (iterator = rhs.Begin(); iterator != rhs.End(); ++iterator)
			{
				PushBack(*iterator);
			}
		}

		return *this;
	}

	template <typename T>
	SList<T>::~SList() 
	{
		Clear();
	}

	template <typename T>
	void SList<T>::PushFront(const T& data)
	{
		Node* newFront = new Node(data, mFront);
		if (mSize == 0)
			mBack = newFront;
		mFront = newFront;
		mSize++;
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (mSize > 0)
		{
			Node* frontNode = mFront;
			mFront = frontNode->mNext;
			delete frontNode;
			mSize--;

			if (mFront == nullptr)
				mBack = nullptr;
		}
	}

	template <typename T>
	void SList<T>::PushBack(const T& data)
	{
		Node* newBack = new Node(data);
		if (mSize == 0)
		{
			mFront = newBack;
			mBack = newBack;
		}
		else
		{
			mBack->mNext = newBack;
			mBack = newBack;
		}
		mSize++;
	}

	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template <typename T>
	T& SList<T>::Front() const
	{
		if (mSize == 0)
			throw std::exception("List is empty!");
		return mFront->mData;
	}

	template <typename T>
	T& SList<T>::Back() const
	{
		if (mSize == 0)
			throw std::exception("List is empty!");
		return mBack->mData;
	}

	template <typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	void SList<T>::Clear()
	{
		while (mSize > 0)
			PopFront();
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Begin() const
	{
		return SList<T>::Iterator(const_cast<SList<T>*>(this), mFront);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::End() const
	{
		return SList<T>::Iterator(const_cast<SList<T>*>(this), nullptr);
	}

	template <typename T>
	void SList<T>::InsertAfter(const T& data, const Iterator& iterator)
	{
		if (iterator == End() || iterator.mNode->mNext == nullptr)
		{
			PushBack(data);
		}
		else 
		{
			Node* newData = new Node(data);
			Node* nodeAfter = iterator.mNode->mNext;
			iterator.mNode->mNext = newData;
			newData->mNext = nodeAfter;
			mSize++;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& data) const
	{
		Iterator iterator;

		for (iterator = Begin(); iterator != End(); ++iterator)
		{
			if (*iterator == data)
				return iterator;
		}

		return iterator;
	}

	template <typename T>
	void SList<T>::Remove(const T& data)
	{
		Iterator iterator;

		if (mSize == 0)
			return;

		if (data == Front())
		{
			PopFront();
		}
		else {
			for (iterator = Begin(); iterator.mNode->mNext != nullptr; ++iterator)
			{
				if (iterator.mNode->mNext->mData == data)
				{
					Node* nodeAfter = iterator.mNode->mNext->mNext;
					delete iterator.mNode->mNext;
					iterator.mNode->mNext = nodeAfter;

					if (nodeAfter == nullptr)
						mBack = iterator.mNode;

					mSize--;
					break;
				}
			}
		}
	}
#pragma endregion
}