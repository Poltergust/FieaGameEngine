#include <cxxtest/TestSuite.h>
#include "SList.h"

using namespace Library;

class SListTestSuite : public CxxTest::TestSuite
{
public:
	void TestIntSListInstantiation(void)
	{
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
		TS_ASSERT(mIntList.IsEmpty());

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntList.Front());
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntList.Back())
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
	}

	void TestIntSListInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(4));
		TS_ASSERT_EQUALS(mIntList.Front(), 4);
		TS_ASSERT_EQUALS(mIntList.Back(), 4);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(7));
		TS_ASSERT_EQUALS(mIntList.Front(), 7);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(4));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(3));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(6));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(1));
		TS_ASSERT_EQUALS(mIntList.Front(), 1);
		TS_ASSERT_EQUALS(mIntList.Back(), 3);
		TS_ASSERT_EQUALS(mIntList.Size(), 4);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Front(), 6);
		TS_ASSERT_EQUALS(mIntList.Back(), 3);
		TS_ASSERT_EQUALS(mIntList.Size(), 3);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
	}

	void TestIntSListDuplicateInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(7));
		TS_ASSERT_EQUALS(mIntList.Front(), 8);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);
		TS_ASSERT_EQUALS(mIntList.Size(), 8);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Front(), 8);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);
		TS_ASSERT_EQUALS(mIntList.Size(), 7);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Front(), 7);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
	}

	void TestIntSListCopyConstructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(9));
		SList<uint32_t> intListToCopy(mIntList);
		TS_ASSERT_EQUALS(mIntList.Front(), 5);
		TS_ASSERT_EQUALS(mIntList.Back(), 9);
		TS_ASSERT_EQUALS(mIntList.Front(), intListToCopy.Front());
		TS_ASSERT_EQUALS(mIntList.Back(), intListToCopy.Back());
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Front(), 9);
		TS_ASSERT_EQUALS(intListToCopy.Front(), 5);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
	}

	void TestIntSListAssignmentOperator(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(9));
		TS_ASSERT_THROWS_NOTHING(mIntList = mIntList);
		SList<uint32_t> intListToCopy;
		TS_ASSERT_THROWS_NOTHING(intListToCopy = mIntList);
		TS_ASSERT_EQUALS(mIntList.Front(), 5);
		TS_ASSERT_EQUALS(mIntList.Back(), 9);
		TS_ASSERT_EQUALS(mIntList.Front(), intListToCopy.Front());
		TS_ASSERT_EQUALS(mIntList.Back(), intListToCopy.Back());
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntList.PopFront());
		TS_ASSERT_EQUALS(mIntList.Front(), 9);
		TS_ASSERT_EQUALS(intListToCopy.Front(), 5);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT_EQUALS(intListToCopy.Size(), 2);
	}

	void TestIntSListDestructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(2));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(3));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(4));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushFront(6));
		TS_ASSERT_THROWS_NOTHING(mIntList.~mIntList());
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
	}

	void TestIntPointerSListInstantiation(void)
	{
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);
		TS_ASSERT(mIntPointerList.IsEmpty());

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Front());
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Back())
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
	}

	void TestIntPointerSListInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x77777777));
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x44444444));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x33333333));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x66666666));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x11111111));
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x33333333);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 4);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x66666666);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x33333333);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 3);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);
	}

	void TestIntPointerSListDuplicateInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x77777777));
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x88888888);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 8);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x88888888);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 7);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x77777777);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);
	}

	void TestIntPointerSListCopyConstructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x99999999));
		SList<uint32_t*> intPointerListToCopy(mIntPointerList);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x99999999);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), intPointerListToCopy.Front());
		TS_ASSERT_EQUALS(mIntPointerList.Back(), intPointerListToCopy.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x99999999);
		TS_ASSERT_EQUALS(intPointerListToCopy.Front(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
	}

	void TestIntPointerSListAssignmentOperator(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x99999999));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList = mIntPointerList);
		SList<uint32_t*> intPointerListToCopy;
		TS_ASSERT_THROWS_NOTHING(intPointerListToCopy = mIntPointerList);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), (uint32_t*)0x99999999);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), intPointerListToCopy.Front());
		TS_ASSERT_EQUALS(mIntPointerList.Back(), intPointerListToCopy.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PopFront());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), (uint32_t*)0x99999999);
		TS_ASSERT_EQUALS(intPointerListToCopy.Front(), (uint32_t*)0x55555555);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT_EQUALS(intPointerListToCopy.Size(), 2);
	}

	void TestIntPointerSListDestructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x33333333));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x44444444));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushFront((uint32_t*)0x66666666));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.~mIntPointerList());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);
	}

	void TestIntObjectSListInstantiation(void)
	{
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);
		TS_ASSERT(mIntObjectList.IsEmpty());

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntObjectList.Front());
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		try
		{
			TS_ASSERT_THROWS_ANYTHING(mIntObjectList.Back())
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "List is empty!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
	}

	void TestIntObjectSListInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(4)));
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 4);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 4);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(7)));
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(4)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(3)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(6)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(1)));
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 1);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 3);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 4);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 6);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 3);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 3);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);
	}

	void TestIntObjectSListDuplicateInsertions(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(7)));
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 8);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 8);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 8);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 7);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 7);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 1);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);
	}

	void TestIntObjectSListCopyConstructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(9)));
		SList<IntObject> intObjectListToCopy(mIntObjectList);
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 5);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 9);
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, intObjectListToCopy.Front().mInt);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, intObjectListToCopy.Back().mInt);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 2);
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 9);
		TS_ASSERT_EQUALS(intObjectListToCopy.Front().mInt, 5);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 1);
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
	}

	void TestIntObjectSListAssignmentOperator(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(9)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList = mIntObjectList);
		SList<IntObject> intObjectListToCopy;
		TS_ASSERT_THROWS_NOTHING(intObjectListToCopy = mIntObjectList);
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 5);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, 9);
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, intObjectListToCopy.Front().mInt);
		TS_ASSERT_EQUALS(mIntObjectList.Back().mInt, intObjectListToCopy.Back().mInt);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 2);
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PopFront());
		TS_ASSERT_EQUALS(mIntObjectList.Front().mInt, 9);
		TS_ASSERT_EQUALS(intObjectListToCopy.Front().mInt, 5);
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 1);
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT_EQUALS(intObjectListToCopy.Size(), 2);
	}

	void TestIntObjectSListDestructor(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(3)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(4)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushFront(IntObject(6)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.~mIntObjectList());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 0);
	}

	// ALL NEW TESTS FOR ASSIGNMENT 3 BEGIN AT THIS POINT!

	void TestIntSListBegin(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(7));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(9));

		// tests for iterator instantiation at the beginning, along with the copy constructor
		SList<uint32_t>::Iterator iterator = mIntList.Begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, 7);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, 8);
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, 9);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntList.End());
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
	}

	void TestIntSListEnd(void)
	{
		// tests for correct behavior for an iterator at the end of a list
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(7));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(8));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(9));
		SList<uint32_t>::Iterator iterator;

		// tests for the iterator assignment operator
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.End());

		try
		{
			uint32_t i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have a Node attached to it!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
	}

	void TestIntSListInsertAfter(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(3));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(6));
		SList<uint32_t>::Iterator iterator;

		// tests for inserting at the beginning of the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(2, iterator));

		// tests for inserting at the middle of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(4, iterator));

		// tests for inserting immediately after another insertion
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(5, iterator));

		// tests for inserting when iterator is on the last node
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(7, iterator));

		// tests for inserting when iterator is past the end of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(8, iterator));

		// tests for correct size
		TS_ASSERT_EQUALS(mIntList.Size(), 8);

		// tests for proper list order
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		for (uint32_t i = 1; iterator != mIntList.End(); i++, iterator++)
		{
			TS_ASSERT_EQUALS(*iterator, i);
		}
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT(mIntList.IsEmpty());

		// tests for inserting into an empty linked list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntList.InsertAfter(3, iterator));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_EQUALS(*iterator, 3);
		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT(mIntList.IsEmpty());
	}

	void TestIntSListFind(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(2));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(6));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(2));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(7));
		SList<uint32_t>::Iterator iterator;

		// tests for finding data in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(6));
		TS_ASSERT_EQUALS(*iterator, 6);

		// tests for finding data earlier in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(5));
		TS_ASSERT_EQUALS(*iterator, 5);

		// tests for finding data at the beginning
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(1));
		TS_ASSERT_EQUALS(*iterator, 1);
		TS_ASSERT_EQUALS(iterator, mIntList.Begin());

		// tests for finding data at the last node
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(7));
		TS_ASSERT_EQUALS(*iterator, 7);

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(9));
		TS_ASSERT_EQUALS(iterator, mIntList.End());

		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
	}

	void TestIntSListRemove(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(2));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(6));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(2));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(7));
		SList<uint32_t>::Iterator iterator;

		// tests for removal of data from linked list
		TS_ASSERT_THROWS_NOTHING(mIntList.Remove(6));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Find(6));
		TS_ASSERT_EQUALS(iterator, mIntList.End());
		TS_ASSERT_EQUALS(mIntList.Size(), 6);

		// tests for removing the first equal data in the linked list
		TS_ASSERT_THROWS_NOTHING(mIntList.Remove(1));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_EQUALS(*iterator, 5);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, 1);

		// tests for proper ordering
		TS_ASSERT_THROWS_NOTHING(mIntList.Remove(2));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, 2);

		// tests for removal at end of list with the iterator being at the 2nd-to-last node
		TS_ASSERT_THROWS_NOTHING(mIntList.Remove(7));
		TS_ASSERT_EQUALS(*iterator, mIntList.Back());

		// tests for removal of data that is not in linked list
		TS_ASSERT_THROWS_NOTHING(mIntList.Remove(9));

		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT(mIntList.IsEmpty());
	}

	void TestIntIteratorComparisonOperators(void)
	{
		SList<uint32_t>::Iterator iterator;
		SList<uint32_t>::Iterator otherIterator;
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(5));
		TS_ASSERT_THROWS_NOTHING(mIntList.PushBack(1));

		// tests for equality between two uninitialized iterators
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to the same node in the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntList.Begin());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to no node, but are part of the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.End());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntList.End());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical data within the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntList.Begin());
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT(iterator != otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical, but are in two different lists
		SList<uint32_t> otherIntList = mIntList;
		TS_ASSERT_THROWS_NOTHING(otherIterator = otherIntList.Begin());
		TS_ASSERT(iterator != otherIterator);

		TS_ASSERT_THROWS_NOTHING(mIntList.Clear());
		TS_ASSERT(mIntList.IsEmpty());
	}

	void TestIntPointerSListBegin(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x77777777));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x99999999));

		// tests for iterator instantiation at the beginning, along with the copy constructor
		SList<uint32_t*>::Iterator iterator = mIntPointerList.Begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x77777777);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x88888888);
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x99999999);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntPointerList.End());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
	}

	void TestIntPointerSListEnd(void)
	{
		// tests for correct behavior for an iterator at the end of a list
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x77777777));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x88888888));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x99999999));
		SList<uint32_t*>::Iterator iterator;

		// tests for the iterator assignment operator
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.End());

		try
		{
			uint32_t* i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have a Node attached to it!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
	}

	void TestIntPointerSListInsertAfter(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x33333333));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x66666666));
		SList<uint32_t*>::Iterator iterator;

		// tests for inserting at the beginning of the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x22222222, iterator));

		// tests for inserting at the middle of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x44444444, iterator));

		// tests for inserting immediately after another insertion
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x55555555, iterator));

		// tests for inserting when iterator is on the last node
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x77777777, iterator));

		// tests for inserting when iterator is past the end of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x88888888, iterator));

		// tests for correct size
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 8);

		// tests for proper list order
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		for (uint32_t i = 0x1; iterator != mIntPointerList.End(); i++, iterator++)
		{
			TS_ASSERT_EQUALS(*iterator, (uint32_t*)(i * 0x11111111));
		}
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT(mIntPointerList.IsEmpty());

		// tests for inserting into an empty linked list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.InsertAfter((uint32_t*)0x33333333, iterator));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x33333333);
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT(mIntPointerList.IsEmpty());
	}

	void TestIntPointerSListFind(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x66666666));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x77777777));
		SList<uint32_t*>::Iterator iterator;

		// tests for finding data in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x66666666));
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x66666666);

		// tests for finding data earlier in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x55555555));
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x55555555);

		// tests for finding data at the beginning
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x11111111));
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(iterator, mIntPointerList.Begin());

		// tests for finding data at the last node
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x77777777));
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x77777777);

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x99999999));
		TS_ASSERT_EQUALS(iterator, mIntPointerList.End());

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
	}

	void TestIntPointerSListRemove(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x66666666));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x77777777));
		SList<uint32_t*>::Iterator iterator;

		// tests for removal of data from linked list
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Remove((uint32_t*)0x66666666));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Find((uint32_t*)0x66666666));
		TS_ASSERT_EQUALS(iterator, mIntPointerList.End());
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 6);

		// tests for removing the first equal data in the linked list
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Remove((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x55555555);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x11111111);

		// tests for proper ordering
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Remove((uint32_t*)0x22222222));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, (uint32_t*)0x22222222);

		// tests for removal at end of list with the iterator being at the 2nd-to-last node
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Remove((uint32_t*)0x77777777));
		TS_ASSERT_EQUALS(*iterator, mIntPointerList.Back());

		// tests for removal of data that is not in linked list
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Remove((uint32_t*)0x99999999));

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT(mIntPointerList.IsEmpty());
	}

	void TestIntPointerIteratorComparisonOperators(void)
	{
		SList<uint32_t*>::Iterator iterator;
		SList<uint32_t*>::Iterator otherIterator;
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x55555555));
		TS_ASSERT_THROWS_NOTHING(mIntPointerList.PushBack((uint32_t*)0x11111111));

		// tests for equality between two uninitialized iterators
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to the same node in the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntPointerList.Begin());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to no node, but are part of the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.End());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntPointerList.End());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical data within the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntPointerList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntPointerList.Begin());
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT(iterator != otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical, but are in two different lists
		SList<uint32_t*> otherIntPointerList = mIntPointerList;
		TS_ASSERT_THROWS_NOTHING(otherIterator = otherIntPointerList.Begin());
		TS_ASSERT(iterator != otherIterator);

		TS_ASSERT_THROWS_NOTHING(mIntPointerList.Clear());
		TS_ASSERT(mIntPointerList.IsEmpty());
	}

	void TestIntObjectPointerSListBegin(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(7)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(9)));

		// tests for iterator instantiation at the beginning, along with the copy constructor
		SList<IntObject>::Iterator iterator = mIntObjectList.Begin();

		// tests for proper traversal through the list using prefix and postfix increments
		TS_ASSERT_EQUALS(*iterator, IntObject(7));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, IntObject(8));
		TS_ASSERT_THROWS_NOTHING(iterator++);
		TS_ASSERT_EQUALS(*iterator, IntObject(9));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(iterator, mIntObjectList.End());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
	}

	void TestIntObjectPointerSListEnd(void)
	{
		// tests for correct behavior for an iterator at the end of a list
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(7)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(8)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(9)));
		SList<IntObject>::Iterator iterator;

		// tests for the iterator assignment operator
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.End());

		try
		{
			IntObject i;
			i = *iterator;
		}
		catch (std::exception& error)
		{
			TS_ASSERT_EQUALS(error.what(), "This iterator does not have a Node attached to it!");
		}

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
	}

	void TestIntObjectSListInsertAfter(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(3)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(6)));
		SList<IntObject>::Iterator iterator;

		// tests for inserting at the beginning of the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(2), iterator));

		// tests for inserting at the middle of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(4), iterator));

		// tests for inserting immediately after another insertion
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(5), iterator));

		// tests for inserting when iterator is on the last node
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(7), iterator));

		// tests for inserting when iterator is past the end of the list
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(8), iterator));

		// tests for correct size
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 8);

		// tests for proper list order
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		for (uint32_t i = 1; iterator != mIntObjectList.End(); i++, iterator++)
		{
			TS_ASSERT_EQUALS(*iterator, IntObject(i));
		}
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT(mIntObjectList.IsEmpty());

		// tests for inserting into an empty linked list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.InsertAfter(IntObject(3), iterator));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_EQUALS(*iterator, IntObject(3));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT(mIntObjectList.IsEmpty());
	}

	void TestIntObjectSListFind(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(6)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(7)));
		SList<IntObject>::Iterator iterator;

		// tests for finding data in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(6)));
		TS_ASSERT_EQUALS(*iterator, IntObject(6));

		// tests for finding data earlier in the list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(5)));
		TS_ASSERT_EQUALS(*iterator, IntObject(5));

		// tests for finding data at the beginning
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(1)));
		TS_ASSERT_EQUALS(*iterator, IntObject(1));
		TS_ASSERT_EQUALS(iterator, mIntObjectList.Begin());

		// tests for finding data at the last node
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(7)));
		TS_ASSERT_EQUALS(*iterator, IntObject(7));

		// tests for not finding the data
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(9)));
		TS_ASSERT_EQUALS(iterator, mIntObjectList.End());

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
	}

	void TestIntObjectSListRemove(void)
	{
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(6)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(7)));
		SList<IntObject>::Iterator iterator;

		// tests for removal of data from linked list
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Remove(IntObject(6)));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Find(IntObject(6)));
		TS_ASSERT_EQUALS(iterator, mIntObjectList.End());
		TS_ASSERT_EQUALS(mIntObjectList.Size(), 6);

		// tests for removing the first equal data in the linked list
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Remove(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_EQUALS(*iterator, IntObject(5));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, IntObject(1));

		// tests for proper ordering
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Remove(IntObject(2)));
		TS_ASSERT_THROWS_NOTHING(++iterator);
		TS_ASSERT_EQUALS(*iterator, IntObject(2));

		// tests for removal at end of list with the iterator being at the 2nd-to-last node
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Remove(IntObject(7)));
		TS_ASSERT_EQUALS(*iterator, mIntObjectList.Back());

		// tests for removal of data that is not in linked list
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Remove(IntObject(9)));

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT(mIntObjectList.IsEmpty());
	}

	void TestIntObjectIteratorComparisonOperators(void)
	{
		SList<IntObject>::Iterator iterator;
		SList<IntObject>::Iterator otherIterator;
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(5)));
		TS_ASSERT_THROWS_NOTHING(mIntObjectList.PushBack(IntObject(1)));

		// tests for equality between two uninitialized iterators
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to the same node in the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntObjectList.Begin());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for equality between iterators pointing to no node, but are part of the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.End());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntObjectList.End());
		TS_ASSERT_EQUALS(iterator, otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical data within the same list
		TS_ASSERT_THROWS_NOTHING(iterator = mIntObjectList.Begin());
		TS_ASSERT_THROWS_NOTHING(otherIterator = mIntObjectList.Begin());
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT_THROWS_NOTHING(++otherIterator);
		TS_ASSERT(iterator != otherIterator);

		// tests for non-equality between two iterators pointing to nodes with identical, but are in two different lists
		SList<IntObject> otherIntObjectList = mIntObjectList;
		TS_ASSERT_THROWS_NOTHING(otherIterator = otherIntObjectList.Begin());
		TS_ASSERT(iterator != otherIterator);

		TS_ASSERT_THROWS_NOTHING(mIntObjectList.Clear());
		TS_ASSERT(mIntObjectList.IsEmpty());
	}

private:
	class IntObject
	{
	public:
		int mInt;

		explicit IntObject(int i = 0) : mInt(i) {}
		bool operator==(const IntObject& iObject) const { return mInt == iObject.mInt; }
	};

	SList<uint32_t> mIntList;
	SList<uint32_t*> mIntPointerList;
	SList<IntObject> mIntObjectList;
};