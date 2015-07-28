#include <cxxtest/TestSuite.h>
#include "Datum.h"

using namespace Library;

class DatumTestSuite : public CxxTest::TestSuite
{
public:
	void TestDatumInstantiation(void)
	{
		Datum d1;

		// each datum should be initialized to unknown type
		TS_ASSERT_EQUALS(d1.GetType(), Datum::Unknown);

		// an empty datum should still be cleared without causing issues
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// the size of an empty datum should be 0
		TS_ASSERT_EQUALS(d1.Size(), 0);
	}

	void TestDatumConstructor(void)
	{
		Datum integerD(Datum::Integer, 10);
		Datum floatD(Datum::Float, 10);
		Datum vectorD(Datum::Vector, 10);
		Datum matrixD(Datum::Matrix, 10);
		Datum stringD(Datum::String, 10);
		Datum pointerD(Datum::Pointer, 10);

		// tests for correct type assignment
		TS_ASSERT_EQUALS(integerD.GetType(), Datum::Integer);
		TS_ASSERT_EQUALS(floatD.GetType(), Datum::Float);
		TS_ASSERT_EQUALS(vectorD.GetType(), Datum::Vector);
		TS_ASSERT_EQUALS(matrixD.GetType(), Datum::Matrix);
		TS_ASSERT_EQUALS(stringD.GetType(), Datum::String);
		TS_ASSERT_EQUALS(pointerD.GetType(), Datum::Pointer);

		// tests for correct size assignment
		TS_ASSERT_EQUALS(integerD.Size(), 10);
		TS_ASSERT_EQUALS(floatD.Size(), 10);
		TS_ASSERT_EQUALS(vectorD.Size(), 10);
		TS_ASSERT_EQUALS(matrixD.Size(), 10);
		TS_ASSERT_EQUALS(stringD.Size(), 10);
		TS_ASSERT_EQUALS(pointerD.Size(), 10);

		// if the datums were properly allocated, Clear() should function normally
		TS_ASSERT_THROWS_NOTHING(integerD.Clear());
		TS_ASSERT_THROWS_NOTHING(floatD.Clear());
		TS_ASSERT_THROWS_NOTHING(vectorD.Clear());
		TS_ASSERT_THROWS_NOTHING(matrixD.Clear());
		TS_ASSERT_THROWS_NOTHING(stringD.Clear());
		TS_ASSERT_THROWS_NOTHING(pointerD.Clear());

		TS_ASSERT_EQUALS(integerD.Size(), 0);
		TS_ASSERT_EQUALS(floatD.Size(), 0);
		TS_ASSERT_EQUALS(vectorD.Size(), 0);
		TS_ASSERT_EQUALS(matrixD.Size(), 0);
		TS_ASSERT_EQUALS(stringD.Size(), 0);
		TS_ASSERT_EQUALS(pointerD.Size(), 0);
	}

