#include "pch.h"

namespace Library
{
#pragma region AllocFunctions
	void Datum::AllocUnknown(std::uint32_t size)
	{
		throw std::exception("Cannot allocate space for unknown type.");
	}
	void Datum::AllocIntegers(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.iPtr = new int[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.iPtr[counter] = int();
				}
			}
			else
			{
				int* temp = new int[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.iPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = int();
				}
				Clear();
				mDatum.iPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			int* temp = new int[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.iPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = int();
			}
			Clear();
			mDatum.iPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			int* temp = new int[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.iPtr[counter];
			}
			Clear();
			mDatum.iPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocFloats(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.fPtr = new float[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.fPtr[counter] = float();
				}
			}
			else
			{
				float* temp = new float[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.fPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = float();
				}
				Clear();
				mDatum.fPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			float* temp = new float[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.fPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = float();
			}
			Clear();
			mDatum.fPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			float* temp = new float[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.fPtr[counter];
			}
			Clear();
			mDatum.fPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocVectors(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.vPtr = new glm::vec4[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.vPtr[counter] = glm::vec4();
				}
			}
			else
			{
				glm::vec4* temp = new glm::vec4[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.vPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = glm::vec4();
				}
				Clear();
				mDatum.vPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			glm::vec4* temp = new glm::vec4[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.vPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = glm::vec4();
			}
			Clear();
			mDatum.vPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			glm::vec4* temp = new glm::vec4[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.vPtr[counter];
			}
			Clear();
			mDatum.vPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocMatrices(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.mPtr = new glm::mat4[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.mPtr[counter] = glm::mat4();
				}
			}
			else
			{
				glm::mat4* temp = new glm::mat4[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.mPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = glm::mat4();
				}
				Clear();
				mDatum.mPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			glm::mat4* temp = new glm::mat4[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.mPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = glm::mat4();
			}
			Clear();
			mDatum.mPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			glm::mat4* temp = new glm::mat4[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.mPtr[counter];
			}
			Clear();
			mDatum.mPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocTables(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.tPtr = new Scope*[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.tPtr[counter] = nullptr;
				}
			}
			else
			{
				Scope** temp = new Scope*[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.tPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = nullptr;
				}
				Clear();
				mDatum.tPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			Scope** temp = new Scope*[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.tPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = nullptr;
			}
			Clear();
			mDatum.tPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			Scope** temp = new Scope*[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.tPtr[counter];
			}
			Clear();
			mDatum.tPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocStrings(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.sPtr = new std::string[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.sPtr[counter] = std::string();
				}
			}
			else
			{
				std::string* temp = new std::string[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.sPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = std::string();
				}
				Clear();
				mDatum.sPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			std::string* temp = new std::string[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.sPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = std::string();
			}
			Clear();
			mDatum.sPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			std::string* temp = new std::string[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.sPtr[counter];
			}
			Clear();
			mDatum.sPtr = temp;
			mSize = size;
		}
	}
	void Datum::AllocPointers(std::uint32_t size)
	{
		if (mCapacity < size)
		{
			if (mCapacity == 0)
			{
				mDatum.rPtr = new RTTI*[size];
				for (std::uint32_t counter = 0; counter < size; counter++)
				{
					mDatum.rPtr[counter] = nullptr;
				}
			}
			else
			{
				RTTI** temp = new RTTI*[size];
				for (std::uint32_t counter = 0; counter < mSize; counter++)
				{
					temp[counter] = mDatum.rPtr[counter];
				}
				for (std::uint32_t counter = mSize; counter < size; counter++)
				{
					temp[counter] = nullptr;
				}
				Clear();
				mDatum.rPtr = temp;
			}

			mSize = size;
			mCapacity = size;
		}
		else if (mSize < size)
		{
			RTTI** temp = new RTTI*[size];
			for (std::uint32_t counter = 0; counter < mSize; counter++)
			{
				temp[counter] = mDatum.rPtr[counter];
			}
			for (std::uint32_t counter = mSize; counter < size; counter++)
			{
				temp[counter] = nullptr;
			}
			Clear();
			mDatum.rPtr = temp;
			mSize = size;
		}
		else if (mSize > size)
		{
			RTTI** temp = new RTTI*[size];
			for (std::uint32_t counter = 0; counter < size; counter++)
			{
				temp[counter] = mDatum.rPtr[counter];
			}
			Clear();
			mDatum.rPtr = temp;
			mSize = size;
		}
	}

	const Datum::AllocFunction Datum::AllocFn[] = { &Datum::AllocUnknown, &Datum::AllocIntegers, &Datum::AllocFloats, &Datum::AllocVectors,
													&Datum::AllocMatrices, &Datum::AllocTables, &Datum::AllocStrings, &Datum::AllocPointers};
#pragma endregion
#pragma region AssignFunctions
	void Datum::AssignUnknown(const Datum& rhs)
	{
		// we may want to move singular unknown datums around
		if (mSize > 1)
			throw std::exception("Cannot assign to unknown type.");
	}
	void Datum::AssignIntegers(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.iPtr[counter] = rhs.mDatum.iPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.iPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.iPtr[counter] = rhs.mDatum.iPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.iPtr, rhs.mSize);
		}
	}
	void Datum::AssignFloats(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.fPtr[counter] = rhs.mDatum.fPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.fPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.fPtr[counter] = rhs.mDatum.fPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.fPtr, rhs.mSize);
		}
	}
	void Datum::AssignVectors(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.vPtr[counter] = rhs.mDatum.vPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.vPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.vPtr[counter] = rhs.mDatum.vPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.vPtr, rhs.mSize);
		}
	}
	void Datum::AssignMatrices(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.mPtr[counter] = rhs.mDatum.mPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.mPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.mPtr[counter] = rhs.mDatum.mPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.mPtr, rhs.mSize);
		}
	}
	void Datum::AssignTables(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.tPtr[counter] = rhs.mDatum.tPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.tPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.tPtr[counter] = rhs.mDatum.tPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.tPtr, rhs.mSize);
		}
	}
	void Datum::AssignStrings(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.sPtr[counter] = rhs.mDatum.sPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.sPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.sPtr[counter] = rhs.mDatum.sPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.sPtr, rhs.mSize);
		}
	}
	void Datum::AssignPointers(const Datum& rhs)
	{
		if (!mIsExternal && !rhs.mIsExternal)
		{
			SetSize(rhs.mSize);
			mCapacity = mSize;
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.rPtr[counter] = rhs.mDatum.rPtr[counter];
			}
		}
		else if (!mIsExternal && rhs.mIsExternal)
		{
			SetStorage(rhs.mDatum.rPtr, rhs.mSize);
		}
		else if (mIsExternal && !rhs.mIsExternal)
		{
			if (mSize != rhs.mSize)
				throw std::exception("Left-hand datum must have same size as right-hand datum!");

			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				mDatum.rPtr[counter] = rhs.mDatum.rPtr[counter];
			}
		}
		else
		{
			SetStorage(rhs.mDatum.rPtr, rhs.mSize);
		}
	}

	const Datum::AssignFunction Datum::AssignFn[] = { &Datum::AssignUnknown, &Datum::AssignIntegers, &Datum::AssignFloats, &Datum::AssignVectors,
													  &Datum::AssignMatrices, &Datum::AssignTables, &Datum::AssignStrings, &Datum::AssignPointers };
