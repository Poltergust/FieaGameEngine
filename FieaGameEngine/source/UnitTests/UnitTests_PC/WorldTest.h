#include <cxxtest/TestSuite.h>
#include <thread>
#include <chrono>
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "EntityFoo.h"

using namespace Library;

class WorldTestSuite : public CxxTest::TestSuite
{
public:
	void TestWorldInstantiation(void)
	{
		World* world = new World(std::string("World"));
		delete world;
	}

	void TestWorldNameFunctionality(void)
	{
		World* world = new World(std::string("World"));
		TS_ASSERT_EQUALS(world->Name(), std::string("World"));

		world->SetName("Planet");
		TS_ASSERT_EQUALS(world->Name(), std::string("Planet"));

		delete world;
	}

	void TestSectorsWithinWorld(void)
	{
		World* world = new World(std::string("World"));

		Scope* sectors = world->Sectors();
		TS_ASSERT_EQUALS(sectors->Size(), 0);

		Sector* sector1 = nullptr;
		TS_ASSERT_THROWS_NOTHING(sector1 = world->CreateSector(std::string("A")));
		TS_ASSERT(sector1 != nullptr);
		TS_ASSERT_EQUALS(sectors->Size(), 1);

		Sector* sector2 = nullptr;
		TS_ASSERT_THROWS_NOTHING(sector2 = world->CreateSector(std::string("B")));
		TS_ASSERT(sector2 != nullptr);
		TS_ASSERT_EQUALS(sectors->Size(), 2);

		TS_ASSERT_EQUALS((*sectors)[std::string("A")].GetTable()->As<Sector>(), sector1);
		TS_ASSERT_EQUALS((*sectors)[std::string("B")].GetTable()->As<Sector>(), sector2);

		TS_ASSERT_EQUALS(sectors->GetParent(), world->As<Scope>());
		TS_ASSERT_EQUALS(sector1->GetWorld(), world);
		TS_ASSERT_EQUALS(sector2->GetWorld(), world);

		// test for update since it only does anything if world has sectors
		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(world->GetWorldState()->mWorld, world);
		TS_ASSERT_EQUALS(world->GetWorldState()->mSector, sector2);
		TS_ASSERT_EQUALS(world->GetWorldState()->mEntity, nullptr);

		delete world;
	}

	void TestEntitiesWithinSectorsWithinWorld(void)
	{
		World* world = new World(std::string("World"));
		EntityFoo::EntityFooFactory entityFooFactory;

		Sector* sector1 = world->CreateSector(std::string("A"));
		Sector* sector2 = world->CreateSector(std::string("B"));

		Entity* entity1 = nullptr;
		Entity* entity2 = nullptr;
		TS_ASSERT_THROWS_NOTHING(entity1 = sector1->CreateEntity(std::string("EntityFoo"), std::string("Player1")));
		TS_ASSERT_THROWS_NOTHING(entity2 = sector1->CreateEntity(std::string("EntityFoo"), std::string("Player2")));
		TS_ASSERT(entity1 != nullptr);
		TS_ASSERT(entity2 != nullptr);
		TS_ASSERT_EQUALS(sector1->Entities()->Size(), 2);

		TS_ASSERT_EQUALS((*sector1->Entities())[std::string("Player1")].GetTable()->As<Entity>(), entity1);
		TS_ASSERT_EQUALS((*sector1->Entities())[std::string("Player2")].GetTable()->As<Entity>(), entity2);

		Entity* entity3 = nullptr;
		TS_ASSERT_THROWS_NOTHING(entity3 = sector2->CreateEntity(std::string("EntityFoo"), std::string("Enemy")));
		TS_ASSERT(entity3 != nullptr);
		TS_ASSERT_EQUALS(sector2->Entities()->Size(), 1);

		TS_ASSERT_EQUALS((*sector2->Entities())[std::string("Enemy")].GetTable()->As<Entity>(), entity3);

		TS_ASSERT_EQUALS(entity1->GetSector(), sector1);
		TS_ASSERT_EQUALS(entity2->GetSector(), sector1);
		TS_ASSERT_EQUALS(entity3->GetSector(), sector2);
		TS_ASSERT_EQUALS(sector1->GetWorld(), sector2->GetWorld());

		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(world->GetWorldState()->mWorld, world);
		TS_ASSERT_EQUALS(world->GetWorldState()->mSector, sector2);
		TS_ASSERT_EQUALS(world->GetWorldState()->mEntity, entity3);

		delete world;
	}

