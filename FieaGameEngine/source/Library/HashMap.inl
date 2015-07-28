#include "HashMap.h"

namespace Library
{
#pragma region DefaultHash
	template <typename T>
	std::uint32_t DefaultHash<T>::operator()(const T& key) const
	{
		std::uint32_t hash = 0;

		const unsigned char* keyArray = reinterpret_cast<const unsigned char*>(&key);
		int keySize = sizeof(T);
		for (int i = 0; i < keySize; i++)
			hash = hashPrime * hash + keyArray[i];

		return hash;
	}

	template <typename T>
	class DefaultHash<T*>
	{
	public:
		std::uint32_t operator()(const T* key) const
		{
			std::uint32_t hash = 0;

			const unsigned char* keyArray = reinterpret_cast<const unsigned char*>(key);
			int keySize = sizeof(T);
			for (int i = 0; i < keySize; i++)
				hash = hashPrime * hash + keyArray[i];

			return hash;
		}
	};

	template <>
	class DefaultHash<std::string>
	{
	public:
		std::uint32_t operator()(const std::string& key) const
		{
			std::uint32_t hash = 0;

			const unsigned char* keyArray = reinterpret_cast<const unsigned char*>(key.c_str());
			int keySize = key.size();
			for (int i = 0; i < keySize; i++)
				hash = hashPrime * hash + keyArray[i];

			return hash;
		}
	};

	template <>
	class DefaultHash<char*>
	{
	public:
		std::uint32_t operator()(const char* key) const
		{
			std::uint32_t hash = 0;

			int keySize = strlen(key);
			for (int i = 0; i < keySize; i++)
				hash = hashPrime * hash + key[i];

			return hash;
		}
	};
	
#pragma endregion

#pragma region Iterator
	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator() : mOwner(nullptr), mBucketIndex(0), mAtEnd(false) {}

	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const HashMap* hMap, std::uint32_t bucketIndex, typename HashMap<TKey, TData, HashFunctor>::ChainIterator chainIterator, bool atEnd = false) 
		: mOwner(hMap), mBucketIndex(bucketIndex), mChainIterator(chainIterator), mAtEnd(atEnd)
	{
		if (mChainIterator == (*mOwner).mBucket[(*mOwner).mSize - 1].End())
			mAtEnd = true;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) : mOwner(rhs.mOwner), mBucketIndex(rhs.mBucketIndex), mChainIterator(rhs.mChainIterator), mAtEnd(rhs.mAtEnd) {}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mBucketIndex = rhs.mBucketIndex;
			mChainIterator = rhs.mChainIterator;
			mAtEnd = rhs.mAtEnd;
		}
		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		if (mBucketIndex >= mOwner->mSize)
			throw std::exception("This iterator cannot return data that falls outside the size of the hash map!");

		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType* HashMap<TKey, TData, HashFunctor>::Iterator::operator->()
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		if (mBucketIndex >= mOwner->mSize)
			throw std::exception("This iterator cannot return data that falls outside the size of the hash map!");

		return &(*mChainIterator);
	}

	template <typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mBucketIndex == rhs.mBucketIndex && mChainIterator == rhs.mChainIterator && mAtEnd == rhs.mAtEnd);
	}

	template <typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return (mOwner != rhs.mOwner || mBucketIndex != rhs.mBucketIndex || mChainIterator != rhs.mChainIterator || mAtEnd != rhs.mAtEnd);
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		if (mOwner->mSize > mBucketIndex && !mAtEnd)
		{
			// if we reached the end of the chain...
			if (++mChainIterator == (*mOwner).mBucket[mBucketIndex].End())
			{
				// go to next bucket in the hash map
				++mBucketIndex;
				if ((*mOwner).mSize == mBucketIndex)
				{
					mAtEnd = true;
					--mBucketIndex;
				}

				// if the bucket is empty, jump to the next unempty one
				while ((*mOwner).mBucket[mBucketIndex].Size() == 0 && !mAtEnd)
				{
					++mBucketIndex;

					// if no unempty bucket is found, go to end of last bucket in hash map
					if ((*mOwner).mSize == mBucketIndex)
					{
						mAtEnd = true;
						--mBucketIndex;
					}
				}

				// the chain operator should start at the next unempty bucket if one is found; otherwise it should point to the end of the last bucket to match with the hash map's end() method
				if (mOwner->mSize > mBucketIndex && !mAtEnd)
					mChainIterator = (*mOwner).mBucket[mBucketIndex].Begin();
				else if (mAtEnd)
					mChainIterator = (*mOwner).mBucket[(*mOwner).mSize - 1].End();
			}
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		if (mOwner == nullptr)
			throw std::exception("This iterator does not have an owner!");

		Iterator copy = *this;
		operator++();
		return copy;
	}
