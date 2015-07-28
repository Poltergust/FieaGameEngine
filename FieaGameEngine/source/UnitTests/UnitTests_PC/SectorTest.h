#include <cxxtest/TestSuite.h>
#include "Sector.h"
#include "Entity.h"
#include "EntityFoo.h"

using namespace Library;

class SectorTestSuite : public CxxTest::TestSuite
{
public:
	void TestSectorInstantiation(void)
	{
		Sector* sector = new Sector(std::string("S"));
		delete sector;
	}

	void TestSectorName(void)
	{
		Sector* sector = new Sector(std::string("S"));

		TS_ASSERT_EQUALS(sector->Name(), std::string("S"));

		delete sector;
	}

	void TestEntitiesWithinSectors(void)
	{
		Sector* sector = new Sector(std::string("S"));
		EntityFoo::EntityFooFactory entityFooFactory;

		Scope* entities = sector->Entities();
		TS_ASSERT_EQUALS(entities->Size(), 0);

		Entity* entity1 = nullptr;
		TS_ASSERT_THROWS_NOTHING(entity1 = sector->CreateEntity(std::string("EntityFoo"), std::string("Player")));
		TS_ASSERT(entity1 != nullptr);
		TS_ASSERT_EQUALS(entities->Size(), 1);

		Entity* entity2 = nullptr;
		TS_ASSERT_THROWS_NOTHING(entity2 = sector->CreateEntity(std::string("EntityFoo"), std::string("Enemy")));
		TS_ASSERT(entity2 != nullptr);
		TS_ASSERT_EQUALS(entities->Size(), 2);

		TS_ASSERT_EQUALS((*entities)[std::string("Player")].GetTable()->As<Entity>(), entity1);
		TS_ASSERT_EQUALS((*entities)[std::string("Enemy")].GetTable()->As<Entity>(), entity2);

		TS_ASSERT_EQUALS(entities->GetParent(), sector->As<Scope>());
		TS_ASSERT_EQUALS(entity1->GetSector(), sector);
		TS_ASSERT_EQUALS(entity2->GetSector(), sector);

		delete sector;
	}
};