#include <cxxtest/TestSuite.h>
#include "Vector.h"

using namespace Library;

class VectorTestSuite : public CxxTest::TestSuite
{
public:
	void TestIntVectorInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorCopyConstructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntVector.PushBack(i);

		Vector<uint32_t> otherIntVector = mIntVector;

		// tests for value comparisons
		for (int i = 0; i < 10; i++)
			TS_ASSERT_EQUALS(mIntVector[i], otherIntVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntVector != &otherIntVector);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorAssignmentOperator(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntVector.PushBack(i);

		Vector<uint32_t> otherIntVector;
		otherIntVector = mIntVector;

		// testing for self-assignment
		TS_ASSERT_THROWS_NOTHING(mIntVector = mIntVector);

		// tests for value comparisons
		for (int i = 0; i < 10; i++)
			TS_ASSERT_EQUALS(mIntVector[i], otherIntVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntVector != &otherIntVector);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorDestructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntVector.PushBack(i);

		// tests for list being empty after destructor call
		mIntVector.~Vector();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorIndexOperator(void)
	{
		// tests for correct return values
		for (std::uint32_t i = 0; i < 6; i++)
		{
			mIntVector.PushBack(i);
			TS_ASSERT_EQUALS(mIntVector[i], i);
		}

		try
		{
			std::uint32_t i;
			i = mIntVector[20];
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			std::uint32_t i;
			i = mIntVector[7];
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorConstIndexOperator(void)
	{
		// tests for correct return values
		for (std::uint32_t i = 0; i < 6; i++)
		{
			mIntVector.PushBack(i);
			TS_ASSERT_EQUALS(mIntVector[i], i);
		}

		try
		{
			const std::uint32_t i = mIntVector[20];
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			const std::uint32_t i = mIntVector[7];
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorPushBack(void)
	{
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		mIntVector.PushBack(3);

		// Tests for proper appends and size
		TS_ASSERT_EQUALS(mIntVector[0], 1);
		TS_ASSERT_EQUALS(mIntVector[1], 2);
		TS_ASSERT_EQUALS(mIntVector[2], 3);
		TS_ASSERT_EQUALS(mIntVector.Size(), 3);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorPopBack(void)
	{
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		mIntVector.PushBack(3);

		// Tests for proper resizing after a pop
		mIntVector.PopBack();
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorFront(void)
	{
		try
		{
			std::uint32_t i;
			i = mIntVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntVector.PushBack(1);
		TS_ASSERT_EQUALS(mIntVector.Front(), 1);
		mIntVector.PopBack();

		try
		{
			std::uint32_t i;
			i = mIntVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorConstFront(void)
	{
		try
		{
			const std::uint32_t i = mIntVector.Front();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntVector.PushBack(1);
		TS_ASSERT_EQUALS(mIntVector.Front(), 1);
		mIntVector.PopBack();

		try
		{
			const std::uint32_t i = mIntVector.Front();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorBack(void)
	{
		try
		{
			std::uint32_t i;
			i = mIntVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		TS_ASSERT_EQUALS(mIntVector.Back(), 2);

		// Tests for getting the new back value after a pop
		mIntVector.PopBack();
		TS_ASSERT_EQUALS(mIntVector.Back(), 1);
		mIntVector.PopBack();

		try
		{
			std::uint32_t i;
			i = mIntVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorConstBack(void)
	{
		try
		{
			const std::uint32_t i = mIntVector.Back();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		TS_ASSERT_EQUALS(mIntVector.Back(), 2);

		// Tests for getting the new back value after a pop
		mIntVector.PopBack();
		TS_ASSERT_EQUALS(mIntVector.Back(), 1);
		mIntVector.PopBack();

		try
		{
			const std::uint32_t i = mIntVector.Back();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntVector.PushBack(i);
			TS_ASSERT_EQUALS(mIntVector.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			TS_ASSERT_EQUALS(mIntVector.Size(), 1000 - i);
			mIntVector.PopBack();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntVector.Size(), 0);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorBeginAndEnd(void)
	{
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		mIntVector.PushBack(3);

		// tests for iterator instantiation at the beginning, along with the copy constructor
		Vector<uint32_t>::Iterator iterator = mIntVector.begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, 1);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, 2);
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, 3);

		// Tests for reaching the end of the vector
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntVector.end());

		// Tests the non-equality operator for Iterator by using begin() and end()
		TS_ASSERT(mIntVector.begin() != mIntVector.end());

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorAt(void)
	{
		// putting size at 3 and capacity at 4
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		mIntVector.PushBack(3);

		TS_ASSERT_EQUALS(mIntVector.At(2), 3);  // regular lookup
		TS_ASSERT_EQUALS(mIntVector.At(3), 0);  // this should increase size to 4
		TS_ASSERT_EQUALS(mIntVector.Size(), 4);

		try
		{
			std::uint32_t i;
			i = mIntVector.At(4);
		}
		catch (std::exception& error)
		{
			// tests for the index falling outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorReserve(void)
	{
		// tests for proper reserving of vector space
		mIntVector.Reserve(10);
		TS_ASSERT_EQUALS(mIntVector.At(9), 0);
		TS_ASSERT_EQUALS(mIntVector.Size(), 10);

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorFind(void)
	{
		mIntVector.PushBack(1);
		mIntVector.PushBack(5);
		mIntVector.PushBack(1);
		mIntVector.PushBack(2);
		mIntVector.PushBack(6);
		mIntVector.PushBack(2);
		mIntVector.PushBack(7);
		Vector<uint32_t>::Iterator iterator;

		// tests for finding data in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntVector.Find(6));
		TS_ASSERT_EQUALS(*iterator, 6);

		// tests for finding data earlier in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntVector.Find(5));
		TS_ASSERT_EQUALS(*iterator, 5);

		// tests for finding data from the beginning, instead of duplicate data later on
		TS_ASSERT_THROWS_NOTHING(iterator = mIntVector.Find(1));
		TS_ASSERT_EQUALS(*iterator, 1);
		TS_ASSERT_EQUALS(iterator, mIntVector.begin());

		// tests for finding data at the last index
		TS_ASSERT_THROWS_NOTHING(iterator = mIntVector.Find(7));
		TS_ASSERT_EQUALS(*iterator, 7);

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntVector.Find(9));
		TS_ASSERT_EQUALS(iterator, mIntVector.end());

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntVectorIteratorExceptions(void)
	{
		Vector<uint32_t>::Iterator iterator;
		try
		{
			std::uint32_t i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			++iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			iterator++;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		mIntVector.Reserve(1);
		mIntVector.PushBack(1);
		iterator = mIntVector.begin();
		TS_ASSERT_THROWS_NOTHING(iterator = iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			std::uint32_t i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the capacity (which can only happen if size equals capacity)
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the capacity of the vector!");
		}

		mIntVector.Reserve(5);
		mIntVector.PushBack(2);
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			std::uint32_t i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the size
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the size of the vector!");
		}

		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
	}

	void TestIntPointerVectorInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorCopyConstructor(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*) 0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*) 0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*) 0x33333333);

		Vector<uint32_t*> otherIntPointerVector = mIntPointerVector;

		// tests for value comparisons
		for (int i = 0; i < 3; i++)
			TS_ASSERT_EQUALS(mIntPointerVector[i], otherIntPointerVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntPointerVector != &otherIntPointerVector);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorAssignmentOperator(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*) 0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*) 0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*) 0x33333333);

		Vector<uint32_t*> otherIntPointerVector;
		otherIntPointerVector = mIntPointerVector;

		// testing for self-assignment
		TS_ASSERT_THROWS_NOTHING(mIntPointerVector = mIntPointerVector);

		// tests for value comparisons
		for (int i = 0; i < 3; i++)
			TS_ASSERT_EQUALS(mIntPointerVector[i], otherIntPointerVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntPointerVector != &otherIntPointerVector);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorDestructor(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*) 0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*) 0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*) 0x33333333);

		// tests for list being empty after destructor call
		mIntPointerVector.~Vector();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorIndexOperator(void)
	{
		// tests for correct return values
		mIntPointerVector.PushBack((std::uint32_t*) 0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*) 0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*) 0x33333333);
		mIntPointerVector.PushBack((std::uint32_t*) 0x44444444);
		mIntPointerVector.PushBack((std::uint32_t*) 0x55555555);
		mIntPointerVector.PushBack((std::uint32_t*) 0x66666666);

		TS_ASSERT_EQUALS(mIntPointerVector[0], (std::uint32_t*) 0x11111111);
		TS_ASSERT_EQUALS(mIntPointerVector[1], (std::uint32_t*) 0x22222222);
		TS_ASSERT_EQUALS(mIntPointerVector[2], (std::uint32_t*) 0x33333333);
		TS_ASSERT_EQUALS(mIntPointerVector[3], (std::uint32_t*)0x44444444);
		TS_ASSERT_EQUALS(mIntPointerVector[4], (std::uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerVector[5], (std::uint32_t*)0x66666666);

		try
		{
			std::uint32_t* i;
			i = mIntPointerVector[20];
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			std::uint32_t* i;
			i = mIntPointerVector[7];
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorConstIndexOperator(void)
	{
		// tests for correct return values
		// tests for correct return values
		mIntPointerVector.PushBack((std::uint32_t*) 0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*) 0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*) 0x33333333);
		mIntPointerVector.PushBack((std::uint32_t*) 0x44444444);
		mIntPointerVector.PushBack((std::uint32_t*) 0x55555555);
		mIntPointerVector.PushBack((std::uint32_t*) 0x66666666);

		TS_ASSERT_EQUALS(mIntPointerVector[0], (std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerVector[1], (std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerVector[2], (std::uint32_t*)0x33333333);
		TS_ASSERT_EQUALS(mIntPointerVector[3], (std::uint32_t*)0x44444444);
		TS_ASSERT_EQUALS(mIntPointerVector[4], (std::uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerVector[5], (std::uint32_t*)0x66666666);

		try
		{
			const std::uint32_t* i = mIntPointerVector[20];
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			const std::uint32_t* i = mIntPointerVector[7];
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorPushBack(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x33333333);

		// Tests for proper appends and size
		TS_ASSERT_EQUALS(mIntPointerVector[0], (std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerVector[1], (std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerVector[2], (std::uint32_t*)0x33333333);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 3);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorPopBack(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x33333333);

		// Tests for proper resizing after a pop
		mIntPointerVector.PopBack();
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 2);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorFront(void)
	{
		try
		{
			std::uint32_t* i;
			i = mIntPointerVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), (std::uint32_t*)0x11111111);
		mIntPointerVector.PopBack();

		try
		{
			std::uint32_t* i;
			i = mIntPointerVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorConstFront(void)
	{
		try
		{
			const std::uint32_t* i = mIntPointerVector.Front();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), (std::uint32_t*)0x11111111);
		mIntPointerVector.PopBack();

		try
		{
			const std::uint32_t* i = mIntPointerVector.Front();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorBack(void)
	{
		try
		{
			std::uint32_t* i;
			i = mIntPointerVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), (std::uint32_t*)0x22222222);

		// Tests for getting the new back value after a pop
		mIntPointerVector.PopBack();
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), (std::uint32_t*)0x11111111);
		mIntPointerVector.PopBack();

		try
		{
			std::uint32_t* i;
			i = mIntPointerVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorConstBack(void)
	{
		try
		{
			const std::uint32_t* i = mIntPointerVector.Back();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), (std::uint32_t*)0x22222222);

		// Tests for getting the new back value after a pop
		mIntPointerVector.PopBack();
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), (std::uint32_t*)0x11111111);
		mIntPointerVector.PopBack();

		try
		{
			const std::uint32_t* i = mIntPointerVector.Back();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntPointerVector.PushBack((std::uint32_t*) (4 * i));
			TS_ASSERT_EQUALS(mIntPointerVector.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = mIntPointerVector.Size(); i > 0; i--)
		{
			TS_ASSERT_EQUALS(mIntPointerVector.Size(), i);
			mIntPointerVector.PopBack();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 0);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorBeginAndEnd(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x33333333);

		// tests for iterator instantiation at the beginning, along with the copy constructor
		Vector<uint32_t*>::Iterator iterator = mIntPointerVector.begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x11111111);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x22222222);
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x33333333);

		// Tests for reaching the end of the vector
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntPointerVector.end());

		// Tests the non-equality operator for Iterator by using begin() and end()
		TS_ASSERT(mIntPointerVector.begin() != mIntPointerVector.end());

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorAt(void)
	{
		// putting size at 3 and capacity at 4
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x33333333);

		TS_ASSERT_EQUALS(mIntPointerVector.At(2), (std::uint32_t*) 0x33333333);  // regular lookup
		TS_ASSERT_EQUALS(mIntPointerVector.At(3), nullptr);  // this should increase size to 4
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 4);

		try
		{
			std::uint32_t* i;
			i = mIntPointerVector.At(4);
		}
		catch (std::exception& error)
		{
			// tests for the index falling outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorReserve(void)
	{
		// tests for proper reserving of vector space
		mIntPointerVector.Reserve(10);
		TS_ASSERT_EQUALS(mIntPointerVector.At(9), (std::uint32_t*)0x0);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 10);

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorFind(void)
	{
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x55555555);
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x66666666);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		mIntPointerVector.PushBack((std::uint32_t*)0x77777777);
		Vector<uint32_t*>::Iterator iterator;

		// tests for finding data in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerVector.Find((std::uint32_t*)0x66666666));
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x66666666);

		// tests for finding data earlier in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerVector.Find((std::uint32_t*)0x55555555));
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x55555555);

		// tests for finding data from the beginning, instead of duplicate data later on
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerVector.Find((std::uint32_t*)0x11111111));
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(iterator, mIntPointerVector.begin());

		// tests for finding data at the last index
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerVector.Find((std::uint32_t*)0x77777777));
		TS_ASSERT_EQUALS(*iterator, (std::uint32_t*)0x77777777);

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerVector.Find((std::uint32_t*)0x99999999));
		TS_ASSERT_EQUALS(iterator, mIntPointerVector.end());

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntPointerVectorIteratorExceptions(void)
	{
		Vector<uint32_t*>::Iterator iterator;
		try
		{
			std::uint32_t* i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			++iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			iterator++;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		mIntPointerVector.Reserve(1);
		mIntPointerVector.PushBack((std::uint32_t*)0x11111111);
		iterator = mIntPointerVector.begin();
		TS_ASSERT_THROWS_NOTHING(iterator = iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			std::uint32_t* i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the capacity (which can only happen if size equals capacity)
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the capacity of the vector!");
		}

		mIntPointerVector.Reserve(5);
		mIntPointerVector.PushBack((std::uint32_t*)0x22222222);
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			std::uint32_t* i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the size
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the size of the vector!");
		}

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());
	}

	void TestIntObjectVectorInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorCopyConstructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectVector.PushBack(IntObject(i));

		Vector<IntObject> otherIntObjectVector = mIntObjectVector;

		// tests for value comparisons
		for (int i = 0; i < 10; i++)
			TS_ASSERT_EQUALS(mIntObjectVector[i], otherIntObjectVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntObjectVector != &otherIntObjectVector);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorAssignmentOperator(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectVector.PushBack(IntObject(i));

		Vector<IntObject> otherIntObjectVector;
		otherIntObjectVector = mIntObjectVector;

		// testing for self-assignment
		TS_ASSERT_THROWS_NOTHING(mIntObjectVector = mIntObjectVector);

		// tests for value comparisons
		for (int i = 0; i < 10; i++)
			TS_ASSERT_EQUALS(mIntObjectVector[i], otherIntObjectVector[i]);

		// tests for being a deep copy
		TS_ASSERT(&mIntObjectVector != &otherIntObjectVector);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorDestructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectVector.PushBack(IntObject(i));

		// tests for list being empty after destructor call
		mIntObjectVector.~Vector();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorIndexOperator(void)
	{
		// tests for correct return values
		for (std::uint32_t i = 0; i < 6; i++)
		{
			mIntObjectVector.PushBack(IntObject(i));
			TS_ASSERT_EQUALS(mIntObjectVector[i], IntObject(i));
		}

		try
		{
			IntObject i;
			i = mIntObjectVector[20];
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			IntObject i;
			i = mIntObjectVector[7];
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorConstIndexOperator(void)
	{
		// tests for correct return values
		for (std::uint32_t i = 0; i < 6; i++)
		{
			mIntObjectVector.PushBack(IntObject(i));
			TS_ASSERT_EQUALS(mIntObjectVector[i], IntObject(i));
		}

		try
		{
			const IntObject i = mIntObjectVector[20];
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		try
		{
			const IntObject i = mIntObjectVector[7];
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// the index falls outside the size
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the size of the vector!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorPushBack(void)
	{
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(3));

		// Tests for proper appends and size
		TS_ASSERT_EQUALS(mIntObjectVector[0], IntObject(1));
		TS_ASSERT_EQUALS(mIntObjectVector[1], IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectVector[2], IntObject(3));
		TS_ASSERT_EQUALS(mIntObjectVector.Size(), 3);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorPopBack(void)
	{
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(3));

		// Tests for proper resizing after a pop
		mIntObjectVector.PopBack();
		TS_ASSERT_EQUALS(mIntObjectVector.Size(), 2);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorFront(void)
	{
		try
		{
			IntObject i;
			i = mIntObjectVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntObjectVector.PushBack(IntObject(1));
		TS_ASSERT_EQUALS(mIntObjectVector.Front(), IntObject(1));
		mIntObjectVector.PopBack();

		try
		{
			IntObject i;
			i = mIntObjectVector.Front();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorConstFront(void)
	{
		try
		{
			const IntObject i = mIntObjectVector.Front();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the front value
		mIntObjectVector.PushBack(IntObject(1));
		TS_ASSERT_EQUALS(mIntObjectVector.Front(), IntObject(1));
		mIntObjectVector.PopBack();

		try
		{
			const IntObject i = mIntObjectVector.Front();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorBack(void)
	{
		try
		{
			IntObject i;
			i = mIntObjectVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectVector.Back(), IntObject(2));

		// Tests for getting the new back value after a pop
		mIntObjectVector.PopBack();
		TS_ASSERT_EQUALS(mIntObjectVector.Back(), IntObject(1));
		mIntObjectVector.PopBack();

		try
		{
			IntObject i;
			i = mIntObjectVector.Back();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorConstBack(void)
	{
		try
		{
			const IntObject i = mIntObjectVector.Back();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		// Tests for getting the back value
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectVector.Back(), IntObject(2));

		// Tests for getting the new back value after a pop
		mIntObjectVector.PopBack();
		TS_ASSERT_EQUALS(mIntObjectVector.Back(), IntObject(1));
		mIntObjectVector.PopBack();

		try
		{
			const IntObject i = mIntObjectVector.Back();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "Vector is empty!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntObjectVector.PushBack(IntObject(i));
			TS_ASSERT_EQUALS(mIntObjectVector.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			TS_ASSERT_EQUALS(mIntObjectVector.Size(), 1000 - i);
			mIntObjectVector.PopBack();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntObjectVector.Size(), 0);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorBeginAndEnd(void)
	{
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(3));

		// tests for iterator instantiation at the beginning, along with the copy constructor
		Vector<IntObject>::Iterator iterator = mIntObjectVector.begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, IntObject(1));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, IntObject(2));
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, IntObject(3));

		// Tests for reaching the end of the vector
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntObjectVector.end());

		// Tests the non-equality operator for Iterator by using begin() and end()
		TS_ASSERT(mIntObjectVector.begin() != mIntObjectVector.end());

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorAt(void)
	{
		// putting size at 3 and capacity at 4
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(3));

		TS_ASSERT_EQUALS(mIntObjectVector.At(2), IntObject(3));  // regular lookup
		TS_ASSERT_EQUALS(mIntObjectVector.At(3), IntObject(0));  // this should increase size to 4
		TS_ASSERT_EQUALS(mIntObjectVector.Size(), 4);

		try
		{
			IntObject i;
			i = mIntObjectVector.At(4);
		}
		catch (std::exception& error)
		{
			// tests for the index falling outside the capacity
			TS_ASSERT_EQUALS(error.what(), "Cannot return data that falls outside the capacity of the vector!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorReserve(void)
	{
		// tests for proper reserving of vector space
		mIntObjectVector.Reserve(10);
		TS_ASSERT_EQUALS(mIntObjectVector.At(9), IntObject(0));
		TS_ASSERT_EQUALS(mIntObjectVector.Size(), 10);

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorFind(void)
	{
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(5));
		mIntObjectVector.PushBack(IntObject(1));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(6));
		mIntObjectVector.PushBack(IntObject(2));
		mIntObjectVector.PushBack(IntObject(7));
		Vector<IntObject>::Iterator iterator;

		// tests for finding data in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectVector.Find(IntObject(6)));
		TS_ASSERT_EQUALS(*iterator, IntObject(6));

		// tests for finding data earlier in the vector
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectVector.Find(IntObject(5)));
		TS_ASSERT_EQUALS(*iterator, IntObject(5));

		// tests for finding data from the beginning, instead of duplicate data later on
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectVector.Find(IntObject(1)));
		TS_ASSERT_EQUALS(*iterator, IntObject(1));
		TS_ASSERT_EQUALS(iterator, mIntObjectVector.begin());

		// tests for finding data at the last index
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectVector.Find(IntObject(7)));
		TS_ASSERT_EQUALS(*iterator, IntObject(7));

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectVector.Find(IntObject(9)));
		TS_ASSERT_EQUALS(iterator, mIntObjectVector.end());

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

	void TestIntObjectVectorIteratorExceptions(void)
	{
		Vector<IntObject>::Iterator iterator;
		try
		{
			IntObject i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			++iterator;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		try
		{
			iterator++;
		}
		catch (std::exception& error)
		{
			// the iterator does not have an owner yet
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have an owner!");
		}

		mIntObjectVector.Reserve(1);
		mIntObjectVector.PushBack(IntObject(1));
		iterator = mIntObjectVector.begin();
		TS_ASSERT_THROWS_NOTHING(iterator = iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			IntObject i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the capacity (which can only happen if size equals capacity)
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the capacity of the vector!");
		}

		mIntObjectVector.Reserve(5);
		mIntObjectVector.PushBack(IntObject(2));
		TS_ASSERT_THROWS_NOTHING(++iterator);

		try
		{
			IntObject i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			// tests for the iterator falling outside the size
			TS_ASSERT_EQUALS(error.what(), "This iterator cannot return data that falls outside the size of the vector!");
		}

		mIntObjectVector.Clear();
		TS_ASSERT(mIntObjectVector.IsEmpty());
	}

private:
	class IntObject
	{
	public:
		int mInt;
		int* mAllocatedInt;

		explicit IntObject(int i = 0, int* iPtr = nullptr) : mInt(i), mAllocatedInt(iPtr)
		{
			mAllocatedInt = (int*)malloc(sizeof(int));
		}
		IntObject(const IntObject& rhs) : mInt(rhs.mInt), mAllocatedInt(nullptr)
		{
			mAllocatedInt = (int*)malloc(sizeof(int));
		}
		IntObject& operator=(const IntObject& rhs)
		{
			if (this != &rhs)
			{
				mInt = rhs.mInt;
			}
			return *this;
		}
		~IntObject()
		{
			free(mAllocatedInt);
		}

		bool operator==(const IntObject& iObject) const { return mInt == iObject.mInt; }
	};

	Vector<uint32_t> mIntVector;
	Vector<uint32_t*> mIntPointerVector;
	Vector<IntObject> mIntObjectVector;
};