#pragma endregion
#pragma region CompareFunctions
	bool Datum::CompareUnknown(const Datum& rhs) const
	{
		throw std::exception("Cannot compare unknown types!");
	}
	bool Datum::CompareIntegers(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.iPtr == *rhs.mDatum.iPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.iPtr[counter] != rhs.mDatum.iPtr[counter])
					return false;
			}
		}
		return true;
	}
	bool Datum::CompareFloats(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.fPtr == *rhs.mDatum.fPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.fPtr[counter] != rhs.mDatum.fPtr[counter])
					return false;
			}
		}
		return true;
	}
	bool Datum::CompareVectors(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.vPtr == *rhs.mDatum.vPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.vPtr[counter] != rhs.mDatum.vPtr[counter])
					return false;
			}
		}
		return true;
	}
	bool Datum::CompareMatrices(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.mPtr == *rhs.mDatum.mPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.mPtr[counter] != rhs.mDatum.mPtr[counter])
					return false;
			}
		}
		return true;
	}
	bool Datum::CompareTables(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.tPtr == *rhs.mDatum.tPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.tPtr[counter] != rhs.mDatum.tPtr[counter])
					return false;
			}
		}
		return true;
	}
	bool Datum::CompareStrings(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.sPtr).compare(*rhs.mDatum.sPtr) == 0;

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.sPtr[counter].compare(rhs.mDatum.sPtr[counter]) != 0)
					return false;
			}
		}
		return true;
	}
	bool Datum::ComparePointers(const Datum& rhs) const
	{
		if (mSize == 1)
			return (*mDatum.rPtr == *rhs.mDatum.rPtr);

		else
		{
			for (std::uint32_t counter = 0; counter < mSize; ++counter)
			{
				if (mDatum.rPtr[counter] != rhs.mDatum.rPtr[counter])
					return false;
			}
		}
		return true;
	}

	const Datum::CompareFunction Datum::CompareFn[] = { &Datum::CompareUnknown, &Datum::CompareIntegers, &Datum::CompareFloats, &Datum::CompareVectors,
														&Datum::CompareMatrices, &Datum::CompareTables, &Datum::CompareStrings, &Datum::ComparePointers };
