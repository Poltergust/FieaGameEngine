#include <cxxtest/TestSuite.h>
#include "Scope.h"

using namespace Library;

class ScopeTestSuite : public CxxTest::TestSuite
{
public:
	void TestScopeInstantiation(void)
	{
		Scope scope;
		TS_ASSERT_EQUALS(scope.GetParent(), nullptr);
		TS_ASSERT_THROWS_NOTHING(scope.Clear());
	}

	void TestScopeCopyConstructor(void)
	{
		Scope s1;
		Datum& d1 = s1.Append(std::string("d1"));
		d1.Set(3);
		Datum& d2 = s1.Append(std::string("d2"));
		d2.Set(3.0f);

		Scope& s2 = s1.AppendScope(std::string("d3"));

		// adopting same scope
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d3"), 0));
		Datum& d4 = s2.Append(std::string("d4"));
		d4.Set(glm::vec4(1.0f));

		Scope& s3 = s1.AppendScope(std::string("d3"));
		Datum& d5 = s3.Append(std::string("d5"));
		d5.Set(glm::mat4(2.0f));

		s2.Append(std::string("d6"));
		Scope& s4 = s2.AppendScope(std::string("d6"));

		// adopting scope of different scope
		s3.Adopt(s4, std::string("d6"), 0);
		Datum& d7 = s4.Append(std::string("d7"));
		d7.Set(std::string("Hello"));

		// test copy constructor with a completely different scope
		Scope anotherS1(s1);
		TS_ASSERT_EQUALS(anotherS1, s1);
		TS_ASSERT(&anotherS1 != &s1);
	}

