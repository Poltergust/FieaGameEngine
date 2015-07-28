#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region SetFunctions
	void Attributed::SetUnknown(Datum& datum, void* valueArray, std::uint32_t index) { throw std::exception("Cannot set value of unknown datum type!"); }
	void Attributed::SetInteger(Datum& datum, void* valueArray, std::uint32_t index) 
	{ 
		if (valueArray == nullptr)
			datum.Set(int(), index);
		else
			datum.Set(((int*)valueArray)[index], index); 
	}
	void Attributed::SetFloat(Datum& datum, void* valueArray, std::uint32_t index) 
	{ 
		if (valueArray == nullptr)
			datum.Set(float(), index);
		else
			datum.Set(((float*)valueArray)[index], index); 
	}
	void Attributed::SetVector(Datum& datum, void* valueArray, std::uint32_t index) 
	{
		if (valueArray == nullptr)
			datum.Set(glm::vec4(), index);
		else
			datum.Set(((glm::vec4*)valueArray)[index], index); 
	}
	void Attributed::SetMatrix(Datum& datum, void* valueArray, std::uint32_t index) 
	{ 
		if (valueArray == nullptr)
			datum.Set(glm::mat4(), index);
		else
			datum.Set(((glm::mat4*)valueArray)[index], index); 
	}
	void Attributed::SetTable(Datum& datum, void* valueArray, std::uint32_t index)
	{ 
		if (valueArray == nullptr)
			datum.Set(new Scope(), index);
		else
			datum.Set(((Scope**)valueArray)[index], index); 
	}
	void Attributed::SetString(Datum& datum, void* valueArray, std::uint32_t index)
	{
		if (valueArray == nullptr)
			datum.Set(std::string(), index);
		else
			datum.Set(((std::string*)valueArray)[index], index);
	}
	void Attributed::SetPointer(Datum& datum, void* valueArray, std::uint32_t index)
	{ 
		if (valueArray == nullptr)
			datum.Set((RTTI*)nullptr, index);
		else
			datum.Set(((RTTI**)valueArray)[index], index); 
	}

	const Attributed::SetFunction Attributed::SetFn[] = { Attributed::SetUnknown, Attributed::SetInteger, Attributed::SetFloat, Attributed::SetVector,
		Attributed::SetMatrix, Attributed::SetTable, Attributed::SetString, Attributed::SetPointer };
#pragma endregion
#pragma region SetStorageFunctions
	void Attributed::SetStorageUnknown(Datum& datum, void* storageArray, std::uint32_t size) { throw std::exception("Cannot set storage of unknown datum type!"); }
	void Attributed::SetStorageInteger(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((int*)storageArray, size); }
	void Attributed::SetStorageFloat(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((float*)storageArray, size); }
	void Attributed::SetStorageVector(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((glm::vec4*)storageArray, size); }
	void Attributed::SetStorageMatrix(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((glm::mat4*)storageArray, size); }
	void Attributed::SetStorageTable(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((Scope**)storageArray, size); }
	void Attributed::SetStorageString(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((std::string*)storageArray, size); }
	void Attributed::SetStoragePointer(Datum& datum, void* storageArray, std::uint32_t size) { datum.SetStorage((RTTI**)storageArray, size); }

	const Attributed::SetStorageFunction Attributed::SetStorageFn[] = { Attributed::SetStorageUnknown, Attributed::SetStorageInteger, Attributed::SetStorageFloat, Attributed::SetStorageVector,
		Attributed::SetStorageMatrix, Attributed::SetStorageTable, Attributed::SetStorageString, Attributed::SetStoragePointer };
#pragma endregion

#pragma region Signature
	Attributed::Signature::Signature() : mName(std::string()), mType(Datum::Unknown), mInitialValue(nullptr), mSize(0), mStorage(nullptr) {}

	Attributed::Signature::Signature(const std::string& name, Datum::DatumType type, void* initialValue, std::uint32_t size, void* storage)
		: mName(name), mType(type), mInitialValue(initialValue), mSize(size), mStorage(storage) {}

	bool Attributed::Signature::operator==(const Signature& rhs) const
	{
		return (mName == rhs.mName && mType == rhs.mType && mInitialValue == rhs.mInitialValue && mSize == rhs.mSize && mStorage == rhs.mStorage);
	}

	bool Attributed::Signature::operator!=(const Signature& rhs) const
	{
		return !operator==(rhs);
	}
#pragma endregion

#pragma region Attributed
	Attributed::Attributed() : Scope(), mPopulateCounter(0), mIsPopulated(false), mThisAttributedObject(this), mSignatures()
	{
		Append(std::string("this")) = mThisAttributedObject;
		mSignatures.PushBack(Signature(std::string(std::string("this")), Datum::Pointer, &mThisAttributedObject, 1, nullptr));
	}

	Attributed::Attributed(const Attributed& rhs) : Scope(rhs), mPopulateCounter(0), mIsPopulated(rhs.mIsPopulated), mThisAttributedObject(this), mSignatures()
	{
		Append(std::string("this")) = mThisAttributedObject;
		mSignatures.PushBack(Signature(std::string(std::string("this")), Datum::Pointer, &mThisAttributedObject, 1, nullptr));
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			mIsPopulated = rhs.mIsPopulated;
			Append(std::string("this")) = mThisAttributedObject;
		}
		return *this;
	}

	void Attributed::Populate()
	{
		for (std::uint32_t i = mPopulateCounter; i < mSignatures.Size(); ++i)
		{
			Signature& signature = mSignatures[i];
			Datum& newDatum = Append(signature.mName);
			newDatum.SetType(signature.mType);

			if (signature.mStorage == nullptr)
			{
				for (std::uint32_t datumCounter = 0; datumCounter < signature.mSize; ++datumCounter)
				{
					SetFn[signature.mType](newDatum, signature.mInitialValue, datumCounter);

					if (newDatum.GetType() == Datum::Table)
						Adopt(*newDatum.GetTable(datumCounter), signature.mName, datumCounter);
				}
			}

			else
			{
				SetStorageFn[signature.mType](newDatum, signature.mStorage, signature.mSize);
			}

			++mPopulateCounter;
		}
		mIsPopulated = true;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& key) const
	{
		if (IsAttribute(key))
		{
			Vector<Signature>::Iterator iterator;
			for (iterator = mSignatures.begin(); iterator != mSignatures.end(); ++iterator)
			{
				if ((*iterator).mName == key)
					return true;
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& key) const
	{
		return (IsAttribute(key) && !IsPrescribedAttribute(key));
	}

	bool Attributed::IsAttribute(const std::string& key) const
	{
		if (!mIsPopulated)
			return false;

		return (Find(key) != nullptr);
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& key)
	{
		if (IsPrescribedAttribute(key))
			throw std::exception("Attempting to append a prescribed attribute.");

		if (!mIsPopulated)
			throw std::exception("Cannot append auxiliary attribute before population.");

		return Append(key);
	}

	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return mSignatures.Size();  // this also contains the "this" attribute, so we shouldn't increase the return value by 1
	}
#pragma endregion
}