	void TestDatumSetTypeAndGetType(void)
	{
		Datum integerD;
		Datum floatD;
		Datum vectorD;
		Datum matrixD;
		Datum tableD;
		Datum stringD;
		Datum pointerD;

		// set the type
		TS_ASSERT_THROWS_NOTHING(integerD.SetType(Datum::Integer));
		TS_ASSERT_THROWS_NOTHING(floatD.SetType(Datum::Float));
		TS_ASSERT_THROWS_NOTHING(vectorD.SetType(Datum::Vector));
		TS_ASSERT_THROWS_NOTHING(matrixD.SetType(Datum::Matrix));
		TS_ASSERT_THROWS_NOTHING(tableD.SetType(Datum::Table));
		TS_ASSERT_THROWS_NOTHING(stringD.SetType(Datum::String));
		TS_ASSERT_THROWS_NOTHING(pointerD.SetType(Datum::Pointer));

		// tests for correct type assignment
		TS_ASSERT_EQUALS(integerD.GetType(), Datum::Integer);
		TS_ASSERT_EQUALS(floatD.GetType(), Datum::Float);
		TS_ASSERT_EQUALS(vectorD.GetType(), Datum::Vector);
		TS_ASSERT_EQUALS(matrixD.GetType(), Datum::Matrix);
		TS_ASSERT_EQUALS(tableD.GetType(), Datum::Table);
		TS_ASSERT_EQUALS(stringD.GetType(), Datum::String);
		TS_ASSERT_EQUALS(pointerD.GetType(), Datum::Pointer);

		// tests for no exceptions when assigning same type
		TS_ASSERT_THROWS_NOTHING(integerD.SetType(Datum::Integer));
		TS_ASSERT_THROWS_NOTHING(floatD.SetType(Datum::Float));
		TS_ASSERT_THROWS_NOTHING(vectorD.SetType(Datum::Vector));
		TS_ASSERT_THROWS_NOTHING(matrixD.SetType(Datum::Matrix));
		TS_ASSERT_THROWS_NOTHING(tableD.SetType(Datum::Table));
		TS_ASSERT_THROWS_NOTHING(stringD.SetType(Datum::String));
		TS_ASSERT_THROWS_NOTHING(pointerD.SetType(Datum::Pointer));

		// tests for exceptions when assigning a type when datum as already been assigned
		TS_ASSERT_THROWS_ANYTHING(integerD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(floatD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(vectorD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(matrixD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(tableD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(stringD.SetType(Datum::Unknown));
		TS_ASSERT_THROWS_ANYTHING(pointerD.SetType(Datum::Unknown));
	}

	void TestIntDatumCopyConstructor(void)
	{
		Datum d1;
		d1 = 1;

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetInteger() != &d2.GetInteger());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(5, 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetInteger() != &d3.GetInteger());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestIntDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		d1 = 1;
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetInteger() != &d2.GetInteger());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(5, 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetInteger() != &d3.GetInteger());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestIntDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		int A[] = { 1, 2, 3 };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetInteger() == &d2.GetInteger());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestIntDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		int A[] = { 1, 2, 3 };
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set(3, 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set(7, 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set(9, 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetInteger() != &d2.GetInteger());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetInteger(), 3);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		d3 = 5;
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestIntDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		int A[] = { 1, 2, 3 };
		int B[] = { 4, 5, 6, 7 };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetInteger() == &d2.GetInteger());
		TS_ASSERT(&d2.GetInteger() != B);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetInteger(), 1);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestIntDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::Integer);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetInteger(), int());
		TS_ASSERT_EQUALS(d1.GetInteger(4), int());

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetInteger(1), int());
		TS_ASSERT_THROWS_ANYTHING(d1.GetInteger(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetInteger(3), int());
		TS_ASSERT_THROWS_ANYTHING(d1.GetInteger(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetInteger(14), int());
		TS_ASSERT_THROWS_ANYTHING(d1.GetInteger(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetInteger());
	}

	void TestIntDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::Integer);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		int A[] = {1, 2, 3, 4, 5};
		d1.SetStorage(A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestIntDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		int A[] = { 1, 2, 3 };
		int B[] = { 4, 5, 6, 7 };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_EQUALS(&d1.GetInteger(), A);
		TS_ASSERT_EQUALS(&d2.GetInteger(), B);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetInteger(), 4));
		TS_ASSERT_EQUALS(&d1.GetInteger(), B);

		// testing for shallow copy
		TS_ASSERT_THROWS_NOTHING(d1.Set(10, 2));
		TS_ASSERT_EQUALS(B[2], 10);
		TS_ASSERT_EQUALS(d2.GetInteger(2), 10);

		// testing for external datum not getting resized
		TS_ASSERT_THROWS_ANYTHING(d1.Set(50, 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestIntDatumComparisonOperator(void)
	{
		Datum d1(Datum::Integer, 3);
		Datum d2(Datum::Integer, 4);
		Datum d3(Datum::Integer, 3);
		Datum d4(Datum::Integer, 1);
		Datum d5;

		int A[] = { 1, 2, 3 };
		int B[] = { 4, 5, 6, 7 };
		int C[] = { 1, 2, 10 };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage(A, 3));
		d4 = 100;

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, 100);

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage(C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestIntDatumGetAndSet(void)
	{
		Datum d1;

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set(1, 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetInteger(), 1);

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1.0f, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set(3, 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetInteger(0), 1);
		TS_ASSERT_EQUALS(d1.GetInteger(1), int());
		TS_ASSERT_EQUALS(d1.GetInteger(2), 3);
	}

	void TestIntDatumSetFromString(void)
	{
		Datum d1(Datum::Integer, 0);
		std::string s1("12");
		std::string s2("hi 5");
		std::string s3("5 alive");
		std::string s4("123abc");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetInteger(), 12);

		// test for invalid input
		TS_ASSERT_THROWS_ANYTHING(d1.SetFromString(s2, 1));

		// test for valid input (with a space) and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetInteger(5), 5);

		// test for valid input (no space)
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s4, 3));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetInteger(3), 123);
	}

	void TestIntDatumToString(void)
	{
		Datum d1(Datum::Integer, 0);
		int A[] = {12, 5, 123};
		std::string s1("12");
		std::string s2("5");
		std::string s3("123");
		std::string s4("1234");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

	void TestFloatDatumCopyConstructor(void)
	{
		Datum d1;
		d1 = 1.0f;

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetFloat() != &d2.GetFloat());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(5.0f, 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetFloat() != &d3.GetFloat());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestFloatDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		d1 = 1.0f;
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetFloat() != &d2.GetFloat());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(5.0f, 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetFloat() != &d3.GetFloat());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestFloatDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		float A[] = { 1.0f, 2.0f, 3.0f };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetFloat() == &d2.GetFloat());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestFloatDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		float A[] = { 1.0f, 2.0f, 3.0f };
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set(3.0f, 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set(7.0f, 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set(9.0f, 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetFloat() != &d2.GetFloat());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetFloat(), 3.0f);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		d3 = 5.0f;
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestFloatDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		float A[] = { 1.0f, 2.0f, 3.0f };
		float B[] = { 4.0f, 5.0f, 6.0f, 7.0f };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetFloat() == &d2.GetFloat());
		TS_ASSERT(&d2.GetFloat() != B);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetFloat(), 1.0f);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestFloatDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::Float);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetFloat(), float());
		TS_ASSERT_EQUALS(d1.GetFloat(4), float());

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetFloat(1), float());
		TS_ASSERT_THROWS_ANYTHING(d1.GetFloat(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetFloat(3), float());
		TS_ASSERT_THROWS_ANYTHING(d1.GetFloat(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetFloat(14), float());
		TS_ASSERT_THROWS_ANYTHING(d1.GetFloat(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetFloat());
	}

	void TestFloatDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::Float);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		float A[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
		d1.SetStorage(A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestFloatDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		float A[] = { 1.0f, 2.0f, 3.0f };
		float B[] = { 4.0f, 5.0f, 6.0f, 7.0f };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_EQUALS(&d1.GetFloat(), A);
		TS_ASSERT_EQUALS(&d2.GetFloat(), B);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetFloat(), 4));
		TS_ASSERT_EQUALS(&d1.GetFloat(), B);

		// testing for shallow copy
		TS_ASSERT_THROWS_NOTHING(d1.Set(10.0f, 2));
		TS_ASSERT_EQUALS(B[2], 10.0f);
		TS_ASSERT_EQUALS(d2.GetFloat(2), 10.0f);

		// testing for external datum not getting resized
		TS_ASSERT_THROWS_ANYTHING(d1.Set(50.0f, 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestFloatDatumComparisonOperator(void)
	{
		Datum d1(Datum::Float, 3);
		Datum d2(Datum::Float, 4);
		Datum d3(Datum::Float, 3);
		Datum d4(Datum::Float, 1);
		Datum d5;

		float A[] = { 1.0f, 2.0f, 3.0f };
		float B[] = { 4.0f, 5.0f, 6.0f, 7.0f };
		float C[] = { 1.0f, 2.0f, 10.0f };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage(A, 3));
		d4 = 100.0f;

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, 100.0f);

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage(C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestFloatDatumGetAndSet(void)
	{
		Datum d1;

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set(1.0f, 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetFloat(), 1.0f);

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set(3.0f, 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetFloat(0), 1.0f);
		TS_ASSERT_EQUALS(d1.GetFloat(1), float());
		TS_ASSERT_EQUALS(d1.GetFloat(2), 3.0f);
	}

	void TestFloatDatumSetFromString(void)
	{
		Datum d1(Datum::Float, 0);
		std::string s1("12.0");
		std::string s2("hi 5.0");
		std::string s3("5.0 alive");
		std::string s4("123.0abc");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetFloat(), 12.0f);

		// test for invalid input
		TS_ASSERT_THROWS_ANYTHING(d1.SetFromString(s2, 1));

		// test for valid input (with a space) and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetFloat(5), 5.0f);

		// test for valid input (no space)
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s4, 3));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetFloat(3), 123.0f);
	}

	void TestFloatDatumToString(void)
	{
		Datum d1(Datum::Float, 0);
		float A[] = { 12.0f, 5.0f, 123.0f };
		std::string s1("12.0");
		std::string s2("5.0");
		std::string s3("123.0");
		std::string s4("1234.0");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

	void TestVectorDatumCopyConstructor(void)
	{
		Datum d1;
		d1 = glm::vec4(1.0f);

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetVector() != &d2.GetVector());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(5.0f), 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetVector() != &d3.GetVector());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestVectorDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		d1 = glm::vec4(1.0f);
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetVector() != &d2.GetVector());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(5.0f), 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetVector() != &d3.GetVector());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestVectorDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetVector() == &d2.GetVector());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestVectorDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(3.0f), 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(7.0f), 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(9.0f), 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetVector() != &d2.GetVector());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetVector(), glm::vec4(3.0f));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		d3 = glm::vec4(5.0f);
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestVectorDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		glm::vec4 B[] = { glm::vec4(4.0f), glm::vec4(5.0f), glm::vec4(6.0f), glm::vec4(7.0f) };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetVector() == &d2.GetVector());
		TS_ASSERT(&d2.GetVector() != B);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetVector(), glm::vec4(1.0f));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestVectorDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::Vector);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetVector(), glm::vec4());
		TS_ASSERT_EQUALS(d1.GetVector(4), glm::vec4());

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetVector(1), glm::vec4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetVector(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetVector(3), glm::vec4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetVector(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetVector(14), glm::vec4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetVector(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetVector());
	}

	void TestVectorDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::Vector);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f), glm::vec4(4.0f), glm::vec4(5.0f) };
		d1.SetStorage(A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestVectorDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		glm::vec4 B[] = { glm::vec4(4.0f), glm::vec4(5.0f), glm::vec4(6.0f), glm::vec4(7.0f) };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_EQUALS(&d1.GetVector(), A);
		TS_ASSERT_EQUALS(&d2.GetVector(), B);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetVector(), 4));
		TS_ASSERT_EQUALS(&d1.GetVector(), B);

		// testing for shallow copy
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(10.0f), 2));
		TS_ASSERT_EQUALS(B[2], glm::vec4(10.0f));
		TS_ASSERT_EQUALS(d2.GetVector(2), glm::vec4(10.0f));

		// testing for external datum not getting resized
		TS_ASSERT_THROWS_ANYTHING(d1.Set(glm::vec4(50.0f), 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestVectorDatumComparisonOperator(void)
	{
		Datum d1(Datum::Vector, 3);
		Datum d2(Datum::Vector, 4);
		Datum d3(Datum::Vector, 3);
		Datum d4(Datum::Vector, 1);
		Datum d5;

		glm::vec4 A[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		glm::vec4 B[] = { glm::vec4(4.0f), glm::vec4(5.0f), glm::vec4(6.0f), glm::vec4(7.0f) };
		glm::vec4 C[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(10.0f) };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage(A, 3));
		d4 = glm::vec4(100.0f);

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, glm::vec4(100.0f));

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage(C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestVectorDatumGetAndSet(void)
	{
		Datum d1;

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(1.0f), 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetVector(), glm::vec4(1.0f));

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1.0f, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::vec4(3.0f), 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetVector(0), glm::vec4(1.0f));
		TS_ASSERT_EQUALS(d1.GetVector(1), glm::vec4());
		TS_ASSERT_EQUALS(d1.GetVector(2), glm::vec4(3.0f));
	}

	void TestVectorDatumSetFromString(void)
	{
		Datum d1(Datum::Vector, 0);
		std::string s1("12.0 13.0 14.0 15.0");
		std::string s2("hi 5.0 6.0 7.0 8.0");
		std::string s3("5.0 6.0 7.0 8.0 alive");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetVector(), glm::vec4(12.0f, 13.0f, 14.0f, 15.0f));

		// test for invalid input
		TS_ASSERT_THROWS_ANYTHING(d1.SetFromString(s2, 1));

		// test for valid input and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetVector(5), glm::vec4(5.0f, 6.0f, 7.0f, 8.0f));
	}

	void TestVectorDatumToString(void)
	{
		Datum d1(Datum::Vector, 0);
		glm::vec4 A[] = { glm::vec4(12.0f), glm::vec4(5.0f), glm::vec4(123.0f) };
		std::string s1("<12.0 12.0 12.0 12.0>");
		std::string s2("<5.0 5.0 5.0 5.0>");
		std::string s3("<123.0 123.0 123.0 123.0>");
		std::string s4("<1234.0 1234.0 1234.0 1234.0>");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

	void TestMatrixDatumCopyConstructor(void)
	{
		Datum d1;
		d1 = glm::mat4(1.0f);

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetMatrix() != &d2.GetMatrix());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(5.0f), 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetMatrix() != &d3.GetMatrix());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestMatrixDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		d1 = glm::mat4(1.0f);
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetMatrix() != &d2.GetMatrix());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(5.0f), 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetMatrix() != &d3.GetMatrix());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestMatrixDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetMatrix() == &d2.GetMatrix());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestMatrixDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(3.0f), 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(7.0f), 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(9.0f), 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetMatrix() != &d2.GetMatrix());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetMatrix(), glm::mat4(3.0f));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		d3 = glm::mat4(5.0f);
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestMatrixDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		glm::mat4 B[] = { glm::mat4(4.0f), glm::mat4(5.0f), glm::mat4(6.0f), glm::mat4(7.0f) };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetMatrix() == &d2.GetMatrix());
		TS_ASSERT(&d2.GetMatrix() != B);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetMatrix(), glm::mat4(1.0f));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestMatrixDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::Matrix);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetMatrix(), glm::mat4());
		TS_ASSERT_EQUALS(d1.GetMatrix(4), glm::mat4());

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetMatrix(1), glm::mat4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetMatrix(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetMatrix(3), glm::mat4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetMatrix(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetMatrix(14), glm::mat4());
		TS_ASSERT_THROWS_ANYTHING(d1.GetMatrix(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetMatrix());
	}

	void TestMatrixDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::Matrix);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f), glm::mat4(4.0f), glm::mat4(5.0f) };
		d1.SetStorage(A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestMatrixDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		glm::mat4 B[] = { glm::mat4(4.0f), glm::mat4(5.0f), glm::mat4(6.0f), glm::mat4(7.0f) };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_EQUALS(&d1.GetMatrix(), A);
		TS_ASSERT_EQUALS(&d2.GetMatrix(), B);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetMatrix(), 4));
		TS_ASSERT_EQUALS(&d1.GetMatrix(), B);

		// testing for shallow copy
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(10.0f), 2));
		TS_ASSERT_EQUALS(B[2], glm::mat4(10.0f));
		TS_ASSERT_EQUALS(d2.GetMatrix(2), glm::mat4(10.0f));

		// testing for external datum not getting resized
		TS_ASSERT_THROWS_ANYTHING(d1.Set(glm::mat4(50.0f), 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestMatrixDatumComparisonOperator(void)
	{
		Datum d1(Datum::Matrix, 3);
		Datum d2(Datum::Matrix, 4);
		Datum d3(Datum::Matrix, 3);
		Datum d4(Datum::Matrix, 1);
		Datum d5;

		glm::mat4 A[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		glm::mat4 B[] = { glm::mat4(4.0f), glm::mat4(5.0f), glm::mat4(6.0f), glm::mat4(7.0f) };
		glm::mat4 C[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(10.0f) };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage(A, 3));
		d4 = glm::mat4(100.0f);

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, glm::mat4(100.0f));

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage(C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestMatrixDatumGetAndSet(void)
	{
		Datum d1;

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(1.0f), 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetMatrix(), glm::mat4(1.0f));

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1.0f, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set(glm::mat4(3.0f), 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetMatrix(0), glm::mat4(1.0f));
		TS_ASSERT_EQUALS(d1.GetMatrix(1), glm::mat4());
		TS_ASSERT_EQUALS(d1.GetMatrix(2), glm::mat4(3.0f));
	}

	void TestMatrixDatumSetFromString(void)
	{
		Datum d1(Datum::Matrix, 0);
		std::string s1("12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0");
		std::string s2("hi 5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0");
		std::string s3("5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0 5.0 6.0 7.0 8.0 alive");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetMatrix(), glm::mat4(12.0f, 13.0f, 14.0f, 15.0f, 12.0f, 13.0f, 14.0f, 15.0f, 12.0f, 13.0f, 14.0f, 15.0f, 12.0f, 13.0f, 14.0f, 15.0f));

		// test for invalid input
		TS_ASSERT_THROWS_ANYTHING(d1.SetFromString(s2, 1));

		// test for valid input and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetMatrix(5), glm::mat4(5.0f, 6.0f, 7.0f, 8.0f, 5.0f, 6.0f, 7.0f, 8.0f, 5.0f, 6.0f, 7.0f, 8.0f, 5.0f, 6.0f, 7.0f, 8.0f));
	}

	void TestMatrixDatumToString(void)
	{
		Datum d1(Datum::Matrix, 0);
		glm::mat4 A[] = { glm::mat4(12.0f), glm::mat4(5.0f), glm::mat4(123.0f) };
		std::string s1("[12.0 0.0 0.0 0.0\n 0.0 12.0 0.0 0.0\n 0.0 0.0 12.0 0.0\n 0.0 0.0 0.0 12.0]");
		std::string s2("[5.0 0.0 0.0 0.0\n 0.0 5.0 0.0 0.0\n 0.0 0.0 5.0 0.0\n 0.0 0.0 0.0 5.0]");
		std::string s3("[123.0 0.0 0.0 0.0\n 0.0 123.0 0.0 0.0\n 0.0 0.0 123.0 0.0\n 0.0 0.0 0.0 123.0]");
		std::string s4("[1234.0 0.0 0.0 0.0\n 0.0 1234.0 0.0 0.0\n 0.0 0.0 1234.0 0.0\n 0.0 0.0 0.0 1234.0]");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

	void TestStringDatumCopyConstructor(void)
	{
		Datum d1;
		d1 = std::string("one");

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetString() != &d2.GetString());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("five"), 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetString() != &d3.GetString());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestStringDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		d1 = std::string("one");
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetString() != &d2.GetString());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("five"), 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetString() != &d3.GetString());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestStringDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		std::string A[] = { std::string("one"), std::string("two"), std::string("three") };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetString() == &d2.GetString());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestStringDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		std::string A[] = { std::string("onett"), std::string("twoson"), std::string("threed") };
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("three"), 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("seven"), 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("nine"), 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetString() != &d2.GetString());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetString(), std::string("three"));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		d3 = std::string("fourside");
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestStringDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		std::string A[] = { std::string("one"), std::string("two"), std::string("three") };
		std::string B[] = { std::string("four"), std::string("five"), std::string("six"), std::string("seven") };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetString() == &d2.GetString());
		TS_ASSERT(&d2.GetString() != B);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetString(), std::string("one"));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestStringDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::String);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetString(), std::string());
		TS_ASSERT_EQUALS(d1.GetString(4), std::string());

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetString(1), std::string());
		TS_ASSERT_THROWS_ANYTHING(d1.GetString(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetString(3), std::string());
		TS_ASSERT_THROWS_ANYTHING(d1.GetString(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetString(14), std::string());
		TS_ASSERT_THROWS_ANYTHING(d1.GetString(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetString());
	}

	void TestStringDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::String);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		std::string A[] = { std::string("one"), std::string("two"), std::string("three"), std::string("four"), std::string("five") };
		d1.SetStorage(A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestStringDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		std::string A[] = { std::string("one"), std::string("two"), std::string("three") };
		std::string B[] = { std::string("four"), std::string("five"), std::string("six"), std::string("seven") };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_EQUALS(&d1.GetString(), A);
		TS_ASSERT_EQUALS(&d2.GetString(), B);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetString(), 4));
		TS_ASSERT_EQUALS(&d1.GetString(), B);

		// testing for shallow copy
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("ten"), 2));
		TS_ASSERT_EQUALS(B[2], std::string("ten"));
		TS_ASSERT_EQUALS(d2.GetString(2), std::string("ten"));

		// testing for external datum not getting resized
		TS_ASSERT_THROWS_ANYTHING(d1.Set(std::string("fifty"), 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestStringDatumComparisonOperator(void)
	{
		Datum d1(Datum::String, 3);
		Datum d2(Datum::String, 4);
		Datum d3(Datum::String, 3);
		Datum d4(Datum::String, 1);
		Datum d5;

		std::string A[] = { std::string("one"), std::string("two"), std::string("three") };
		std::string B[] = { std::string("four"), std::string("five"), std::string("six"), std::string("seven") };
		std::string C[] = { std::string("one"), std::string("two"), std::string("ten") };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage(B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage(A, 3));
		d4 = std::string("one hundred");

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, std::string("one hundred"));

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage(C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestStringDatumGetAndSet(void)
	{
		Datum d1;

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("one"), 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetString(), std::string("one"));

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1.0f, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set(std::string("three"), 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetString(0), std::string("one"));
		TS_ASSERT_EQUALS(d1.GetString(1), std::string());
		TS_ASSERT_EQUALS(d1.GetString(2), std::string("three"));
	}

	void TestStringDatumSetFromString(void)
	{
		Datum d1(Datum::String, 0);
		std::string s1("12");
		std::string s2("5 alive");
		std::string s3("123abc");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetString(), s1);

		// test for valid input (with a space) and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s2, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetString(5), s2);

		// test for valid input (no space)
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 3));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS(d1.GetString(3), s3);
	}

	void TestStringDatumToString(void)
	{
		Datum d1(Datum::String, 0);
		std::string A[] = { std::string("twelve"), std::string("five"), std::string("one hundred and twenty-three") };
		std::string s1("twelve");
		std::string s2("five");
		std::string s3("one hundred and twenty-three");
		std::string s4("one thousand, one hundred and twenty-three");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

	void TestPointerDatumCopyConstructor(void)
	{
		Datum d1;
		IntObject iObject1(1);
		d1 = (RTTI*) &iObject1;

		// tests for proper deep copy of a scalar
		Datum d2(d1);
		TS_ASSERT(&d1.GetPointer() != &d2.GetPointer());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		IntObject iObject2(5);
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject2, 3));
		Datum d3 = d1;
		TS_ASSERT(&d1.GetPointer() != &d3.GetPointer());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestPointerDatumAssignmentOperatorCase1(void)
	{
		Datum d1;
		IntObject iObject1(1);
		d1 = (RTTI*) &iObject1;
		Datum d2;
		d2 = d1;

		// tests for proper deep copy of a scalar
		TS_ASSERT(&d1.GetPointer() != &d2.GetPointer());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// tests for proper deep copy of a datum
		IntObject iObject2(5);
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject2, 3));
		Datum d3;
		d3 = d1;
		TS_ASSERT(&d1.GetPointer() != &d3.GetPointer());
		TS_ASSERT_EQUALS(d1, d3);
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.Size(), d3.Size());
	}

	void TestPointerDatumAssignmentOperatorCase2(void)
	{
		Datum d1;
		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage((RTTI**)A, 3));
		Datum d2;
		d2 = d1;

		// tests for shallow copy of external storage
		TS_ASSERT(&d1.GetPointer() == &d2.GetPointer());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
		TS_ASSERT_THROWS_ANYTHING(d2.SetSize(4));
	}

	void TestPointerDatumAssignmentOperatorCase3(void)
	{
		Datum d1;
		Datum d2;
		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject iObject4(3);
		IntObject iObject5(7);
		IntObject iObject6(9);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };

		TS_ASSERT_THROWS_NOTHING(d2.SetStorage((RTTI**)A, 3));
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject4, 0));
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject5, 1));
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject6, 2));
		d2 = d1;

		// tests for proper deep copy of datum of same size
		TS_ASSERT(&d1.GetPointer() != &d2.GetPointer());
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetPointer(), (RTTI*)&iObject4);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());

		// an exception is thrown when size is not the same between both sides
		Datum d3;
		IntObject iObject7(5);
		d3 = (RTTI*)&iObject4;
		TS_ASSERT_THROWS_ANYTHING(d2 = d3);
	}

	void TestPointerDatumAssignmentOperatorCase4(void)
	{
		Datum d1;
		Datum d2;
		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject iObject4(4);
		IntObject iObject5(5);
		IntObject iObject6(6);
		IntObject iObject7(7);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };
		IntObject* B[] = { &iObject4, &iObject5, &iObject6, &iObject7 };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage((RTTI**)A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage((RTTI**)B, 4));
		d2 = d1;

		// tests for proper shallow copy of datum
		TS_ASSERT(&d1.GetPointer() == &d2.GetPointer());
		TS_ASSERT(d2.GetPointer() != (RTTI*)B[0]);
		TS_ASSERT_EQUALS(d1, d2);
		TS_ASSERT_EQUALS(d2.GetPointer(), (RTTI*)A[0]);
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.Size(), d2.Size());
	}

	void TestPointerDatumSetSize(void)
	{
		Datum d1;

		// cannot set size of unknown type
		TS_ASSERT_THROWS_ANYTHING(d1.SetSize(5));

		// tests for proper size assignment and default initialization
		d1.SetType(Datum::Pointer);
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(5));
		TS_ASSERT_EQUALS(d1.Size(), 5);
		TS_ASSERT_EQUALS(d1.GetPointer(), nullptr);
		TS_ASSERT_EQUALS(d1.GetPointer(4), nullptr);

		// tests for decreasing size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(2));
		TS_ASSERT_EQUALS(d1.Size(), 2);
		TS_ASSERT_EQUALS(d1.GetPointer(1), nullptr);
		TS_ASSERT_THROWS_ANYTHING(d1.GetPointer(2));

		// tests for increasing size, but under capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(4));
		TS_ASSERT_EQUALS(d1.Size(), 4);
		TS_ASSERT_EQUALS(d1.GetPointer(3), nullptr);
		TS_ASSERT_THROWS_ANYTHING(d1.GetPointer(4));

		// tests for increasing capacity
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(15));
		TS_ASSERT_EQUALS(d1.Size(), 15);
		TS_ASSERT_EQUALS(d1.GetPointer(14), nullptr);
		TS_ASSERT_THROWS_ANYTHING(d1.GetPointer(15));

		// tests for zeroing out size
		TS_ASSERT_THROWS_NOTHING(d1.SetSize(0));
		TS_ASSERT_EQUALS(d1.Size(), 0);
		TS_ASSERT_THROWS_ANYTHING(d1.GetPointer());
	}

	void TestPointerDatumClear(void)
	{
		Datum d1;

		// an empty datum can be cleared with no problem
		TS_ASSERT_THROWS_NOTHING(d1.Clear());

		// setting up a datum then clearing it
		d1.SetType(Datum::Pointer);
		d1.SetSize(1000);
		TS_ASSERT_EQUALS(d1.Size(), 1000);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 0);

		// a datum with external storage should not be cleared within the Datum class
		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject iObject4(4);
		IntObject iObject5(5);
		IntObject* A[] = {&iObject1, &iObject2, &iObject3, &iObject4, &iObject5};
		d1.SetStorage((RTTI**)A, 5);
		TS_ASSERT_EQUALS(d1.Size(), 5);
		d1.Clear();
		TS_ASSERT_EQUALS(d1.Size(), 5);
	}

	void TestPointerDatumSetStorage(void)
	{
		Datum d1;
		Datum d2;
		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject iObject4(4);
		IntObject iObject5(5);
		IntObject iObject6(6);
		IntObject iObject7(7);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };
		IntObject* B[] = { &iObject4, &iObject5, &iObject6, &iObject7 };

		// testing for functionality of SetStorage()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage((RTTI**)A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage((RTTI**)B, 4));
		TS_ASSERT_EQUALS(d1.GetPointer(), (RTTI*)A[0]);
		TS_ASSERT_EQUALS(d2.GetPointer(), (RTTI*)B[0]);

		// testing SetStorage() on an already external datum
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage(&d2.GetPointer(), 4));
		TS_ASSERT_EQUALS(d1.GetPointer(), (RTTI*)B[0]);

		// testing for shallow copy
		IntObject iObject8(10);
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject8, 2));
		TS_ASSERT_EQUALS(B[2], &iObject8);
		TS_ASSERT_EQUALS(d2.GetPointer(2), (RTTI*)&iObject8);

		// testing for external datum not getting resized
		IntObject iObject9(50);
		TS_ASSERT_THROWS_ANYTHING(d1.Set((RTTI*)&iObject9, 10));
		TS_ASSERT_EQUALS(d1.Size(), 4);
	}

	void TestPointerDatumComparisonOperator(void)
	{
		Datum d1(Datum::Pointer, 3);
		Datum d2(Datum::Pointer, 4);
		Datum d3(Datum::Pointer, 3);
		Datum d4(Datum::Pointer, 1);
		Datum d5;

		IntObject iObject1(1);
		IntObject iObject2(2);
		IntObject iObject3(3);
		IntObject iObject4(4);
		IntObject iObject5(5);
		IntObject iObject6(6);
		IntObject iObject7(7);
		IntObject iObject8(10);
		IntObject iObject9(100);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };
		IntObject* B[] = { &iObject4, &iObject5, &iObject6, &iObject7 };
		IntObject* C[] = { &iObject1, &iObject2, &iObject8 };

		TS_ASSERT_THROWS_NOTHING(d1.SetStorage((RTTI**)A, 3));
		TS_ASSERT_THROWS_NOTHING(d2.SetStorage((RTTI**)B, 4));
		TS_ASSERT_THROWS_NOTHING(d3.SetStorage((RTTI**)A, 3));
		d4 = (RTTI*)&iObject9;

		// test for when datums are of different sizes
		TS_ASSERT(d1 != d2);

		// test for datum equality
		TS_ASSERT_EQUALS(d1, d3);

		// test for scalar equality
		TS_ASSERT_EQUALS(d4, (RTTI*)&iObject9);

		// test for exception when different types are compared
		TS_ASSERT_THROWS_ANYTHING(d1 == d5);

		// test for non-equality
		d3.SetStorage((RTTI**)C, 3);
		TS_ASSERT(d1 != d3);
	}

	void TestPointerDatumGetAndSet(void)
	{
		Datum d1;
		IntObject iObject1(1);
		IntObject iObject2(3);

		// tests for standard get and set functionality
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject1, 0));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS(d1.GetPointer(), (RTTI*)&iObject1);

		// tests for exception when different type parameter is passed in
		TS_ASSERT_THROWS_ANYTHING(d1.Set(1.0f, 0));

		// tests for proper reallocating of datum when set increases size and capacity
		TS_ASSERT_THROWS_NOTHING(d1.Set((RTTI*)&iObject2, 2));
		TS_ASSERT_EQUALS(d1.Size(), 3);
		TS_ASSERT_EQUALS(d1.GetPointer(0), (RTTI*)&iObject1);
		TS_ASSERT_EQUALS(d1.GetPointer(1), nullptr);
		TS_ASSERT_EQUALS(d1.GetPointer(2), (RTTI*)&iObject2);
	}

	void TestPointerDatumSetFromString(void)
	{
		Datum d1(Datum::Pointer, 0);
		std::string s1("12");
		std::string s2("hi 5");
		std::string s3("5 alive");
		std::string s4("123abc");

		// test for string input with just a number
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s1));
		TS_ASSERT_EQUALS(d1.Size(), 1);
		TS_ASSERT_EQUALS((std::uint32_t)d1.GetPointer(), 12);

		// test for invalid input
		TS_ASSERT_THROWS_ANYTHING(d1.SetFromString(s2, 1));

		// test for valid input (with a space) and resize
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s3, 5));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS((std::uint32_t)d1.GetPointer(5), 5);

		// test for valid input (no space)
		TS_ASSERT_THROWS_NOTHING(d1.SetFromString(s4, 3));
		TS_ASSERT_EQUALS(d1.Size(), 6);
		TS_ASSERT_EQUALS((std::uint32_t)d1.GetPointer(3), 123);
	}

	void TestPointerDatumToString(void)
	{
		Datum d1(Datum::Pointer, 0);
		IntObject iObject1(12);
		IntObject iObject2(5);
		IntObject iObject3(255);
		IntObject* A[] = { &iObject1, &iObject2, &iObject3 };

		char buffer[10];
		sprintf_s(buffer, sizeof(buffer), "0x%X", (std::uint32_t)&iObject1);
		std::string s1(buffer);

		sprintf_s(buffer, sizeof(buffer), "0x%X", (std::uint32_t)&iObject2);
		std::string s2(buffer);

		sprintf_s(buffer, sizeof(buffer), "0x%X", (std::uint32_t)&iObject3);
		std::string s3(buffer);

		std::string s4("0x100");

		// tests for proper functionality of ToString()
		TS_ASSERT_THROWS_NOTHING(d1.SetStorage((RTTI**)A, 3));
		TS_ASSERT_EQUALS(d1.ToString(), s1);
		TS_ASSERT_EQUALS(d1.ToString(1), s2);
		TS_ASSERT_EQUALS(d1.ToString(2), s3);
		TS_ASSERT(d1.ToString(2) != s4);

		// test for exception when out of bounds
		TS_ASSERT_THROWS_ANYTHING(d1.ToString(3));
	}

private:
	class IntObject
	{
	public:
		int* mAllocatedInt;

		explicit IntObject(int i = 0) : mAllocatedInt(nullptr)
		{
			mAllocatedInt = new int;
			*mAllocatedInt = i;
		}
		IntObject(const IntObject& rhs) : mAllocatedInt(nullptr)
		{
			mAllocatedInt = new int;
			*mAllocatedInt = *rhs.mAllocatedInt;
		}
		IntObject& operator=(const IntObject& rhs)
		{
			if (this != &rhs)
			{
				*mAllocatedInt = *rhs.mAllocatedInt;
			}
			return *this;
		}
		~IntObject()
		{
			delete mAllocatedInt;
		}

		bool operator==(const IntObject& iObject) const { return *mAllocatedInt == *iObject.mAllocatedInt; }
	};
};