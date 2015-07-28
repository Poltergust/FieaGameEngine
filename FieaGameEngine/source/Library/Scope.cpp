#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope(std::uint32_t size) : mTable(size), mOrder(size), mParent(nullptr) {}

	Scope::Scope(const Scope& rhs) : mTable(), mOrder(), mParent(nullptr) 
	{
		operator=(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Orphan();
			Clear();
			mTable.Resize(rhs.mTable.Size());  // this should be OK to call since the hash map is empty after Clear()

			for (std::uint32_t i = 0; i < rhs.mOrder.Size(); ++i)
			{
				if (rhs.mOrder[i]->second.GetType() != Datum::Table)
				{
					Datum& d = Append(rhs.mOrder[i]->first);
					d = rhs.mOrder[i]->second;
				}
				else
				{
					std::uint32_t datumSize = rhs.mOrder[i]->second.Size();
					for (std::uint32_t datumCounter = 0; datumCounter < datumSize; ++datumCounter)
					{
						Scope& s = AppendScope(rhs.mOrder[i]->first);  // s is a reference to a scope
						Datum* scopeDatum = Find(rhs.mOrder[i]->first);  // scopeDatum contains s
						Scope* scopePointer = rhs.mOrder[i]->second.GetTable(datumCounter); // scope pointer is a pointer to the corresponding scope in scopeDatum

						if (scopePointer == nullptr)
							scopeDatum->Set((Scope*)nullptr, datumCounter);  // if the scope in the rhs datum is null, this scope should also be null
						else
							s = *scopePointer;  // recursive call
					}
				}
			}
		}
		return *this;
	}

	Scope::~Scope()
	{
		Orphan();
		Clear();
	}

	Datum& Scope::operator[](const std::string& key)
	{
		return Append(key);
	}

	Datum& Scope::operator[](std::uint32_t index) const
	{
		if (index >= mOrder.Size())
			throw std::exception("Index is too large.");

		return mOrder[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (this == &rhs)
			return true;

		if (mTable.Size() != rhs.mTable.Size() || mOrder.Size() != rhs.mOrder.Size())
			return false;

		for (std::uint32_t i = 0; i < mOrder.Size(); ++i)
		{
			if (mOrder[i]->second != rhs.mOrder[i]->second)
				return false;
		}

		return true;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !operator==(rhs);
	}

	Datum* Scope::Find(const std::string& key) const
	{
		HashMap<std::string, Datum>::Iterator iterator = mTable.Find(key);
		if (iterator != mTable.end())
			return &iterator->second;

		return nullptr;
	}

	Datum* Scope::Search(const std::string& key, Scope** scope) const
	{
		Datum* d = Find(key);
		if (d == nullptr)
		{
			if (mParent != nullptr)
			{
				if (scope != nullptr)
					*scope = nullptr;
				return mParent->Search(key, scope);
			}
			return nullptr;
		}
		if (scope != nullptr)
			*scope = const_cast<Scope*>(this);
		return d;
	}

	Datum& Scope::Append(const std::string& key)
	{
		if (key == std::string())
			throw std::exception("Key cannot be an empty string.");

		// try to find entry first
		Datum* d = Find(key);
		if (d != nullptr)
			return *d;

		// if no entry is found, then one is inserted
		std::pair<std::string, Datum> pair(key, Datum());
		HashMap<std::string, Datum>::Iterator iterator = mTable.Insert(pair);
		mOrder.PushBack(&(*iterator));
		return iterator->second;
	}

	Scope& Scope::AppendScope(const std::string& key)
	{
		if (key == std::string())
			throw std::exception("Key cannot be an empty string.");

		Scope* newScope = new Scope();
		newScope->mParent = this;

		// try to find entry first in this scope
		Datum* d = Find(key);
		if (d != nullptr)
		{
			if (d->GetType() != Datum::Table && d->GetType() != Datum::Unknown)
			{
				delete newScope;
				throw std::exception("Found entry is not a table!");
			}
			if (d->IsExternal())
			{
				delete newScope;
				throw std::exception("Table entry is external. Cannot modify data owned by something else.");
			}

			// a new scope gets added into this table datum
			std::uint32_t datumSize = d->Size();
			d->Set(newScope, datumSize);
			return *d->GetTable(datumSize);
		}

		// if no entry is found, create new datum with this scope
		Datum scopeDatum;
		scopeDatum = newScope;
		std::pair<std::string, Datum> pair(key, scopeDatum);
		HashMap<std::string, Datum>::Iterator iterator = mTable.Insert(pair);
		mOrder.PushBack(&(*iterator));
		return *(iterator->second.GetTable());
	}

	void Scope::Adopt(Scope& child, const std::string& key, std::uint32_t index)
	{
		if (key == std::string())
			throw std::exception("Key cannot be an empty string.");

		child.Orphan();
		child.mParent = this;

		// try to find entry first in this scope
		Datum* d = Find(key);
		if (d != nullptr)
		{
			if (d->GetType() != Datum::Table)
				throw std::exception("Found entry is not a table!");
			if (d->IsExternal())
				throw std::exception("Table is external. Cannot modify data owned by something else.");

			std::uint32_t originalDatumSize = d->Size();

			// if a scope is empty or not pointing to anything at the given index, we can just have it point to something else
			if (originalDatumSize <= index || d->GetTable(index) == nullptr || d->GetTable(index)->mOrder.Size() == 0)
				d->Set(&child, index);

			// otherwise, we add in the child scope and rearrange the datum array if necessary
			else
			{
				if (index < originalDatumSize)
				{
					d->SetSize(originalDatumSize + 1);
					for (std::uint32_t i = originalDatumSize; i > index; --i)
					{
						d->Set(d->GetTable(i - 1), i);
					}
				}
				else if (index > originalDatumSize)
				{
					index = originalDatumSize;
				}
				d->Set(&child, index);
			}
		}
		else
		{
			Datum scopeDatum;
			scopeDatum = &child;

			std::pair<std::string, Datum> pair(key, scopeDatum);
			HashMap<std::string, Datum>::Iterator iterator = mTable.Insert(pair);
			mOrder.PushBack(&(*iterator));
		}
	}

	void Scope::Orphan()
	{
		std::string scopeName;
		if (mParent != nullptr)
		{

#ifdef DEBUG
			assert(mParent->FindName(this, scopeName));
#else
			mParent->FindName(this, scopeName);
#endif

			Datum* d = mParent->Find(scopeName);

			std::uint32_t datumSize = d->Size();

			for (std::uint32_t i = 0; i < datumSize; ++i)
			{
				if (d->GetTable(i) == this)
				{
					d->Set((Scope*)nullptr, i);
					break;
				}
			}
		}
		mParent = nullptr;
	}

	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	bool Scope::FindName(const Scope* scope, std::string& name) const
	{
		for (std::uint32_t i = 0; i < this->mOrder.Size(); ++i)
		{
			if (this->mOrder[i]->second.GetType() == Datum::Table)
			{
				std::uint32_t datumSize = this->mOrder[i]->second.Size();
				for (std::uint32_t datumCounter = 0; datumCounter < datumSize; ++datumCounter)
				{
					if (this->mOrder[i]->second.GetTable(datumCounter) == scope)
					{
						name = this->mOrder[i]->first;
						return true;
					}
				}
			}
		}
		return false;
	}

	Scope::Iterator Scope::begin() const
	{
		return mOrder.begin();
	}

	Scope::Iterator Scope::end() const
	{
		return mOrder.end();
	}

	std::uint32_t Scope::Size() const
	{
		return mOrder.Size();
	}

	void Scope::Clear()
	{
		HashMap<std::string, Datum>::Iterator iterator;
		for (iterator = mTable.begin(); iterator != mTable.end(); ++iterator)
		{
			if (iterator->second.GetType() == Datum::Table)
			{
				std::uint32_t datumSize = iterator->second.Size();
				for (std::uint32_t scopeCounter = 0; scopeCounter < datumSize; ++scopeCounter)
				{
					Scope* childScope = iterator->second.GetTable(scopeCounter);
					if (childScope != nullptr)
					{
						if (!iterator->second.IsExternal())
							delete childScope;
						else
							childScope->mParent = nullptr;
					}
				}
			}
		}

		mTable.Clear();
		mOrder.Clear();
	}
}