#pragma endregion

#pragma region HashMap
	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::HashMap(const std::uint32_t size) : mBeginBucketIndex(size - 1), mSize(size), mNumData(0)
	{
		if (mSize == 0)
			throw std::exception("You must have a hash map size greater than 0!");

		for (std::uint32_t i = 0; i < mSize; i++)
		{
			mBucket.PushBack(ChainType());
		}
	}

	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::HashMap(const HashMap& rhs) 
		: mBucket(rhs.mBucket), mBeginBucketIndex(rhs.mBeginBucketIndex), mSize(rhs.mSize), mNumData(rhs.mNumData)
	{
		if (mSize == 0)
			throw std::exception("You must have a hash map size greater than 0!");
	}

	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>& HashMap<TKey, TData, HashFunctor>::operator=(const HashMap& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mBucket = rhs.mBucket;
			mBeginBucketIndex = rhs.mBeginBucketIndex;
			mSize = rhs.mSize;
			mNumData = rhs.mNumData;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::~HashMap() 
	{
		Clear();
	}

	template <typename TKey, typename TData, typename HashFunctor>
	TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
		std::pair<TKey, TData> newEntry(key, TData());
		Iterator iterator = Insert(newEntry);
		return (*iterator).second;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::operator==(const HashMap& rhs) const
	{
		if (mSize != rhs.mSize || mNumData != rhs.mNumData)
			return false;

		Iterator leftIterator = begin();
		Iterator rightIterator = rhs.begin();

		while (leftIterator != end() && rightIterator != end())
		{
			if (*leftIterator != *rightIterator)
				return false;

			++leftIterator;
			++rightIterator;
		}

		return true;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::operator!=(const HashMap& rhs) const
	{
		return !operator==(rhs);
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		HashFunctor hFunctor;
		std::uint32_t bucketIndex = hFunctor(key) & mSize - 1;

		Iterator iterator;
		for (iterator = HashMap<TKey, TData, HashFunctor>::Iterator(this, bucketIndex, mBucket[bucketIndex].Begin()); iterator != end() && iterator.mChainIterator != mBucket[bucketIndex].End(); ++iterator)
		{
			if ((*iterator).first == key)
				return iterator;
		}

		return end();
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& pair)
	{
		Iterator iterator = Find(pair.first);

		if (iterator != end())
			return iterator;

		HashFunctor hFunctor;
		std::uint32_t bucketIndex = hFunctor(pair.first) & mSize - 1;

		mBucket[bucketIndex].PushBack(pair);
		++mNumData;

		if (mBeginBucketIndex > bucketIndex)
			mBeginBucketIndex = bucketIndex;

		return Find(pair.first);
	}

	template <typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		Iterator iterator = Find(key);

		if (iterator != end())
		{
			HashFunctor hFunctor;
			std::uint32_t bucketIndex = hFunctor(key) & mSize - 1;

			std::pair<TKey, TData> pairToRemove((*iterator).first, (*iterator).second);
			mBucket[bucketIndex].Remove(pairToRemove);
			--mNumData;

			if (mBucket[bucketIndex].Size() == 0)
			{
				while (mBeginBucketIndex != mSize && mBucket[mBeginBucketIndex].Size() == 0)
					++mBeginBucketIndex;
			}
		}
	}

	template <typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Clear()
	{
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			mBucket[i].Clear();
		}
		
		mBeginBucketIndex = mSize - 1;
		mNumData = 0;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	std::uint32_t HashMap<TKey, TData, HashFunctor>::Size() const
	{
		return mNumData;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Resize(std::uint32_t newSize)
	{
		if (mSize > newSize)
		{
			for (std::uint32_t i = mSize; i > newSize; --i)
				mBucket.PopBack();
		}
		else if (mSize < newSize)
		{
			for (std::uint32_t i = mSize; i < newSize; ++i)
				mBucket.PushBack(ChainType());
		}
		mSize = newSize;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return Find(key) != end();
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin() const
	{
		return HashMap<TKey, TData, HashFunctor>::Iterator(this, mBeginBucketIndex, mBucket[mBeginBucketIndex].Begin());
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end() const
	{
		// this will return the end of the last bucket
		return HashMap<TKey, TData, HashFunctor>::Iterator(this, mSize - 1, mBucket[mSize - 1].End(), true);
	}
#pragma endregion
}