	void TestScopeAssignmentOperator(void)
	{
		Scope s1;
		Datum& d1 = s1.Append(std::string("d1"));
		d1.Set(3);
		Datum& d2 = s1.Append(std::string("d2"));
		d2.Set(3.0f);

		Scope& s2 = s1.AppendScope(std::string("d3"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d3"), 0));
		Datum& d4 = s2.Append(std::string("d4"));
		d4.Set(glm::vec4(1.0f));

		Scope& s3 = s1.AppendScope(std::string("d3"));
		Datum& d5 = s3.Append(std::string("d5"));
		d5.Set(glm::mat4(2.0f));

		s2.Append(std::string("d6"));
		s2.AppendScope(std::string("d6"));

		Scope s4;
		s2.Adopt(s4, std::string("d6"), 0);
		Datum& d7 = s4.Append(std::string("d7"));
		d7.Set(std::string("Hello"));

		// test assignment operator with a completely different scope
		Scope anotherS1;
		TS_ASSERT_THROWS_NOTHING(anotherS1 = s1);
		TS_ASSERT_EQUALS(anotherS1, s1);
		TS_ASSERT(&anotherS1 != &s1);

		// test self assignment
		TS_ASSERT_THROWS_NOTHING(s1 = s1);
	}

	void TestScopeStringIndexOperator(void)
	{
		Scope s1;
		Datum& d1 = s1[std::string("d1")];
		Datum& d2 = s1[std::string("d2")];
		Datum& anotherD1 = s1[std::string("d1")];

		d1.Set(1);
		d2.Set(1.0f);

		TS_ASSERT_EQUALS(d1, s1[std::string("d1")]);
		TS_ASSERT_EQUALS(d2, s1[std::string("d2")]);
		TS_ASSERT_EQUALS(d1, anotherD1);
	}

	void TestScopeIntegerIndexOperator(void)
	{
		Scope s1;
		TS_ASSERT_THROWS_ANYTHING(s1[10]);
		
		s1.Append(std::string("d1"));
		s1.Append(std::string("d2"));
		s1.Append(std::string("d3"));

		TS_ASSERT_THROWS_NOTHING(s1[2]);
		TS_ASSERT_THROWS_ANYTHING(s1[3]);

		Datum& d2 = s1[1];
		d2.Set(std::string("Hello"));
		TS_ASSERT_EQUALS(s1[1].GetString(), std::string("Hello"));
	}

	void TestScopeComparisonOperators(void)
	{
		Scope s1;
		Datum& d1 = s1.Append(std::string("d1"));
		d1.Set(3);
		Datum& d2 = s1.Append(std::string("d2"));
		d2.Set(3.0f);

		Scope& s2 = s1.AppendScope(std::string("d3"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d3"), 0));
		Datum& d4 = s2.Append(std::string("d4"));
		d4.Set(glm::vec4(1.0f));
		s2.Append(std::string("d5"));
		s2.AppendScope(std::string("d5"));

		Scope s3;
		s2.Adopt(s3, std::string("d5"), 0);
		Datum& d6 = s3.Append(std::string("d6"));
		d6.Set(std::string("Hello"));

		Scope anotherScope1;
		Datum& anotherDatum1 = anotherScope1.Append(std::string("anotherDatum1"));
		anotherDatum1.Set(3);
		Datum& anotherDatum2 = anotherScope1.Append(std::string("anotherDatum2"));
		anotherDatum2.Set(3.0f);

		Scope& anotherScope2 = anotherScope1.AppendScope(std::string("anotherDatum3"));
		TS_ASSERT_THROWS_NOTHING(anotherScope1.Adopt(anotherScope2, std::string("anotherDatum3"), 0));
		Datum& anotherDatum4 = anotherScope2.Append(std::string("anotherDatum4"));
		anotherDatum4.Set(glm::vec4(1.0f));
		anotherScope2.Append(std::string("anotherDatum5"));
		anotherScope2.AppendScope(std::string("anotherDatum5"));

		Scope anotherScope3;
		anotherScope2.Adopt(anotherScope3, std::string("anotherDatum5"), 0);
		Datum& anotherDatum6 = anotherScope3.Append(std::string("anotherDatum6"));
		anotherDatum6.Set(std::string("Hello"));

		// test for equality despite using different keys
		TS_ASSERT_EQUALS(s1, anotherScope1);

		// test for non-equality after changing a value at the most nested scope
		anotherDatum6.Set(std::string("World"));
		TS_ASSERT(s1 != anotherScope1);
	}

	void TestScopeFind(void)
	{
		Scope s1;
		Datum& d1 = s1.Append(std::string("d1"));
		d1.Set(3);
		Datum& d2 = s1.Append(std::string("d2"));
		d2.Set(3.0f);

		Scope& s2 = s1.AppendScope(std::string("d3"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d3"), 0));
		Datum& d4 = s2.Append(std::string("d4"));
		d4.Set(glm::vec4(1.0f));
		s2.Append(std::string("d5"));
		s2.AppendScope(std::string("d5"));

		Datum* findDatum = s1.Find(std::string("d1"));
		TS_ASSERT_EQUALS(findDatum->GetInteger(), 3);

		findDatum = s1.Find(std::string("d4"));
		TS_ASSERT_EQUALS(findDatum, nullptr);
	}

	void TestScopeSearch(void)
	{
		Scope s1;
		Datum& d1 = s1.Append(std::string("d1"));
		d1.Set(3);
		Datum& d2 = s1.Append(std::string("d2"));
		d2.Set(3.0f);

		Scope& s2 = s1.AppendScope(std::string("d3"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d3"), 0));
		Datum& d4 = s2.Append(std::string("d4"));
		d4.Set(glm::vec4(1.0f));
		s2.Append(std::string("d5"));
		s2.AppendScope(std::string("d5"));

		Scope s3;
		s2.Adopt(s3, std::string("d5"), 0);
		Datum& d6 = s3.Append(std::string("d6"));
		d6.Set(std::string("Hello"));

		// test for valid search within own scope
		Datum* findDatum = s2.Search(std::string("d4"));
		TS_ASSERT_EQUALS(findDatum->GetVector(), glm::vec4(1.0f));

		// test for valid search within ancestor scope
		findDatum = s3.Search(std::string("d4"));
		TS_ASSERT_EQUALS(findDatum->GetVector(), glm::vec4(1.0f));

		// test for invalid search with the key being in a child
		findDatum = s1.Search(std::string("d4"));
		TS_ASSERT_EQUALS(findDatum, nullptr);
	}

	void TestScopeAppend(void)
	{
		Scope s1;

		// test for proper append
		Datum& d1 = s1.Append(std::string("d1"));
		TS_ASSERT_EQUALS(s1[std::string("d1")].GetType(), Datum::Unknown);

		// test for being able to change type
		d1.Set(3);
		TS_ASSERT_EQUALS(s1[std::string("d1")].GetType(), Datum::Integer);
	}

	void TestScopeAppendScope(void)
	{
		Scope s1;
		s1.AppendScope(std::string("d1"));
		s1.AppendScope(std::string("d2"));
		s1.AppendScope(std::string("d2"));

		// test for scope being appended
		TS_ASSERT_EQUALS(s1.Find(std::string("d1"))->Size(), 1);

		// test for multiple scopes within the same datum
		TS_ASSERT_EQUALS(s1.Find(std::string("d2"))->Size(), 2);
	}

	void TestScopeAdoptAndOrphan(void)
	{
		Scope s1;

		s1.AppendScope(std::string("d1"));
		Scope s2;
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s2, std::string("d1"), 0));
		TS_ASSERT_EQUALS(s1.Find(std::string("d1"))->Size(), 1);

		Scope& s3 = s1.AppendScope(std::string("d1"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s3, std::string("d1"), 1));
		TS_ASSERT_EQUALS(s1.Find(std::string("d1"))->Size(), 2);

		Scope& s4 = s3.AppendScope(std::string("d2"));
		TS_ASSERT_THROWS_NOTHING(s1.Adopt(s4, std::string("d2"), 0));
		TS_ASSERT_EQUALS(s1.Find(std::string("d2"))->Size(), 1);

		// when you orphan a scope, I have it so that it keeps its children
		s3.Orphan();
		TS_ASSERT_EQUALS(s1.Find(std::string("d1"))->GetTable(1), nullptr);
		TS_ASSERT_EQUALS(s1.Find(std::string("d2"))->GetTable(0), &s4);
	}

	void TestScopeGetParent(void)
	{
		Scope s1;
		Scope& s2 = s1.AppendScope(std::string("d1"));
		TS_ASSERT_EQUALS(s2.GetParent(), &s1);

		Scope& s3 = s2.AppendScope(std::string("d2"));
		TS_ASSERT_EQUALS(s3.GetParent(), &s2);
	}

	void TestScopeFindName(void)
	{
		Scope s1;
		std::string name = std::string();

		Scope& s2 = s1.AppendScope(std::string("d1"));
		TS_ASSERT(s1.FindName(&s2, name));
		TS_ASSERT_EQUALS(name, std::string("d1"));

		Scope s3;
		TS_ASSERT_EQUALS(s1.FindName(&s3, name), false);
	}
};