#pragma endregion
#pragma region ClearFunctions
	void Datum::ClearUnknown() { throw std::exception("Cannot deallocate invalid type."); }
	void Datum::ClearIntegers() { delete[] mDatum.iPtr; }
	void Datum::ClearFloats() { delete[] mDatum.fPtr; }
	void Datum::ClearVectors() { delete[] mDatum.vPtr; }
	void Datum::ClearMatrices() { delete[] mDatum.mPtr; }
	void Datum::ClearStrings() { delete[] mDatum.sPtr; }
	void Datum::ClearPointers() { delete[] mDatum.rPtr; }

	const Datum::ClearFunction Datum::ClearFn[] = {&Datum::ClearUnknown, &Datum::ClearIntegers, &Datum::ClearFloats, &Datum::ClearVectors, 
												   &Datum::ClearMatrices, &Datum::ClearPointers, &Datum::ClearStrings, &Datum::ClearPointers};
#pragma endregion
#pragma region SetStringFunctions
	void Datum::SetUnknownFromString(std::string s, std::uint32_t index)
	{
		throw std::exception("Cannot set unknown type from string.");
	}
	void Datum::SetIntegersFromString(std::string s, std::uint32_t index)
	{
		int i;
		int result = sscanf_s(s.c_str(), "%d", &i);
		if (result != 1)
			throw std::exception("Cannot parse integer from string.");

		Set(i, index);
	}
	void Datum::SetFloatsFromString(std::string s, std::uint32_t index)
	{
		float f;
		int result = sscanf_s(s.c_str(), "%f", &f);
		if (result != 1)
			throw std::exception("Cannot parse float from string.");

		Set(f, index);
	}
	void Datum::SetVectorsFromString(std::string s, std::uint32_t index)
	{
		glm::vec4 v;
		int result = sscanf_s(s.c_str(), "%f %f %f %f", &v.x, &v.y, &v.z, &v.w);
		if (result != 4)
			throw std::exception("Cannot parse vector from string.");

		Set(v, index);
	}
	void Datum::SetMatricesFromString(std::string s, std::uint32_t index)
	{
		glm::mat4 m;
		int result = sscanf_s(s.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &m[0][0], &m[0][1], &m[0][2], &m[0][3], &m[1][0], &m[1][1], &m[1][2], &m[1][3], &m[2][0], &m[2][1], &m[2][2], &m[2][3], &m[3][0], &m[3][1], &m[3][2], &m[3][3]);
		if (result != 16)
			throw std::exception("Cannot parse matrix from string.");

		Set(m, index);
	}
	void Datum::SetStringsFromString(std::string s, std::uint32_t index)
	{
		Set(s, index);
	}
	void Datum::SetPointersFromString(std::string s, std::uint32_t index)
	{
		RTTI* r = nullptr;
		std::uint32_t tempInt;
		int result = sscanf_s(s.c_str(), "%u", &tempInt);
		if (result != 1)
			throw std::exception("Cannot parse pointer from string.");

		r = (RTTI*)tempInt;
		Set(r, index);
	}

	const Datum::SetFromStringFunction Datum::SetStringFn[] = { &Datum::SetUnknownFromString, &Datum::SetIntegersFromString, &Datum::SetFloatsFromString, &Datum::SetVectorsFromString,
																&Datum::SetMatricesFromString, &Datum::SetPointersFromString, &Datum::SetStringsFromString, &Datum::SetPointersFromString };
