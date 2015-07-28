#include "Vector.h"

namespace Library
{
#pragma region Iterator
	template <typename T>
	Vector<T>::Iterator::Iterator() : mOwner(nullptr), mIndex(0) {}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Vector* vec, std::uint32_t index) : mOwner(vec), mIndex(index) {}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Iterator& rhs) : mOwner(rhs.mOwner), mIndex(rhs.mIndex) {}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mIndex = rhs.mIndex;
		}

		return *this;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*()
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		if (mIndex >= mOwner->mCapacity)
			throw std::exception("This iterator cannot return data that falls outside the capacity of the vector!");

		if (mIndex >= mOwner->mSize)
			throw std::exception("This iterator cannot return data that falls outside the size of the vector!");

		return const_cast<T&>((*mOwner)[mIndex]);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mIndex == rhs.mIndex);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return (mOwner != rhs.mOwner || mIndex != rhs.mIndex);
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		if (mOwner->mSize > mIndex)
			++mIndex;

		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		Iterator copy = *this;
		operator++();
		return copy;
	}
#pragma endregion

#pragma region Vector
	template <typename T>
	Vector<T>::Vector(std::uint32_t size) : mArray(nullptr), mSize(0), mCapacity(0)
	{
		Reserve(size);
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& rhs) : mArray(nullptr), mSize(0), mCapacity(0)
	{
		operator=(rhs);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
	{
		if (this != &rhs)
		{
			Iterator iterator;
			Clear();

			for (iterator = rhs.begin(); iterator != rhs.end(); ++iterator)
			{
				PushBack(*iterator);
			}
		}

		return *this;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		if (index >= mCapacity)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (index >= mSize)
			throw std::exception("Cannot return data that falls outside the size of the vector!");

		return mArray[index];
	}

	template <typename T>
	const T& Vector<T>::operator[](std::uint32_t index) const
	{
		if (index >= mCapacity)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (index >= mSize)
			throw std::exception("Cannot return data that falls outside the size of the vector!");

		return mArray[index];
	}

	template <typename T>
	bool Vector<T>::operator==(const Vector<T>& rhs) const
	{
		if (mSize != rhs.mSize)
			return false;

		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (mArray[i] != rhs.mArray[i])
				return false;
		}
		return true;
	}

	template <typename T>
	bool Vector<T>::operator!=(const Vector<T>& rhs) const
	{
		return !operator==(rhs);
	}

	template <typename T>
	void Vector<T>::PushBack(const T& data)
	{
		if (mCapacity == 0)
			Reserve(1);

		if (mSize == mCapacity)
			Reserve(mCapacity * 2);

		T* ptr;
		ptr = new(&mArray[mSize]) T(data);
		mSize++;
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (mSize > 0)
		{
			mArray[mSize - 1].~T();
			mSize--;
		}
	}

	template <typename T>
	bool Vector<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		if (mCapacity == 0)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (mSize == 0)
			throw std::exception("Vector is empty!");

		return mArray[0];
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		if (mCapacity == 0)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (mSize == 0)
			throw std::exception("Vector is empty!");

		return mArray[0];
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (mCapacity == 0)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (mSize == 0)
			throw std::exception("Vector is empty!");

		return mArray[mSize - 1];
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		if (mCapacity == 0)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (mSize == 0)
			throw std::exception("Vector is empty!");

		return mArray[mSize - 1];
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Vector<T>::Iterator(this, 0);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Vector<T>::Iterator(this, mSize);
	}

	template <typename T>
	T& Vector<T>::At(std::uint32_t index)
	{
		if (index >= mCapacity)
			throw std::exception("Cannot return data that falls outside the capacity of the vector!");

		if (index >= mSize)
		{
			for (uint32_t i = mSize; i <= index; ++i)
			{
				T* ptr;
				ptr = new(&mArray[i]) T();
			}
			mSize = index + 1;
		}

		return mArray[index];
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t newCapacity)
	{
		if (newCapacity > mCapacity)
		{
			if (mCapacity == 0)
				mArray = (T*)malloc(newCapacity * sizeof(T));
			else
				mArray = (T*)realloc(mArray, newCapacity * sizeof(T));

			mCapacity = newCapacity;
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& data) const
	{
		Iterator iterator;

		for (iterator = begin(); iterator != end(); ++iterator)
		{
			if (*iterator == data)
				break;
		}

		return iterator;
	}

	template <typename T>
	bool Vector<T>::Remove(const T& data)
	{
		bool foundData = false;
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (foundData)
			{
				mArray[i - 1] = mArray[i];
			}
			else
			{
				if (mArray[i] == data)
				{
					foundData = true;
				}
			}
		}

		if (foundData)
			PopBack();

		return foundData;
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		while (mSize > 0)
			PopBack();

		free(mArray);

		mArray = nullptr;
		mCapacity = 0;
	}
#pragma endregion
}