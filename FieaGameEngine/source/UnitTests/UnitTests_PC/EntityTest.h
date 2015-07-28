#include <cxxtest/TestSuite.h>
#include "Entity.h"

using namespace Library;

class EntityTestSuite : public CxxTest::TestSuite
{
public:
	void TestEntityInstantiation(void)
	{
		Entity* entity = new Entity();
		delete entity;
	}

	void TestEntityName(void)
	{
		Entity* entity = new Entity();

		TS_ASSERT_EQUALS(entity->Name(), std::string());

		delete entity;
	}
};