#pragma endregion
#pragma region ToStringFunctions
	std::string Datum::UnknownToString(std::uint32_t index) const
	{
		throw std::exception("Cannot set a string from an unknown type.");
	}
	std::string Datum::IntegersToString(std::uint32_t index) const
	{
		char buffer[50];
		int i = GetInteger(index);
		sprintf_s(buffer, sizeof(buffer), "%d", i);
		return std::string(buffer);
	}
	std::string Datum::FloatsToString(std::uint32_t index) const
	{
		char buffer[50];
		float f = GetFloat(index);
		sprintf_s(buffer, sizeof(buffer), "%.1f", f);
		return std::string(buffer);
	}
	std::string Datum::VectorsToString(std::uint32_t index) const
	{
		char buffer[200];
		glm::vec4 v = GetVector(index);
		sprintf_s(buffer, sizeof(buffer), "<%.1f %.1f %.1f %.1f>", v.x, v.y, v.z, v.w);
		return std::string(buffer);
	}
	std::string Datum::MatricesToString(std::uint32_t index) const
	{
		char buffer[500];
		glm::mat4 m = GetMatrix(index);
		sprintf_s(buffer, sizeof(buffer), "[%.1f %.1f %.1f %.1f\n %.1f %.1f %.1f %.1f\n %.1f %.1f %.1f %.1f\n %.1f %.1f %.1f %.1f]", m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
		return std::string(buffer);
	}
	std::string Datum::StringsToString(std::uint32_t index) const
	{
		return GetString(index);
	}
	std::string Datum::PointersToString(std::uint32_t index) const
	{
		char buffer[50];
		RTTI* r = GetPointer(index);
		sprintf_s(buffer, sizeof(buffer), "0x%X", (std::uint32_t) r);
		return std::string(buffer);
	}
	
	const Datum::ToStringFunction Datum::ToStringFn[] = { &Datum::UnknownToString, &Datum::IntegersToString, &Datum::FloatsToString, &Datum::VectorsToString,
														  &Datum::MatricesToString, &Datum::PointersToString, &Datum::StringsToString, &Datum::PointersToString };
#pragma endregion

	Datum::Datum(Datum::DatumType type, std::uint32_t size) : mType(type), mDatum(), mSize(0), mCapacity(0), mIsExternal(false) 
	{
		if (size != 0)
			SetSize(size);
	}

	Datum::Datum(const Datum& rhs) : mType(Unknown), mDatum(), mSize(0), mCapacity(0), mIsExternal(false)
	{
		operator=(rhs);
	}

	Datum::~Datum()
	{
		Clear();
	}
#pragma region AssignmentOperator
	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			SetType(rhs.mType);
			(this->*AssignFn[mType])(rhs);
		}

		return *this;
	}

	Datum& Datum::operator=(const int& rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(const float& rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(Scope* rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}

	Datum& Datum::operator=(RTTI* rhs)
	{
		if (mSize > 1)
			throw std::exception("Datum must have a size of 0 or 1!");

		Set(rhs);
		return *this;
	}
#pragma endregion
#pragma region ComparisonOperator
	bool Datum::operator==(const Datum& rhs) const
	{
		if (mType != rhs.mType)
			throw std::exception("Both values must be of same type!");

		if (mSize != rhs.mSize)
			return false;

		return (this->*CompareFn[mType])(rhs);
	}
	bool Datum::operator==(const int& rhs) const
	{
		if (mType != Integer)
			throw std::exception("Datum is not of type int!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.iPtr[0] == rhs;
	}
	bool Datum::operator==(const float& rhs) const
	{
		if (mType != Float)
			throw std::exception("Datum is not of type float!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.fPtr[0] == rhs;
	}
	bool Datum::operator==(const glm::vec4& rhs) const
	{
		if (mType != Vector)
			throw std::exception("Datum is not of type glm::vec4!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.vPtr[0] == rhs;
	}
	bool Datum::operator==(const glm::mat4& rhs) const
	{
		if (mType != Matrix)
			throw std::exception("Datum is not of type glm::mat4!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.mPtr[0] == rhs;
	}
	bool Datum::operator==(const Scope* rhs) const
	{
		if (mType != Pointer)
			throw std::exception("Datum is not a pointer type!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.tPtr[0] == rhs;
	}
	bool Datum::operator==(const std::string& rhs) const
	{
		if (mType != String)
			throw std::exception("Datum is not of type std::string!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.sPtr[0] == rhs;
	}
	bool Datum::operator==(const RTTI* rhs) const
	{
		if (mType != Pointer)
			throw std::exception("Datum is not a pointer type!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.rPtr[0] == rhs;
	}
	bool Datum::operator!=(const Datum& rhs) const
	{
		if (mType != rhs.mType)
			throw std::exception("Both values must be of same type!");
		if (mSize != rhs.mSize)
			return true;

		return !(this->*CompareFn[mType])(rhs);
	}
	bool Datum::operator!=(const int& rhs) const
	{
		if (mType != Integer)
			throw std::exception("Datum is not of type int!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.iPtr[0] != rhs;
	}
	bool Datum::operator!=(const float& rhs) const
	{
		if (mType != Float)
			throw std::exception("Datum is not of type float!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.fPtr[0] != rhs;
	}
	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		if (mType != Vector)
			throw std::exception("Datum is not of type glm::vec4!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.vPtr[0] != rhs;
	}
	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		if (mType != Matrix)
			throw std::exception("Datum is not of type glm::mat4!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.mPtr[0] != rhs;
	}
	bool Datum::operator!=(const Scope* rhs) const
	{
		if (mType != Pointer)
			throw std::exception("Datum is not a pointer type!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.tPtr[0] != rhs;
	}
	bool Datum::operator!=(const std::string& rhs) const
	{
		if (mType != String)
			throw std::exception("Datum is not of type std::string!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.sPtr[0] != rhs;
	}
	bool Datum::operator!=(const RTTI* rhs) const
	{
		if (mType != Pointer)
			throw std::exception("Datum is not a pointer type!");
		if (mSize != 1)
			throw std::exception("Datum must have a size of 1!");

		return mDatum.rPtr[0] != rhs;
	}
#pragma endregion

	Scope& Datum::operator[](std::uint32_t index)
	{
		return *GetTable(index);
	}

	Datum::DatumType Datum::GetType() const
	{
		return mType;
	}

	bool Datum::IsExternal() const
	{
		return mIsExternal;
	}

	void Datum::SetType(Datum::DatumType type)
	{
		if (mType != Unknown && mType != type)
			throw std::exception("Type has already been set!");

		mType = type;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::SetSize(std::uint32_t size)
	{
		if (mIsExternal && mSize != size)
			throw std::exception("Cannot resize external storage!");

		(this->*AllocFn[mType])(size);
	}

	void Datum::Clear()
	{
		if (mDatum.iPtr != nullptr && !mIsExternal)
		{
			(this->*ClearFn[mType])();
			mDatum.iPtr = nullptr;
			mSize = 0;
		}
	}
#pragma region SetStorage
	void Datum::SetStorage(int* intArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Integer);
		Clear();

		mDatum.iPtr = intArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(float* floatArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Float);
		Clear();

		mDatum.fPtr = floatArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::vec4* vectorArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Vector);
		Clear();

		mDatum.vPtr = vectorArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::mat4* matrixArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Matrix);
		Clear();

		mDatum.mPtr = matrixArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}
	void Datum::SetStorage(Scope** tableArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Table);
		Clear();

		mDatum.tPtr = tableArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}
	void Datum::SetStorage(std::string* stringArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(String);
		Clear();

		mDatum.sPtr = stringArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(RTTI** pointerArray, std::uint32_t size)
	{
		if (size == 0)
			throw std::exception("Incoming data must be at least a size of 1.");

		SetType(Pointer);
		Clear();

		mDatum.rPtr = pointerArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}
#pragma endregion
#pragma region Set
	void Datum::Set(const int& value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Integer);
		else if (mType != Integer)
			throw std::exception("Value needs to be of type int.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.iPtr[index] = value;
	}

	void Datum::Set(const float& value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Float);
		else if (mType != Float)
			throw std::exception("Value needs to be of type float.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.fPtr[index] = value;
	}
	
	void Datum::Set(const glm::vec4& value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Vector);
		else if (mType != Vector)
			throw std::exception("Value needs to be of type glm::vec4.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.vPtr[index] = value;
	}

	void Datum::Set(const glm::mat4& value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Matrix);
		else if (mType != Matrix)
			throw std::exception("Value needs to be of type glm::mat4.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.mPtr[index] = value;
	}

	void Datum::Set(Scope* value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Table);
		else if (mType != Table)
			throw std::exception("Value needs to be a table type.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.tPtr[index] = value;
	}

	void Datum::Set(const std::string& value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(String);
		else if (mType != String)
			throw std::exception("Value needs to be of type std::string.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.sPtr[index] = value;
	}

	void Datum::Set(RTTI* value, std::uint32_t index)
	{
		if (mType == Unknown)
			SetType(Pointer);
		else if (mType != Pointer)
			throw std::exception("Value needs to be a pointer type.");

		if (index + 1 > mSize)
		{
			SetSize(index + 1);
		}

		mDatum.rPtr[index] = value;
	}
#pragma endregion
#pragma region Get
	int& Datum::GetInteger(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Integer)
			throw std::exception("This is not an integer datum.");

		return mDatum.iPtr[index];
	}

	float& Datum::GetFloat(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Float)
			throw std::exception("This is not a float datum.");

		return mDatum.fPtr[index];
	}

	glm::vec4& Datum::GetVector(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Vector)
			throw std::exception("This is not a vector datum.");

		return mDatum.vPtr[index];
	}

	glm::mat4& Datum::GetMatrix(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Matrix)
			throw std::exception("This is not a matrix datum.");

		return mDatum.mPtr[index];
	}

	Scope*& Datum::GetTable(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Table)
			throw std::exception("This is not a table datum.");

		return mDatum.tPtr[index];
	}

	std::string& Datum::GetString(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != String)
			throw std::exception("This is not a string datum.");

		return mDatum.sPtr[index];
	}

	RTTI*& Datum::GetPointer(std::uint32_t index) const
	{
		if (mSize < index + 1)
			throw std::exception("Index is too large.");
		if (mType != Pointer)
			throw std::exception("This is not a pointer datum.");

		return mDatum.rPtr[index];
	}
#pragma endregion

	void Datum::SetFromString(std::string s, std::uint32_t index)
	{
		(this->*SetStringFn[mType])(s, index);
	}
	
	std::string Datum::ToString(std::uint32_t index) const
	{
		return (this->*ToStringFn[mType])(index);
	}
}