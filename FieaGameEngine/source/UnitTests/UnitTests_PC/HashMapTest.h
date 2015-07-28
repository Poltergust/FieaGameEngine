#include <cxxtest/TestSuite.h>
#include "HashMap.h"

using namespace Library;

static std::uint32_t numBuckets = 20;

class HashMapTestSuite : public CxxTest::TestSuite
{
public:
	HashMapTestSuite() : mIntHashMap(20), mIntPointerHashMap(20), mIntObjectHashMap(20), mStringHashMap(20), mCharHashMap(20) {}

	void TestIntHashMapInstantiation(void)
	{
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapCopyConstructor(void)
	{
		IntPair pair1(1, 2);
		IntPair pair2(100, 200);

		mIntHashMap.Insert(pair1);
		mIntHashMap.Insert(pair2);
		IntHashMap otherIntHashMap(mIntHashMap);

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mIntHashMap.Size(), otherIntHashMap.Size());
		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], otherIntHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], otherIntHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mIntHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherIntHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherIntHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherIntHashMap[pair2.first], 200);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapAssignmentOperator(void)
	{
		IntPair pair1(1, 2);
		IntPair pair2(100, 200);

		IntPair pair3(5, 5);
		IntPair pair4(7, 7);
		IntPair pair5(10, 10);

		mIntHashMap.Insert(pair1);
		mIntHashMap.Insert(pair2);

		IntHashMap otherIntHashMap(20);
		otherIntHashMap.Insert(pair3);
		otherIntHashMap.Insert(pair4);
		otherIntHashMap.Insert(pair5);

		// the hash maps are distinct at this point
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);
		TS_ASSERT_EQUALS(otherIntHashMap.Size(), 3);

		// does the deep copy
		otherIntHashMap = mIntHashMap;

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mIntHashMap.Size(), otherIntHashMap.Size());
		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], otherIntHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], otherIntHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mIntHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherIntHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherIntHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherIntHashMap[pair2.first], 200);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapDestructor(void)
	{
		IntPair pair1(1, 2);
		IntPair pair2(100, 200);

		IntHashMap localIntHashMap(20);

		localIntHashMap.Insert(pair1);
		localIntHashMap.Insert(pair2);

		// the destructor gets called here for localIntHashMap, so the test succeeds if no exception is thrown
	}

	void TestIntHashMapIndexOperator(void)
	{
		IntPair pair1(1, 2);
		IntPair pair2(100, 200);

		// test for lookup of an insertion
		mIntHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);

		// test for instantiation of an empty entry
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], 0);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapInsertions(void)
	{
		// test for pair insertion on empty hash map and size readjustment
		IntPair pair1(1, 2);
		IntHashMapIterator iterator = mIntHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);

		// test for pair insertion when hash map is populated
		IntPair pair2(100, 200);
		iterator = mIntHashMap.Insert(pair2);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		// test for not inserting duplicate pair data
		iterator = mIntHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		// test for not inserting duplicate key data
		IntPair pair3(100, 200000);
		iterator = mIntHashMap.Insert(pair3);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mIntHashMap[pair3.first], pair2.second);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapFind(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		IntPair pair1(1, 2);
		IntPair pair2(5, 6);
		IntPair pair3(1000, 300000);
		IntPair pair4(1, 5);
		IntPair pair5(7, 7);

		IntHashMapIterator iterator1 = mIntHashMap.Insert(pair1);
		IntHashMapIterator iterator2 = mIntHashMap.Insert(pair2);
		IntHashMapIterator iterator3 = mIntHashMap.Insert(pair3);
		IntHashMapIterator iterator4 = mIntHashMap.Insert(pair4);
		IntHashMapIterator iterator5 = mIntHashMap.end();

		// tests for appropriate results
		TS_ASSERT_EQUALS(iterator1, mIntHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator2, mIntHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(iterator3, mIntHashMap.Find(pair3.first));
		TS_ASSERT_EQUALS(iterator4, mIntHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator5, mIntHashMap.Find(pair5.first));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 3);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapRemove(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		IntPair pair1(1, 2);
		IntPair pair2(5, 6);
		IntPair pair3(1000, 300000);
		IntPair pair4(1, 5);
		IntPair pair5(7, 7);

		IntHashMapIterator iterator1 = mIntHashMap.Insert(pair1);
		IntHashMapIterator iterator2 = mIntHashMap.Insert(pair2);
		IntHashMapIterator iterator3 = mIntHashMap.Insert(pair3);
		IntHashMapIterator iterator4 = mIntHashMap.Insert(pair4);
		IntHashMapIterator iterator5 = mIntHashMap.end();

		// tests for removing a pair and decrementing the data counter
		TS_ASSERT_EQUALS(*iterator1, *mIntHashMap.Find(pair1.first));
		TS_ASSERT_THROWS_NOTHING(mIntHashMap.Remove(pair1.first));
		TS_ASSERT_EQUALS(mIntHashMap.Find(pair1.first), mIntHashMap.end());
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		TS_ASSERT_EQUALS(*iterator3, *mIntHashMap.Find(pair3.first));
		TS_ASSERT_THROWS_NOTHING(mIntHashMap.Remove(pair3.first));
		TS_ASSERT_EQUALS(mIntHashMap.Find(pair3.first), mIntHashMap.end());
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);

		// test for inserting into a bucket after delete
		iterator4 = mIntHashMap.Insert(pair4);
		TS_ASSERT_EQUALS(*iterator2, *mIntHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(*iterator4, *mIntHashMap.Find(pair4.first));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		// test for not doing anything if the key is not found
		TS_ASSERT_THROWS_NOTHING(mIntHashMap.Remove(pair5.first));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapContainsKey(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		IntPair pair1(1, 2);
		IntPair pair2(5, 6);
		IntPair pair3(1000, 300000);
		IntPair pair4(1, 5);
		IntPair pair5(7, 7);

		mIntHashMap.Insert(pair1);
		mIntHashMap.Insert(pair2);
		mIntHashMap.Insert(pair3);

		// only pair5 should not have a key in the hash table
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(pair1.first), true);
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(pair2.first), true);
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(pair3.first), true);
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(pair4.first), true);
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(pair5.first), false);

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapBeginAndEnd(void)
	{
		// when hash map is empty, begin should equal end
		TS_ASSERT_EQUALS(mIntHashMap.begin(), mIntHashMap.end());

		// incrementing at end should do nothing
		IntHashMapIterator iterator = mIntHashMap.begin();
		++iterator;
		TS_ASSERT_EQUALS(iterator, mIntHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mIntHashMap.end());

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntHashMapIteratorIncrementors(void)
	{
		IntPair pair1(1, 2);
		IntPair pair2(3, 4);
		IntPair pair3(5, 6);

		mIntHashMap.Insert(pair1);
		mIntHashMap.Insert(pair2);
		mIntHashMap.Insert(pair3);

		TS_ASSERT_EQUALS(mIntHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mIntHashMap[pair3.first], pair3.second);

		IntHashMapIterator iterator;
		iterator = mIntHashMap.begin();
		TS_ASSERT(iterator != mIntHashMap.end());

		++iterator;
		TS_ASSERT(iterator != mIntHashMap.end());
		iterator++;
		TS_ASSERT(iterator != mIntHashMap.end());
		++iterator;
		TS_ASSERT_EQUALS(iterator, mIntHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mIntHashMap.end());

		mIntHashMap.Clear();
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestIntPointerHashMapInstantiation(void)
	{
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapCopyConstructor(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(100), 200);

		mIntPointerHashMap.Insert(pair1);
		mIntPointerHashMap.Insert(pair2);
		IntPointerHashMap otherIntPointerHashMap(mIntPointerHashMap);

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), otherIntPointerHashMap.Size());
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], otherIntPointerHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], otherIntPointerHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mIntPointerHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherIntPointerHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherIntPointerHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherIntPointerHashMap[pair2.first], 200);

		delete pair1.first;
		delete pair2.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapAssignmentOperator(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(100), 200);

		IntPointerPair pair3(new std::uint32_t(5), 5);
		IntPointerPair pair4(new std::uint32_t(7), 7);
		IntPointerPair pair5(new std::uint32_t(10), 10);

		mIntPointerHashMap.Insert(pair1);
		mIntPointerHashMap.Insert(pair2);

		IntPointerHashMap otherIntPointerHashMap(20);
		otherIntPointerHashMap.Insert(pair3);
		otherIntPointerHashMap.Insert(pair4);
		otherIntPointerHashMap.Insert(pair5);

		// the hash maps are distinct at this point
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 2);
		TS_ASSERT_EQUALS(otherIntPointerHashMap.Size(), 3);

		// does the deep copy
		otherIntPointerHashMap = mIntPointerHashMap;

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), otherIntPointerHashMap.Size());
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], otherIntPointerHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], otherIntPointerHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mIntPointerHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherIntPointerHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherIntPointerHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherIntPointerHashMap[pair2.first], 200);

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;
		delete pair4.first;
		delete pair5.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapDestructor(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(100), 200);

		IntPointerHashMap localIntPointerHashMap(20);

		localIntPointerHashMap.Insert(pair1);
		localIntPointerHashMap.Insert(pair2);

		delete pair1.first;
		delete pair2.first;

		// the destructor gets called here for localIntPointerHashMap, so the test succeeds if no exception is thrown
	}

	void TestIntPointerHashMapIndexOperator(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(100), 200);

		// test for lookup of an insertion
		mIntPointerHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 1);

		// test for instantiation of an empty entry
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], 0);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 2);

		delete pair1.first;
		delete pair2.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapInsertions(void)
	{
		// test for pair insertion on empty hash map and size readjustment
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerHashMapIterator iterator = mIntPointerHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 1);

		// test for pair insertion when hash map is populated
		IntPointerPair pair2(new std::uint32_t(100), 200);
		iterator = mIntPointerHashMap.Insert(pair2);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 2);

		// test for not inserting duplicate pair data
		iterator = mIntPointerHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 2);

		// special test for pointer; even if two pointers point to the same value, a new entry will be created
		IntPointerPair pair3(new std::uint32_t(100), 200000);
		iterator = mIntPointerHashMap.Insert(pair3);
		TS_ASSERT_EQUALS(*iterator, pair3);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair3.first], pair3.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 3);

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapFind(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(5), 6);
		IntPointerPair pair3(new std::uint32_t(1000), 300000);
		IntPointerPair pair4(new std::uint32_t(1), 5);
		IntPointerPair pair5(new std::uint32_t(7), 7);

		IntPointerHashMapIterator iterator1 = mIntPointerHashMap.Insert(pair1);
		IntPointerHashMapIterator iterator2 = mIntPointerHashMap.Insert(pair2);
		IntPointerHashMapIterator iterator3 = mIntPointerHashMap.Insert(pair3);
		IntPointerHashMapIterator iterator4 = mIntPointerHashMap.Insert(pair4);
		IntPointerHashMapIterator iterator5 = mIntPointerHashMap.end();

		// tests for appropriate results
		TS_ASSERT_EQUALS(iterator1, mIntPointerHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator2, mIntPointerHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(iterator3, mIntPointerHashMap.Find(pair3.first));
		TS_ASSERT_EQUALS(iterator4, mIntPointerHashMap.Find(pair4.first));
		TS_ASSERT_EQUALS(iterator5, mIntPointerHashMap.Find(pair5.first));
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 4);

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;
		delete pair4.first;
		delete pair5.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapRemove(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(5), 6);
		IntPointerPair pair3(new std::uint32_t(1000), 300000);
		IntPointerPair pair4(new std::uint32_t(1), 5);
		IntPointerPair pair5(new std::uint32_t(7), 7);

		IntPointerHashMapIterator iterator1 = mIntPointerHashMap.Insert(pair1);
		IntPointerHashMapIterator iterator2 = mIntPointerHashMap.Insert(pair2);
		IntPointerHashMapIterator iterator3 = mIntPointerHashMap.Insert(pair3);
		IntPointerHashMapIterator iterator4 = mIntPointerHashMap.Insert(pair4);
		IntPointerHashMapIterator iterator5 = mIntPointerHashMap.end();

		// tests for removing a pair and decrementing the data counter
		TS_ASSERT_EQUALS(*iterator1, *mIntPointerHashMap.Find(pair1.first));
		TS_ASSERT_THROWS_NOTHING(mIntPointerHashMap.Remove(pair1.first));
		TS_ASSERT_EQUALS(mIntPointerHashMap.Find(pair1.first), mIntPointerHashMap.end());
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 3);

		TS_ASSERT_EQUALS(*iterator3, *mIntPointerHashMap.Find(pair3.first));
		TS_ASSERT_THROWS_NOTHING(mIntPointerHashMap.Remove(pair3.first));
		TS_ASSERT_EQUALS(mIntPointerHashMap.Find(pair3.first), mIntPointerHashMap.end());
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 2);

		// test for inserting into a bucket after delete
		iterator1 = mIntPointerHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator2, *mIntPointerHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(*iterator1, *mIntPointerHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 3);

		// test for not doing anything if the key is not found
		TS_ASSERT_THROWS_NOTHING(mIntPointerHashMap.Remove(pair5.first));
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 3);

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;
		delete pair4.first;
		delete pair5.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapContainsKey(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(5), 6);
		IntPointerPair pair3(new std::uint32_t(1000), 300000);
		IntPointerPair pair4(new std::uint32_t(1), 5);
		IntPointerPair pair5(new std::uint32_t(7), 7);

		mIntPointerHashMap.Insert(pair1);
		mIntPointerHashMap.Insert(pair2);
		mIntPointerHashMap.Insert(pair3);

		// only pair4 and pair5 should not have a key in the hash table
		TS_ASSERT_EQUALS(mIntPointerHashMap.ContainsKey(pair1.first), true);
		TS_ASSERT_EQUALS(mIntPointerHashMap.ContainsKey(pair2.first), true);
		TS_ASSERT_EQUALS(mIntPointerHashMap.ContainsKey(pair3.first), true);
		TS_ASSERT_EQUALS(mIntPointerHashMap.ContainsKey(pair4.first), false);
		TS_ASSERT_EQUALS(mIntPointerHashMap.ContainsKey(pair5.first), false);

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;
		delete pair4.first;
		delete pair5.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapBeginAndEnd(void)
	{
		// when hash map is empty, begin should equal end
		TS_ASSERT_EQUALS(mIntPointerHashMap.begin(), mIntPointerHashMap.end());

		// incrementing at end should do nothing
		IntPointerHashMapIterator iterator = mIntPointerHashMap.begin();
		++iterator;
		TS_ASSERT_EQUALS(iterator, mIntPointerHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mIntPointerHashMap.end());

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestIntPointerHashMapIteratorIncrementors(void)
	{
		IntPointerPair pair1(new std::uint32_t(1), 2);
		IntPointerPair pair2(new std::uint32_t(3), 4);
		IntPointerPair pair3(new std::uint32_t(5), 6);

		mIntPointerHashMap.Insert(pair1);
		mIntPointerHashMap.Insert(pair2);
		mIntPointerHashMap.Insert(pair3);

		TS_ASSERT_EQUALS(mIntPointerHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mIntPointerHashMap[pair3.first], pair3.second);

		IntPointerHashMapIterator iterator;
		iterator = mIntPointerHashMap.begin();
		TS_ASSERT(iterator != mIntPointerHashMap.end());

		++iterator;
		TS_ASSERT(iterator != mIntPointerHashMap.end());
		iterator++;
		TS_ASSERT(iterator != mIntPointerHashMap.end());
		++iterator;
		TS_ASSERT_EQUALS(iterator, mIntPointerHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mIntPointerHashMap.end());

		delete pair1.first;
		delete pair2.first;
		delete pair3.first;

		mIntPointerHashMap.Clear();
		TS_ASSERT_EQUALS(mIntPointerHashMap.Size(), 0);
	}

	void TestStringHashMapInstantiation(void)
	{
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapCopyConstructor(void)
	{
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("one hundred"), 200);

		mStringHashMap.Insert(pair1);
		mStringHashMap.Insert(pair2);
		StringHashMap otherStringHashMap(mStringHashMap);

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mStringHashMap.Size(), otherStringHashMap.Size());
		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], otherStringHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], otherStringHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mStringHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mStringHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherStringHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherStringHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherStringHashMap[pair2.first], 200);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapAssignmentOperator(void)
	{
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("one hundred"), 200);

		StringPair pair3(std::string("five"), 5);
		StringPair pair4(std::string("seven"), 7);
		StringPair pair5(std::string("ten"), 10);

		mStringHashMap.Insert(pair1);
		mStringHashMap.Insert(pair2);

		StringHashMap otherStringHashMap(20);
		otherStringHashMap.Insert(pair3);
		otherStringHashMap.Insert(pair4);
		otherStringHashMap.Insert(pair5);

		// the hash maps are distinct at this point
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);
		TS_ASSERT_EQUALS(otherStringHashMap.Size(), 3);

		// does the deep copy
		otherStringHashMap = mStringHashMap;

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mStringHashMap.Size(), otherStringHashMap.Size());
		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], otherStringHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], otherStringHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mStringHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mStringHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherStringHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherStringHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherStringHashMap[pair2.first], 200);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapDestructor(void)
	{
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("one hundred"), 200);

		StringHashMap localStringHashMap(20);

		localStringHashMap.Insert(pair1);
		localStringHashMap.Insert(pair2);

		// the destructor gets called here for localStringHashMap, so the test succeeds if no exception is thrown
	}

	void TestStringHashMapIndexOperator(void)
	{
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("one hundred"), 200);

		// test for lookup of an insertion
		mStringHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 1);

		// test for instantiation of an empty entry
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], 0);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapInsertions(void)
	{
		// test for pair insertion on empty hash map and size readjustment
		StringPair pair1(std::string("one"), 2);
		StringHashMapIterator iterator = mStringHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 1);

		// test for pair insertion when hash map is populated
		StringPair pair2(std::string("one hundred"), 200);
		iterator = mStringHashMap.Insert(pair2);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		// test for not inserting duplicate pair data
		iterator = mStringHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		// test for not inserting duplicate key data
		StringPair pair3(std::string("one hundred"), 200000);
		iterator = mStringHashMap.Insert(pair3);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mStringHashMap[pair3.first], pair2.second);
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapFind(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("five"), 6);
		StringPair pair3(std::string("one thousand"), 300000);
		StringPair pair4(std::string("one"), 5);
		StringPair pair5(std::string("seven"), 7);

		StringHashMapIterator iterator1 = mStringHashMap.Insert(pair1);
		StringHashMapIterator iterator2 = mStringHashMap.Insert(pair2);
		StringHashMapIterator iterator3 = mStringHashMap.Insert(pair3);
		StringHashMapIterator iterator4 = mStringHashMap.Insert(pair4);
		StringHashMapIterator iterator5 = mStringHashMap.end();

		// tests for appropriate results
		TS_ASSERT_EQUALS(iterator1, mStringHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator2, mStringHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(iterator3, mStringHashMap.Find(pair3.first));
		TS_ASSERT_EQUALS(iterator4, mStringHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator5, mStringHashMap.Find(pair5.first));
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 3);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapRemove(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("five"), 6);
		StringPair pair3(std::string("one thousand"), 300000);
		StringPair pair4(std::string("one"), 5);
		StringPair pair5(std::string("seven"), 7);

		StringHashMapIterator iterator1 = mStringHashMap.Insert(pair1);
		StringHashMapIterator iterator2 = mStringHashMap.Insert(pair2);
		StringHashMapIterator iterator3 = mStringHashMap.Insert(pair3);
		StringHashMapIterator iterator4 = mStringHashMap.Insert(pair4);
		StringHashMapIterator iterator5 = mStringHashMap.end();

		// tests for removing a pair and decrementing the data counter
		TS_ASSERT_EQUALS(*iterator1, *mStringHashMap.Find(pair1.first));
		TS_ASSERT_THROWS_NOTHING(mStringHashMap.Remove(pair1.first));
		TS_ASSERT_EQUALS(mStringHashMap.Find(pair1.first), mStringHashMap.end());
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		TS_ASSERT_EQUALS(*iterator3, *mStringHashMap.Find(pair3.first));
		TS_ASSERT_THROWS_NOTHING(mStringHashMap.Remove(pair3.first));
		TS_ASSERT_EQUALS(mStringHashMap.Find(pair3.first), mStringHashMap.end());
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 1);

		// test for inserting into a bucket after delete
		iterator4 = mStringHashMap.Insert(pair4);
		TS_ASSERT_EQUALS(*iterator2, *mStringHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(*iterator4, *mStringHashMap.Find(pair4.first));
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		// test for not doing anything if the key is not found
		TS_ASSERT_THROWS_NOTHING(mStringHashMap.Remove(pair5.first));
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 2);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapContainsKey(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("five"), 6);
		StringPair pair3(std::string("one thousand"), 300000);
		StringPair pair4(std::string("one"), 5);
		StringPair pair5(std::string("seven"), 7);

		mStringHashMap.Insert(pair1);
		mStringHashMap.Insert(pair2);
		mStringHashMap.Insert(pair3);

		// only pair5 should not have a key in the hash table
		TS_ASSERT_EQUALS(mStringHashMap.ContainsKey(pair1.first), true);
		TS_ASSERT_EQUALS(mStringHashMap.ContainsKey(pair2.first), true);
		TS_ASSERT_EQUALS(mStringHashMap.ContainsKey(pair3.first), true);
		TS_ASSERT_EQUALS(mStringHashMap.ContainsKey(pair4.first), true);
		TS_ASSERT_EQUALS(mStringHashMap.ContainsKey(pair5.first), false);

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapBeginAndEnd(void)
	{
		// when hash map is empty, begin should equal end
		TS_ASSERT_EQUALS(mStringHashMap.begin(), mStringHashMap.end());

		// incrementing at end should do nothing
		StringHashMapIterator iterator = mStringHashMap.begin();
		++iterator;
		TS_ASSERT_EQUALS(iterator, mStringHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mStringHashMap.end());

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestStringHashMapIteratorIncrementors(void)
	{
		StringPair pair1(std::string("one"), 2);
		StringPair pair2(std::string("three"), 4);
		StringPair pair3(std::string("five"), 6);

		mStringHashMap.Insert(pair1);
		mStringHashMap.Insert(pair2);
		mStringHashMap.Insert(pair3);

		TS_ASSERT_EQUALS(mStringHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mStringHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mStringHashMap[pair3.first], pair3.second);

		StringHashMapIterator iterator;
		iterator = mStringHashMap.begin();
		TS_ASSERT(iterator != mStringHashMap.end());

		++iterator;
		TS_ASSERT(iterator != mStringHashMap.end());
		iterator++;
		TS_ASSERT(iterator != mStringHashMap.end());
		++iterator;
		TS_ASSERT_EQUALS(iterator, mStringHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mStringHashMap.end());

		mStringHashMap.Clear();
		TS_ASSERT_EQUALS(mStringHashMap.Size(), 0);
	}

	void TestCharHashMapInstantiation(void)
	{
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapCopyConstructor(void)
	{
		CharPair pair1("one", 2);
		CharPair pair2("one hundred", 200);

		mCharHashMap.Insert(pair1);
		mCharHashMap.Insert(pair2);
		CharHashMap otherCharHashMap(mCharHashMap);

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mCharHashMap.Size(), otherCharHashMap.Size());
		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], otherCharHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], otherCharHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mCharHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mCharHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherCharHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherCharHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherCharHashMap[pair2.first], 200);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapAssignmentOperator(void)
	{
		CharPair pair1("one", 2);
		CharPair pair2("one hundred", 200);

		CharPair pair3("five", 5);
		CharPair pair4("seven", 7);
		CharPair pair5("ten", 10);

		mCharHashMap.Insert(pair1);
		mCharHashMap.Insert(pair2);

		CharHashMap otherCharHashMap(20);
		otherCharHashMap.Insert(pair3);
		otherCharHashMap.Insert(pair4);
		otherCharHashMap.Insert(pair5);

		// the hash maps are distinct at this point
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);
		TS_ASSERT_EQUALS(otherCharHashMap.Size(), 3);

		// does the deep copy
		otherCharHashMap = mCharHashMap;

		// the two hash maps should be identical
		TS_ASSERT_EQUALS(mCharHashMap.Size(), otherCharHashMap.Size());
		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], otherCharHashMap[pair1.first]);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], otherCharHashMap[pair2.first]);

		// removing an item in one hash map should have no effect on the other
		mCharHashMap.Remove(pair1.first);

		TS_ASSERT_EQUALS(mCharHashMap.Size(), 1);
		TS_ASSERT_EQUALS(otherCharHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], 200);
		TS_ASSERT_EQUALS(otherCharHashMap[pair1.first], 2);
		TS_ASSERT_EQUALS(otherCharHashMap[pair2.first], 200);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapDestructor(void)
	{
		CharPair pair1("one", 2);
		CharPair pair2("one hundred", 200);

		CharHashMap localCharHashMap(20);

		localCharHashMap.Insert(pair1);
		localCharHashMap.Insert(pair2);

		// the destructor gets called here for localCharHashMap, so the test succeeds if no exception is thrown
	}

	void TestCharHashMapIndexOperator(void)
	{
		CharPair pair1("one", 2);
		CharPair pair2("one hundred", 200);

		// test for lookup of an insertion
		mCharHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 1);

		// test for instantiation of an empty entry
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], 0);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapInsertions(void)
	{
		// test for pair insertion on empty hash map and size readjustment
		CharPair pair1("one", 2);
		CharHashMapIterator iterator = mCharHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 1);

		// test for pair insertion when hash map is populated
		CharPair pair2("one hundred", 200);
		iterator = mCharHashMap.Insert(pair2);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		// test for not inserting duplicate pair data
		iterator = mCharHashMap.Insert(pair1);
		TS_ASSERT_EQUALS(*iterator, pair1);
		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		// test for not inserting duplicate key data
		CharPair pair3("one hundred", 200000);
		iterator = mCharHashMap.Insert(pair3);
		TS_ASSERT_EQUALS(*iterator, pair2);
		TS_ASSERT_EQUALS(mCharHashMap[pair3.first], pair2.second);
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapFind(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		CharPair pair1("one", 2);
		CharPair pair2("five", 6);
		CharPair pair3("one thousand", 300000);
		CharPair pair4("one", 5);
		CharPair pair5("seven", 7);

		CharHashMapIterator iterator1 = mCharHashMap.Insert(pair1);
		CharHashMapIterator iterator2 = mCharHashMap.Insert(pair2);
		CharHashMapIterator iterator3 = mCharHashMap.Insert(pair3);
		CharHashMapIterator iterator4 = mCharHashMap.Insert(pair4);
		CharHashMapIterator iterator5 = mCharHashMap.end();

		// tests for appropriate results
		TS_ASSERT_EQUALS(iterator1, mCharHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator2, mCharHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(iterator3, mCharHashMap.Find(pair3.first));
		TS_ASSERT_EQUALS(iterator4, mCharHashMap.Find(pair1.first));
		TS_ASSERT_EQUALS(iterator5, mCharHashMap.Find(pair5.first));
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 3);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapRemove(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		CharPair pair1("one", 2);
		CharPair pair2("five", 6);
		CharPair pair3("one thousand", 300000);
		CharPair pair4("one", 5);
		CharPair pair5("seven", 7);

		CharHashMapIterator iterator1 = mCharHashMap.Insert(pair1);
		CharHashMapIterator iterator2 = mCharHashMap.Insert(pair2);
		CharHashMapIterator iterator3 = mCharHashMap.Insert(pair3);
		CharHashMapIterator iterator4 = mCharHashMap.Insert(pair4);
		CharHashMapIterator iterator5 = mCharHashMap.end();

		// tests for removing a pair and decrementing the data counter
		TS_ASSERT_EQUALS(*iterator1, *mCharHashMap.Find(pair1.first));
		TS_ASSERT_THROWS_NOTHING(mCharHashMap.Remove(pair1.first));
		TS_ASSERT_EQUALS(mCharHashMap.Find(pair1.first), mCharHashMap.end());
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		TS_ASSERT_EQUALS(*iterator3, *mCharHashMap.Find(pair3.first));
		TS_ASSERT_THROWS_NOTHING(mCharHashMap.Remove(pair3.first));
		TS_ASSERT_EQUALS(mCharHashMap.Find(pair3.first), mCharHashMap.end());
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 1);

		// test for inserting into a bucket after delete
		iterator4 = mCharHashMap.Insert(pair4);
		TS_ASSERT_EQUALS(*iterator2, *mCharHashMap.Find(pair2.first));
		TS_ASSERT_EQUALS(*iterator4, *mCharHashMap.Find(pair4.first));
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		// test for not doing anything if the key is not found
		TS_ASSERT_THROWS_NOTHING(mCharHashMap.Remove(pair5.first));
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 2);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapContainsKey(void)
	{
		// the keys for pair1 and pair2 actually hash to the same bucket index
		CharPair pair1("one", 2);
		CharPair pair2("five", 6);
		CharPair pair3("one thousand", 300000);
		CharPair pair4("one", 5);
		CharPair pair5("seven", 7);

		mCharHashMap.Insert(pair1);
		mCharHashMap.Insert(pair2);
		mCharHashMap.Insert(pair3);

		// only pair5 should not have a key in the hash table
		TS_ASSERT_EQUALS(mCharHashMap.ContainsKey(pair1.first), true);
		TS_ASSERT_EQUALS(mCharHashMap.ContainsKey(pair2.first), true);
		TS_ASSERT_EQUALS(mCharHashMap.ContainsKey(pair3.first), true);
		TS_ASSERT_EQUALS(mCharHashMap.ContainsKey(pair4.first), true);
		TS_ASSERT_EQUALS(mCharHashMap.ContainsKey(pair5.first), false);

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapBeginAndEnd(void)
	{
		// when hash map is empty, begin should equal end
		TS_ASSERT_EQUALS(mCharHashMap.begin(), mCharHashMap.end());

		// incrementing at end should do nothing
		CharHashMapIterator iterator = mCharHashMap.begin();
		++iterator;
		TS_ASSERT_EQUALS(iterator, mCharHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mCharHashMap.end());

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
	}

	void TestCharHashMapIteratorIncrementors(void)
	{
		CharPair pair1("one", 2);
		CharPair pair2("three", 4);
		CharPair pair3("five", 6);

		mCharHashMap.Insert(pair1);
		mCharHashMap.Insert(pair2);
		mCharHashMap.Insert(pair3);

		TS_ASSERT_EQUALS(mCharHashMap[pair1.first], pair1.second);
		TS_ASSERT_EQUALS(mCharHashMap[pair2.first], pair2.second);
		TS_ASSERT_EQUALS(mCharHashMap[pair3.first], pair3.second);

		CharHashMapIterator iterator;
		iterator = mCharHashMap.begin();
		TS_ASSERT(iterator != mCharHashMap.end());

		++iterator;
		TS_ASSERT(iterator != mCharHashMap.end());
		iterator++;
		TS_ASSERT(iterator != mCharHashMap.end());
		++iterator;
		TS_ASSERT_EQUALS(iterator, mCharHashMap.end());
		iterator++;
		TS_ASSERT_EQUALS(iterator, mCharHashMap.end());

		mCharHashMap.Clear();
		TS_ASSERT_EQUALS(mCharHashMap.Size(), 0);
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

	class IntObjectHash
	{
	public:
		std::uint32_t operator()(const IntObject& key) const
		{
			std::uint32_t hash = 0;

			const unsigned char* keyArray = reinterpret_cast<const unsigned char*>(key.mAllocatedInt);
			int keySize = sizeof(int*);
			for (int i = 0; i < keySize; i++)
			{
				hash = hashPrime * hash + keyArray[keySize];
			}

			return hash;
		}
	};

	typedef std::pair<std::uint32_t, std::uint32_t> IntPair;
	typedef std::pair<std::uint32_t*, std::uint32_t> IntPointerPair;
	typedef std::pair<IntObject, std::uint32_t> IntObjectPair;
	typedef std::pair<std::string, std::uint32_t> StringPair;
	typedef std::pair<char*, std::uint32_t> CharPair;

	typedef HashMap<std::uint32_t, std::uint32_t> IntHashMap;
	typedef HashMap<std::uint32_t*, std::uint32_t> IntPointerHashMap;
	typedef HashMap<IntObject, std::uint32_t, IntObjectHash> IntObjectHashMap;
	typedef HashMap<std::string, std::uint32_t> StringHashMap;
	typedef HashMap<char*, std::uint32_t> CharHashMap;

	typedef HashMap<std::uint32_t, std::uint32_t>::Iterator IntHashMapIterator;
	typedef HashMap<std::uint32_t*, std::uint32_t>::Iterator IntPointerHashMapIterator;
	typedef HashMap<IntObject, std::uint32_t, IntObjectHash>::Iterator IntObjectHashMapIterator;
	typedef HashMap<std::string, std::uint32_t>::Iterator StringHashMapIterator;
	typedef HashMap<char*, std::uint32_t>::Iterator CharHashMapIterator;

	IntHashMap mIntHashMap;
	IntPointerHashMap mIntPointerHashMap;
	IntObjectHashMap mIntObjectHashMap;
	StringHashMap mStringHashMap;
	CharHashMap mCharHashMap;
};