	// TESTS FOR ASSIGNMENT 14 START HERE!

	void TestActionsWithinEntitiesWithinSectorsWithinWorld(void)
	{
		World* world = new World(std::string("World"));
		EntityFoo::EntityFooFactory entityFooFactory;

		Sector* sector1 = world->CreateSector(std::string("A"));

		Entity* entity1 = sector1->CreateEntity(std::string("EntityFoo"), std::string("Player1"));

		Action* action1 = nullptr;
		TS_ASSERT_THROWS_NOTHING(action1 = entity1->CreateAction(std::string("ActionListIf"), std::string("If")));
		TS_ASSERT(action1 != nullptr);
		TS_ASSERT_EQUALS(entity1->Actions()->Size(), 1);

		TS_ASSERT_EQUALS((*entity1->Actions())[std::string("If")].GetTable()->As<Action>(), action1);

		TS_ASSERT_EQUALS(action1->GetEntity(), entity1);
		TS_ASSERT_EQUALS(action1->GetContainingAction(), nullptr);
		TS_ASSERT_THROWS_ANYTHING(world->Update());

		Action* actionList1 = nullptr;
		Action* actionList2 = nullptr;
		TS_ASSERT_THROWS_NOTHING(actionList1 = action1->As<ActionListIf>()->CreateThenAction(std::string("ActionList"), std::string("then")));
		TS_ASSERT_THROWS_NOTHING(actionList2 = action1->As<ActionListIf>()->CreateElseAction(std::string("ActionList"), std::string("else")));
		TS_ASSERT(actionList1 != nullptr);
		TS_ASSERT(actionList2 != nullptr);
		TS_ASSERT_EQUALS(actionList1, action1->As<ActionListIf>()->ThenAction()->As<ActionList>());
		TS_ASSERT_EQUALS(actionList2, action1->As<ActionListIf>()->ElseAction()->As<ActionList>());

		Action* actionPrint1 = nullptr;
		Action* actionPrint2 = nullptr;
		TS_ASSERT_THROWS_NOTHING(actionPrint1 = actionList1->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("thenPrint")));
		TS_ASSERT_THROWS_NOTHING(actionPrint2 = actionList2->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("elsePrint")));
		TS_ASSERT(actionPrint1 != nullptr);
		TS_ASSERT(actionPrint2 != nullptr);
		TS_ASSERT_EQUALS(actionPrint1, (*actionList1->As<ActionList>()->ContainedActions())[std::string("thenPrint")].GetTable()->As<ActionPrint>());
		TS_ASSERT_EQUALS(actionPrint2, (*actionList2->As<ActionList>()->ContainedActions())[std::string("elsePrint")].GetTable()->As<ActionPrint>());

		actionPrint1->As<ActionPrint>()->SetString(std::string("Yes"));
		actionPrint2->As<ActionPrint>()->SetString(std::string("No"));

		TS_ASSERT_EQUALS(actionList1->GetEntity(), entity1);
		TS_ASSERT_EQUALS(actionList2->GetEntity(), entity1);
		TS_ASSERT_EQUALS(actionList1->GetContainingAction(), action1);
		TS_ASSERT_EQUALS(actionList2->GetContainingAction(), action1);

		TS_ASSERT_EQUALS(actionPrint1->GetEntity(), entity1);
		TS_ASSERT_EQUALS(actionPrint2->GetEntity(), entity1);
		TS_ASSERT_EQUALS(actionPrint1->GetContainingAction(), actionList1);
		TS_ASSERT_EQUALS(actionPrint2->GetContainingAction(), actionList2);

		delete world;
	}

	// TESTS FOR ASSIGNMENT 16 START HERE!

	void TestNoDelayReactionsWithinEntitiesWithinSectorsWithinWorld(void)
	{
		World* world = new World(std::string("World"));
		EntityFoo::EntityFooFactory entityFooFactory;

		Sector* sector1 = world->CreateSector(std::string("A"));

		Entity* entity1 = sector1->CreateEntity(std::string("EntityFoo"), std::string("Player1"));

		Action* reaction1 = nullptr;
		TS_ASSERT_THROWS_NOTHING(reaction1 = entity1->CreateAction(std::string("ReactionAttributed"), std::string("Reaction")));
		TS_ASSERT(reaction1 != nullptr);
		TS_ASSERT_EQUALS(entity1->Actions()->Size(), 1);

		TS_ASSERT_THROWS_ANYTHING(reaction1->As<ReactionAttributed>()->SetSubtype(0, 10))
		TS_ASSERT_THROWS_NOTHING(reaction1->As<ReactionAttributed>()->SetSubtype(0, 4));

		Action* actionListIf = reaction1->As<ActionList>()->CreateActionForList(std::string("ActionListIf"), std::string("If"));

		Action* actionListThen = actionListIf->As<ActionListIf>()->CreateThenAction(std::string("ActionList"), std::string("then"));
		Action* actionListElse = actionListIf->As<ActionListIf>()->CreateElseAction(std::string("ActionList"), std::string("else"));

		Action* actionPrintThen = actionListThen->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("thenPrint"));
		Action* actionPrintElse = actionListElse->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("elsePrint"));

		actionPrintThen->As<ActionPrint>()->SetString(std::string("YesReaction"));
		actionPrintElse->As<ActionPrint>()->SetString(std::string("NoReaction"));

		Action* actionEvent = nullptr;
		TS_ASSERT_THROWS_NOTHING(actionEvent = entity1->CreateAction(std::string("ActionEvent"), std::string("Event")));
		TS_ASSERT(actionEvent != nullptr);
		TS_ASSERT_EQUALS(entity1->Actions()->Size(), 2);

		// with an incorrect subtype, the reaction containing ActionListIf should never be notified
		actionEvent->As<ActionEvent>()->SetSubtype(1);
		actionEvent->As<ActionEvent>()->SetDelay(0.0f);

		/*actionListIf->As<ActionListIf>()->SetCondition(1);
		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		// now we are notifying the reaction properly
		actionEvent->As<ActionEvent>()->SetSubtype(0);

		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, true);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		actionListIf->As<ActionListIf>()->SetCondition(0);
		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, true);*/

		delete world;
	}

	void TestDelayedReactionsWithinEntitiesWithinSectorsWithinWorld(void)
	{
		World* world = new World(std::string("World"));
		EntityFoo::EntityFooFactory entityFooFactory;

		Sector* sector1 = world->CreateSector(std::string("A"));

		Entity* entity1 = sector1->CreateEntity(std::string("EntityFoo"), std::string("Player1"));

		Action* reaction1 = nullptr;
		TS_ASSERT_THROWS_NOTHING(reaction1 = entity1->CreateAction(std::string("ReactionAttributed"), std::string("Reaction")));
		TS_ASSERT(reaction1 != nullptr);
		TS_ASSERT_EQUALS(entity1->Actions()->Size(), 1);

		TS_ASSERT_THROWS_ANYTHING(reaction1->As<ReactionAttributed>()->SetSubtype(0, 10));
		TS_ASSERT_THROWS_NOTHING(reaction1->As<ReactionAttributed>()->SetSubtype(0, 4));

		Action* actionListIf = reaction1->As<ActionList>()->CreateActionForList(std::string("ActionListIf"), std::string("If"));

		Action* actionListThen = actionListIf->As<ActionListIf>()->CreateThenAction(std::string("ActionList"), std::string("then"));
		Action* actionListElse = actionListIf->As<ActionListIf>()->CreateElseAction(std::string("ActionList"), std::string("else"));

		Action* actionPrintThen = actionListThen->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("thenPrint"));
		Action* actionPrintElse = actionListElse->As<ActionList>()->CreateActionForList(std::string("ActionPrint"), std::string("elsePrint"));

		actionPrintThen->As<ActionPrint>()->SetString(std::string("YesReaction"));
		actionPrintElse->As<ActionPrint>()->SetString(std::string("NoReaction"));

		Action* actionEvent = nullptr;
		TS_ASSERT_THROWS_NOTHING(actionEvent = entity1->CreateAction(std::string("ActionEvent"), std::string("Event")));
		TS_ASSERT(actionEvent != nullptr);
		TS_ASSERT_EQUALS(entity1->Actions()->Size(), 2);

		// the reaction should only be notified after 200 milliseconds
		actionEvent->As<ActionEvent>()->SetSubtype(0);
		actionEvent->As<ActionEvent>()->SetDelay(0.2f);

		/*actionListIf->As<ActionListIf>()->SetCondition(1);
		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		// notify the reaction
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, true);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		// since this new event does not notify the reaction, ActionListIf still has the values it had the last update
		actionListIf->As<ActionListIf>()->SetCondition(0);
		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, true);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		// notify the reaction twice since the event created last update was enqueued
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		TS_ASSERT_THROWS_NOTHING(world->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, true);*/

		delete world;
	}
};