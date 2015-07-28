#include <cxxtest/TestSuite.h>
#include "Stack.h"

using namespace Library;

class StackTestSuite : public CxxTest::TestSuite
{
public:
	void TestIntStackInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackCopyConstructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntStack.Push(i);

		Stack<uint32_t> otherIntStack = mIntStack;

		// tests for value comparisons
		std::uint32_t initialSize = mIntStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntStack.Top(), otherIntStack.Top());
			mIntStack.Pop();
			otherIntStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntStack != &otherIntStack);

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackAssignmentOperator(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntStack.Push(i);

		Stack<uint32_t> otherIntStack;
		otherIntStack = mIntStack;

		// tests for self assignment
		TS_ASSERT_THROWS_NOTHING(mIntStack = mIntStack);

		// tests for value comparisons
		std::uint32_t initialSize = mIntStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntStack.Top(), otherIntStack.Top());
			mIntStack.Pop();
			otherIntStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntStack != &otherIntStack);

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackDestructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntStack.Push(i);

		// tests for stack being empty after destructor call
		mIntStack.~Stack();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackPush(void)
	{
		mIntStack.Push(1);
		mIntStack.Push(2);
		mIntStack.Push(3);

		// Tests for proper pushes and size
		TS_ASSERT_EQUALS(mIntStack.Top(), 3);
		TS_ASSERT_EQUALS(mIntStack.Size(), 3);

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackPop(void)
	{
		mIntStack.Push(1);
		mIntStack.Push(2);
		mIntStack.Push(3);
		mIntStack.Push(4);

		mIntStack.Pop();
		mIntStack.Pop();

		// Tests for proper pops and size
		TS_ASSERT_EQUALS(mIntStack.Top(), 2);
		TS_ASSERT_EQUALS(mIntStack.Size(), 2);

		mIntStack.Pop();

		TS_ASSERT_EQUALS(mIntStack.Top(), 1);
		TS_ASSERT_EQUALS(mIntStack.Size(), 1);

		mIntStack.Pop();
		TS_ASSERT(mIntStack.IsEmpty());

		TS_ASSERT_THROWS_NOTHING(mIntStack.Pop());
	}

	void TestIntStackTop(void)
	{
		try
		{
			std::uint32_t i;
			i = mIntStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntStack.Push(1);
		mIntStack.Push(2);
		TS_ASSERT_EQUALS(mIntStack.Top(), 2);

		// Tests for getting the new back value after a pop
		mIntStack.Pop();
		TS_ASSERT_EQUALS(mIntStack.Top(), 1);
		mIntStack.Pop();

		try
		{
			std::uint32_t i;
			i = mIntStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackConstTop(void)
	{
		try
		{
			const std::uint32_t i = mIntStack.Top();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntStack.Push(1);
		mIntStack.Push(2);
		TS_ASSERT_EQUALS(mIntStack.Top(), 2);

		// Tests for getting the new back value after a pop
		mIntStack.Pop();
		TS_ASSERT_EQUALS(mIntStack.Top(), 1);
		mIntStack.Pop();

		try
		{
			const std::uint32_t i = mIntStack.Top();
			std::uint32_t j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntStackSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntStack.Push(i);
			TS_ASSERT_EQUALS(mIntStack.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			TS_ASSERT_EQUALS(mIntStack.Size(), 1000 - i);
			mIntStack.Pop();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntStack.Size(), 0);

		mIntStack.Clear();
		TS_ASSERT(mIntStack.IsEmpty());
	}

	void TestIntPointerStackInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackCopyConstructor(void)
	{
		mIntPointerStack.Push((std::uint32_t*) 0x11111111);
		mIntPointerStack.Push((std::uint32_t*) 0x22222222);
		mIntPointerStack.Push((std::uint32_t*) 0x33333333);

		Stack<uint32_t*> otherIntPointerStack = mIntPointerStack;

		// tests for value comparisons
		std::uint32_t initialSize = mIntPointerStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntPointerStack.Top(), otherIntPointerStack.Top());
			mIntPointerStack.Pop();
			otherIntPointerStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntPointerStack != &otherIntPointerStack);

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackAssignmentOperator(void)
	{
		mIntPointerStack.Push((std::uint32_t*) 0x11111111);
		mIntPointerStack.Push((std::uint32_t*) 0x22222222);
		mIntPointerStack.Push((std::uint32_t*) 0x33333333);

		Stack<uint32_t*> otherIntPointerStack;
		otherIntPointerStack = mIntPointerStack;

		// tests for self assignment
		TS_ASSERT_THROWS_NOTHING(mIntPointerStack = mIntPointerStack);

		// tests for value comparisons
		std::uint32_t initialSize = mIntPointerStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntPointerStack.Top(), otherIntPointerStack.Top());
			mIntPointerStack.Pop();
			otherIntPointerStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntPointerStack != &otherIntPointerStack);

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackDestructor(void)
	{
		mIntPointerStack.Push((std::uint32_t*) 0x11111111);
		mIntPointerStack.Push((std::uint32_t*) 0x22222222);
		mIntPointerStack.Push((std::uint32_t*) 0x33333333);

		// tests for stack being empty after destructor call
		mIntPointerStack.~Stack();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackPush(void)
	{
		mIntPointerStack.Push((std::uint32_t*) 0x11111111);
		mIntPointerStack.Push((std::uint32_t*) 0x22222222);
		mIntPointerStack.Push((std::uint32_t*) 0x33333333);

		// Tests for proper pushes and size
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*) 0x33333333);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 3);

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackPop(void)
	{
		mIntPointerStack.Push((std::uint32_t*) 0x11111111);
		mIntPointerStack.Push((std::uint32_t*) 0x22222222);
		mIntPointerStack.Push((std::uint32_t*) 0x33333333);
		mIntPointerStack.Push((std::uint32_t*) 0x44444444);

		mIntPointerStack.Pop();
		mIntPointerStack.Pop();

		// Tests for proper pops and size
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 2);

		mIntPointerStack.Pop();

		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x11111111);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 1);

		mIntPointerStack.Pop();
		TS_ASSERT(mIntPointerStack.IsEmpty());

		TS_ASSERT_THROWS_NOTHING(mIntPointerStack.Pop());
	}

	void TestIntPointerStackTop(void)
	{
		try
		{
			std::uint32_t* i;
			i = mIntPointerStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntPointerStack.Push((std::uint32_t*)0x11111111);
		mIntPointerStack.Push((std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x22222222);

		// Tests for getting the new back value after a pop
		mIntPointerStack.Pop();
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x11111111);
		mIntPointerStack.Pop();

		try
		{
			std::uint32_t* i;
			i = mIntPointerStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackConstTop(void)
	{
		try
		{
			const std::uint32_t* i = mIntPointerStack.Top();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntPointerStack.Push((std::uint32_t*)0x11111111);
		mIntPointerStack.Push((std::uint32_t*)0x22222222);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x22222222);

		// Tests for getting the new back value after a pop
		mIntPointerStack.Pop();
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), (std::uint32_t*)0x11111111);
		mIntPointerStack.Pop();

		try
		{
			const std::uint32_t* i = mIntPointerStack.Top();
			const std::uint32_t* j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntPointerStackSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntPointerStack.Push((std::uint32_t*) (4 * i));
			TS_ASSERT_EQUALS(mIntPointerStack.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = mIntPointerStack.Size(); i > 0; i--)
		{
			TS_ASSERT_EQUALS(mIntPointerStack.Size(), i);
			mIntPointerStack.Pop();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 0);

		mIntPointerStack.Clear();
		TS_ASSERT(mIntPointerStack.IsEmpty());
	}

	void TestIntObjectStackInstantiation(void)
	{
		// Vector should be empty upon initialization; this is also done after every test to test for Clear()
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackCopyConstructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectStack.Push(IntObject(i));

		Stack<IntObject> otherIntObjectStack = mIntObjectStack;

		// tests for value comparisons
		std::uint32_t initialSize = mIntObjectStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntObjectStack.Top(), otherIntObjectStack.Top());
			mIntObjectStack.Pop();
			otherIntObjectStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntObjectStack != &otherIntObjectStack);

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackAssignmentOperator(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectStack.Push(IntObject(i));

		Stack<IntObject> otherIntObjectStack;
		otherIntObjectStack = mIntObjectStack;

		// tests for self assignment
		TS_ASSERT_THROWS_NOTHING(mIntObjectStack = mIntObjectStack);

		// tests for value comparisons
		std::uint32_t initialSize = mIntObjectStack.Size();
		for (std::uint32_t i = 0; i < initialSize; i++)
		{
			TS_ASSERT_EQUALS(mIntObjectStack.Top(), otherIntObjectStack.Top());
			mIntObjectStack.Pop();
			otherIntObjectStack.Pop();
		}

		// tests for being a deep copy
		TS_ASSERT(&mIntObjectStack != &otherIntObjectStack);

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackDestructor(void)
	{
		for (std::uint32_t i = 0; i < 10; i++)
			mIntObjectStack.Push(IntObject(i));

		// tests for stack being empty after destructor call
		mIntObjectStack.~Stack();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackPush(void)
	{
		mIntObjectStack.Push(IntObject(1));
		mIntObjectStack.Push(IntObject(2));
		mIntObjectStack.Push(IntObject(3));

		// Tests for proper pushes and size
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(3));
		TS_ASSERT_EQUALS(mIntObjectStack.Size(), 3);

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackPop(void)
	{
		mIntObjectStack.Push(IntObject(1));
		mIntObjectStack.Push(IntObject(2));
		mIntObjectStack.Push(IntObject(3));
		mIntObjectStack.Push(IntObject(4));

		mIntObjectStack.Pop();
		mIntObjectStack.Pop();

		// Tests for proper pops and size
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectStack.Size(), 2);

		mIntObjectStack.Pop();

		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(1));
		TS_ASSERT_EQUALS(mIntObjectStack.Size(), 1);

		mIntObjectStack.Pop();
		TS_ASSERT(mIntObjectStack.IsEmpty());

		TS_ASSERT_THROWS_NOTHING(mIntObjectStack.Pop());
	}

	void TestIntObjectStackTop(void)
	{
		try
		{
			IntObject i;
			i = mIntObjectStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntObjectStack.Push(IntObject(1));
		mIntObjectStack.Push(IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(2));

		// Tests for getting the new back value after a pop
		mIntObjectStack.Pop();
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(1));
		mIntObjectStack.Pop();

		try
		{
			IntObject i;
			i = mIntObjectStack.Top();
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackConstTop(void)
	{
		try
		{
			const IntObject i = mIntObjectStack.Top();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if capacity is at 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		// Tests for getting the back value
		mIntObjectStack.Push(IntObject(1));
		mIntObjectStack.Push(IntObject(2));
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(2));

		// Tests for getting the new back value after a pop
		mIntObjectStack.Pop();
		TS_ASSERT_EQUALS(mIntObjectStack.Top(), IntObject(1));
		mIntObjectStack.Pop();

		try
		{
			const IntObject i = mIntObjectStack.Top();
			IntObject j;
			j = i;
		}
		catch (std::exception& error)
		{
			// Tests for proper exception handling if size is at 0, but capacity is greater than 0
			TS_ASSERT_EQUALS(error.what(), "The stack is empty!");
		}

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
	}

	void TestIntObjectStackSize(void)
	{
		// Tests for size increasing after each push
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			mIntObjectStack.Push(IntObject(i));
			TS_ASSERT_EQUALS(mIntObjectStack.Size(), i + 1);
		}

		// Tests for size decreasing after each pop
		for (std::uint32_t i = 0; i < 1000; i++)
		{
			TS_ASSERT_EQUALS(mIntObjectStack.Size(), 1000 - i);
			mIntObjectStack.Pop();
		}

		// Tests for size to be at 0 after an equal number of pushes and pops
		TS_ASSERT_EQUALS(mIntObjectStack.Size(), 0);

		mIntObjectStack.Clear();
		TS_ASSERT(mIntObjectStack.IsEmpty());
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

	Stack<uint32_t> mIntStack;
	Stack<uint32_t*> mIntPointerStack;
	Stack<IntObject> mIntObjectStack;
};