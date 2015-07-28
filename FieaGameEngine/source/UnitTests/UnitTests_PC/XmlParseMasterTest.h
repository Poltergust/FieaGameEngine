#include <cxxtest/TestSuite.h>
#include <thread>
#include <chrono>
#include "XmlParseHelperFoo.h"
#include "XmlParseHelperTable.h"
#include "XmlParseHelperWorld.h"
#include "XmlParseHelperSector.h"
#include "XmlParseHelperEntity.h"
#include "XmlParseHelperAction.h"
#include "EntityFoo.h"

using namespace Library;

class XmlParseMasterTestSuite : public CxxTest::TestSuite
{
public:
	XmlParseMasterTestSuite() : mSharedData(), mMaster(mSharedData), mHelper(), mTestScope(new Scope()), mTableSharedData(mTestScope), mTableMaster(mTableSharedData), mTableHelper(),
								mWorldScope(new Scope()), mWorldSharedData(mWorldScope), mWorldMaster(mWorldSharedData), mWorldHelper(), mSectorHelper(), mEntityHelper(), mActionHelper() {}

	~XmlParseMasterTestSuite()
	{
		delete mTestScope;
		delete mWorldScope;
	}

	void TestXmlParseMasterInstantiation(void) {}

	void TestXmlParseMasterHelperAddAndRemove(void)
	{
		mMaster.AddHelper(mHelper);
		TS_ASSERT_THROWS_NOTHING(mMaster.RemoveHelper(mHelper));
	}

	void TestXmlParseMasterBasicInput1(void)
	{
		mMaster.AddHelper(mHelper);
		
		mSharedData.Reset();
		mMaster.ResetParser();
		mHelper.Initialize();

		std::string input = std::string("<integer>7</integer>");
		mMaster.Parse(input.c_str(), input.length(), true);

		TS_ASSERT_EQUALS(mSharedData.GetIntData(), 7);
		TS_ASSERT_EQUALS(mSharedData.GetStartElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetEndElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetAttributeKey(), std::string());
		TS_ASSERT_EQUALS(mSharedData.GetAttributeValue(), std::string());
		TS_ASSERT_EQUALS(mSharedData.GetNumStartCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetNumEndCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetMaxDepth(), 1);

		mMaster.RemoveHelper(mHelper);
	}

	void TestXmlParseMasterBasicInput2(void)
	{
		mMaster.AddHelper(mHelper);

		mSharedData.Reset();
		mMaster.ResetParser();
		mHelper.Initialize();

		std::string input = std::string("<integer name = \"value\">10</integer>");
		mMaster.Parse(input.c_str(), input.length(), true);

		TS_ASSERT_EQUALS(mSharedData.GetIntData(), 10);
		TS_ASSERT_EQUALS(mSharedData.GetStartElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetEndElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetAttributeKey(), std::string("name"));
		TS_ASSERT_EQUALS(mSharedData.GetAttributeValue(), std::string("value"));
		TS_ASSERT_EQUALS(mSharedData.GetNumStartCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetNumEndCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetMaxDepth(), 1);

		mMaster.RemoveHelper(mHelper);
	}

	void TestXmlParseMasterGetAndSetSharedData(void)
	{
		XmlParseHelperFoo::SharedData otherSharedData;
		mMaster.SetSharedData(&otherSharedData);
		TS_ASSERT_EQUALS(mSharedData.GetXmlParseMaster(), nullptr);
		TS_ASSERT_EQUALS(mMaster.GetSharedData(), &otherSharedData);

		mMaster.AddHelper(mHelper);
		mSharedData.Reset();
		mMaster.ResetParser();
		mHelper.Initialize();

		std::string input = std::string("<integer name = \"value\">10</integer>");
		mMaster.Parse(input.c_str(), input.length(), true);

		TS_ASSERT_EQUALS(otherSharedData.GetIntData(), 10);
		TS_ASSERT_EQUALS(otherSharedData.GetStartElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(otherSharedData.GetEndElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(otherSharedData.GetAttributeKey(), std::string("name"));
		TS_ASSERT_EQUALS(otherSharedData.GetAttributeValue(), std::string("value"));
		TS_ASSERT_EQUALS(otherSharedData.GetNumStartCalls(), 1);
		TS_ASSERT_EQUALS(otherSharedData.GetNumEndCalls(), 1);
		TS_ASSERT_EQUALS(otherSharedData.GetMaxDepth(), 1);

		mMaster.SetSharedData(&mSharedData);
		TS_ASSERT_EQUALS(otherSharedData.GetXmlParseMaster(), nullptr);
		TS_ASSERT_EQUALS(mMaster.GetSharedData(), &mSharedData);

		mMaster.RemoveHelper(mHelper);
	}

	void TestXmlParseMasterClone(void)
	{
		mMaster.AddHelper(mHelper);
		
		XmlParseMaster* masterClone = mMaster.Clone();
		XmlParseHelperFoo::SharedData* cloneData = masterClone->GetSharedData()->As<XmlParseHelperFoo::SharedData>();

		std::string input = std::string("<integer name = \"value\">10</integer>");
		masterClone->Parse(input.c_str(), input.length(), true);

		TS_ASSERT_EQUALS(cloneData->GetIntData(), 10);
		TS_ASSERT_EQUALS(cloneData->GetStartElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(cloneData->GetEndElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(cloneData->GetAttributeKey(), std::string("name"));
		TS_ASSERT_EQUALS(cloneData->GetAttributeValue(), std::string("value"));
		TS_ASSERT_EQUALS(cloneData->GetNumStartCalls(), 1);
		TS_ASSERT_EQUALS(cloneData->GetNumEndCalls(), 1);
		TS_ASSERT_EQUALS(cloneData->GetMaxDepth(), 1);

		mMaster.RemoveHelper(mHelper);
		delete masterClone;
	}

	void TestXmlParseMasterReadFromFile(void)
	{
		mMaster.AddHelper(mHelper);
		mSharedData.Reset();
		mMaster.ResetParser();
		mHelper.Initialize();

		mMaster.ParseFromFile(std::string("Files/TestXML.txt"));

		TS_ASSERT_EQUALS(mSharedData.GetIntData(), 10);
		TS_ASSERT_EQUALS(mSharedData.GetStartElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetEndElementName(), std::string("integer"));
		TS_ASSERT_EQUALS(mSharedData.GetAttributeKey(), std::string("name"));
		TS_ASSERT_EQUALS(mSharedData.GetAttributeValue(), std::string("value"));
		TS_ASSERT_EQUALS(mSharedData.GetNumStartCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetNumEndCalls(), 1);
		TS_ASSERT_EQUALS(mSharedData.GetMaxDepth(), 1);

		TS_ASSERT_EQUALS(mMaster.GetFileName(), "Files/TestXML.txt");

		mMaster.RemoveHelper(mHelper);
	}

	// TESTS FOR ASSIGNMENT 11 START HERE!

	void TestXmlParseMasterWithSimpleScope(void)
	{
		mTableMaster.AddHelper(mTableHelper);
		mTableSharedData.Reset();
		mTableMaster.ResetParser();
		mTableHelper.Initialize();

		std::string input = std::string("<scope><integer>7</integer></scope>");
		mTableMaster.Parse(input.c_str(), input.length(), true);

		Datum* scopeDatum = mTestScope->Find("Table");
		TS_ASSERT(scopeDatum != nullptr);

		Scope* s = scopeDatum->GetTable();
		TS_ASSERT(s != nullptr);

		Datum* integerDatum = s->Find("Integer");
		TS_ASSERT(integerDatum != nullptr);
		TS_ASSERT_EQUALS(integerDatum->GetInteger(), 7);

		TS_ASSERT_EQUALS(mTableSharedData.GetNumStartCalls(), 2);
		TS_ASSERT_EQUALS(mTableSharedData.GetNumEndCalls(), 2);
		TS_ASSERT_EQUALS(mTableSharedData.GetMaxDepth(), 2);

		mTableMaster.RemoveHelper(mTableHelper);
	}

	void TestXmlParseMasterWithSimpleScopeAndNamedAttributes(void)
	{
		mTableMaster.AddHelper(mTableHelper);
		mTableSharedData.Reset();
		mTableMaster.ResetParser();
		mTableHelper.Initialize();

		std::string input = std::string("<scope firstScope = \"\"><float f = \"4\">7.3</float></scope>");
		mTableMaster.Parse(input.c_str(), input.length(), true);

		Datum* scopeDatum = mTestScope->Find("firstScope");
		TS_ASSERT(scopeDatum != nullptr);

		Scope* s = scopeDatum->GetTable();
		TS_ASSERT(s != nullptr);

		Datum* floatDatum = s->Find("f");
		TS_ASSERT(floatDatum != nullptr);
		TS_ASSERT_EQUALS(floatDatum->GetFloat(4), 7.3f);

		TS_ASSERT_EQUALS(mTableSharedData.GetNumStartCalls(), 2);
		TS_ASSERT_EQUALS(mTableSharedData.GetNumEndCalls(), 2);
		TS_ASSERT_EQUALS(mTableSharedData.GetMaxDepth(), 2);

		mTableMaster.RemoveHelper(mTableHelper);
	}

	void TestXmlParseMasterWithNestedScope(void)
	{
		mTableMaster.AddHelper(mTableHelper);
		mTableSharedData.Reset();
		mTableMaster.ResetParser();
		mTableHelper.Initialize();

		std::string input = std::string("<scope firstScope = \"\"><vector v = \"2\">1.0 2.0 3.0 4.0</vector><scope secondScope = \"\"><float f = \"7\">2.8</float></scope></scope>");
		mTableMaster.Parse(input.c_str(), input.length(), true);

		Datum* scopeDatum = mTestScope->Find("firstScope");
		TS_ASSERT(scopeDatum != nullptr);

		Scope* s = scopeDatum->GetTable();
		TS_ASSERT(s != nullptr);

		Datum* vectorDatum = s->Find("v");
		TS_ASSERT(vectorDatum != nullptr);
		TS_ASSERT_EQUALS(vectorDatum->GetVector(2), glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));

		Datum* nestedScopeDatum = s->Find("secondScope");
		TS_ASSERT(nestedScopeDatum != nullptr);

		Scope* s2 = nestedScopeDatum->GetTable();
		TS_ASSERT(s2 != nullptr);

		Datum* nestedFloatDatum = s2->Find("f");
		TS_ASSERT(nestedFloatDatum != nullptr);
		TS_ASSERT_EQUALS(nestedFloatDatum->GetFloat(7), 2.8f);

		TS_ASSERT_EQUALS(mTableSharedData.GetNumStartCalls(), 4);
		TS_ASSERT_EQUALS(mTableSharedData.GetNumEndCalls(), 4);
		TS_ASSERT_EQUALS(mTableSharedData.GetMaxDepth(), 3);

		mTableMaster.RemoveHelper(mTableHelper);
	}

	// TESTS FOR ASSIGNMENT 13 START HERE!

	void TestXmlParseMasterWithWorld(void)
	{
		EntityFoo::EntityFooFactory eFooFactory;

		mWorldMaster.AddHelper(mWorldHelper);
		mWorldMaster.AddHelper(mSectorHelper);
		mWorldMaster.AddHelper(mEntityHelper);

		mWorldSharedData.Reset();
		mWorldMaster.ResetParser();
		mWorldHelper.Initialize();

		std::string input = std::string("<world Pandora = \"\"><sector Alpha = \"\"><entity class = \"EntityFoo\" name = \"eFoo\"></entity></sector></world>");
		mWorldMaster.Parse(input.c_str(), input.length(), true);

		Datum* worldDatum = mWorldScope->Find("Universe");
		TS_ASSERT(worldDatum != nullptr);

		World* w = worldDatum->GetTable()->As<World>();
		TS_ASSERT(w != nullptr);
		TS_ASSERT_EQUALS(w->Name(), std::string("Pandora"));

		Sector* s = w->Sectors()->Find("Alpha")->GetTable()->As<Sector>();
		TS_ASSERT(s != nullptr);

		Entity* e = s->Entities()->Find("eFoo")->GetTable()->As<Entity>();
		TS_ASSERT(e != nullptr);
		TS_ASSERT(e->Is(std::string("EntityFoo")));

		mWorldMaster.RemoveHelper(mEntityHelper);
		mWorldMaster.RemoveHelper(mSectorHelper);
		mWorldMaster.RemoveHelper(mWorldHelper);
	}

	// TESTS FOR ASSIGNMENT 14 START HERE!

	void TestXmlParseMasterWithActions(void)
	{
		EntityFoo::EntityFooFactory eFooFactory;

		mWorldMaster.AddHelper(mWorldHelper);
		mWorldMaster.AddHelper(mSectorHelper);
		mWorldMaster.AddHelper(mEntityHelper);
		mWorldMaster.AddHelper(mActionHelper);
		mWorldMaster.AddHelper(mTableHelper);

		mWorldSharedData.Reset();
		mWorldMaster.ResetParser();
		mWorldHelper.Initialize();

		// Sorry! Will use XML files in the future
		std::string input = std::string("<world Pandora = \"\"><sector Alpha = \"\"><entity class = \"EntityFoo\" name = \"eFoo\"><action class=\"ActionListIf\" name = \"If\"><integer condition = \"0\">1</integer><action class = \"ActionList\" name = \"then\"><action class = \"ActionPrint\" name = \"thenPrint\">YesXml</action></action><action class = \"ActionList\" name = \"else\"><action class = \"ActionPrint\" name = \"elsePrint\">NoXml</action></action></action></entity></sector></world>");
		mWorldMaster.Parse(input.c_str(), input.length(), true);

		Datum* worldDatum = mWorldScope->Find("Universe");
		TS_ASSERT(worldDatum != nullptr);

		World* w = worldDatum->GetTable()->As<World>();
		TS_ASSERT(w != nullptr);
		TS_ASSERT_EQUALS(w->Name(), std::string("Pandora"));

		Sector* s = w->Sectors()->Find("Alpha")->GetTable()->As<Sector>();
		TS_ASSERT(s != nullptr);

		Entity* e = s->Entities()->Find("eFoo")->GetTable()->As<Entity>();
		TS_ASSERT(e != nullptr);
		TS_ASSERT(e->Is(std::string("EntityFoo")));

		Action* a = e->Actions()->Find("If")->GetTable()->As<Action>();
		TS_ASSERT(a != nullptr);
		TS_ASSERT(a->Is(std::string("ActionListIf")));

		ActionPrint* aPrint1 = (*a->As<ActionListIf>()->ThenAction()->As<ActionList>()->ContainedActions())["thenPrint"].GetTable()->As<ActionPrint>();
		ActionPrint* aPrint2 = (*a->As<ActionListIf>()->ElseAction()->As<ActionList>()->ContainedActions())["elsePrint"].GetTable()->As<ActionPrint>();
		TS_ASSERT(aPrint1 != nullptr);
		TS_ASSERT(aPrint2 != nullptr);

		TS_ASSERT_EQUALS(aPrint1->GetEntity(), e);
		TS_ASSERT_EQUALS(aPrint2->GetEntity(), e);
		TS_ASSERT_EQUALS(aPrint1->GetContainingAction(), a->As<ActionListIf>()->ThenAction()->As<ActionList>());
		TS_ASSERT_EQUALS(aPrint2->GetContainingAction(), a->As<ActionListIf>()->ElseAction()->As<ActionList>());

		mWorldMaster.RemoveHelper(mTableHelper);
		mWorldMaster.RemoveHelper(mActionHelper);
		mWorldMaster.RemoveHelper(mEntityHelper);
		mWorldMaster.RemoveHelper(mSectorHelper);
		mWorldMaster.RemoveHelper(mWorldHelper);
	}

	// TESTS FOR ASSIGNMENT 16 START HERE!
	void TestXmlParseMasterWithReactions(void)
	{
		EntityFoo::EntityFooFactory eFooFactory;

		mWorldMaster.AddHelper(mWorldHelper);
		mWorldMaster.AddHelper(mSectorHelper);
		mWorldMaster.AddHelper(mEntityHelper);
		mWorldMaster.AddHelper(mActionHelper);
		mWorldMaster.AddHelper(mTableHelper);

		mWorldSharedData.Reset();
		mWorldMaster.ResetParser();
		mWorldHelper.Initialize();

		// Sorry! Will use XML files in the future
		std::string input = std::string("<world Pandora = \"\"><sector Alpha = \"\"><entity class = \"EntityFoo\" name = \"eFoo\"><action class=\"ReactionAttributed\" name = \"Reaction\"><integer subtype = \"4\">0</integer><action class=\"ActionListIf\" name = \"If\"><integer condition = \"0\">1</integer><action class = \"ActionList\" name = \"then\"><action class = \"ActionPrint\" name = \"thenPrint\">YesReactionXml</action></action><action class = \"ActionList\" name = \"else\"><action class = \"ActionPrint\" name = \"elsePrint\">NoReactionXml</action></action></action></action><action class = \"ActionEvent\" name = \"Event\"><integer subtype = \"0\">0</integer><float delay = \"0\">0.0</float></action></entity></sector></world>");
		mWorldMaster.Parse(input.c_str(), input.length(), true);

		Datum* worldDatum = mWorldScope->Find("Universe");
		TS_ASSERT(worldDatum != nullptr);

		World* w = worldDatum->GetTable()->As<World>();
		TS_ASSERT(w != nullptr);
		TS_ASSERT_EQUALS(w->Name(), std::string("Pandora"));

		Sector* s = w->Sectors()->Find("Alpha")->GetTable()->As<Sector>();
		TS_ASSERT(s != nullptr);

		Entity* e = s->Entities()->Find("eFoo")->GetTable()->As<Entity>();
		TS_ASSERT(e != nullptr);
		TS_ASSERT(e->Is(std::string("EntityFoo")));

		Action* reaction = e->Actions()->Find("Reaction")->GetTable()->As<Action>();
		TS_ASSERT(reaction != nullptr);
		TS_ASSERT(reaction->Is(std::string("ReactionAttributed")));
		TS_ASSERT_EQUALS(reaction->As<ReactionAttributed>()->GetSubtype(4), 0);

		Action* actionEvent = e->Actions()->Find("Event")->GetTable()->As<Action>();
		TS_ASSERT(actionEvent != nullptr);
		TS_ASSERT(actionEvent->Is(std::string("ActionEvent")));
		TS_ASSERT_EQUALS(actionEvent->As<ActionEvent>()->GetSubtype(), 0);

		Action* actionListIf = reaction->As<ActionList>()->ContainedActions()->Find("If")->GetTable()->As<Action>();
		TS_ASSERT(actionListIf != nullptr);
		TS_ASSERT(actionListIf->Is(std::string("ActionListIf")));

		ActionPrint* aPrint1 = (*actionListIf->As<ActionListIf>()->ThenAction()->As<ActionList>()->ContainedActions())["thenPrint"].GetTable()->As<ActionPrint>();
		ActionPrint* aPrint2 = (*actionListIf->As<ActionListIf>()->ElseAction()->As<ActionList>()->ContainedActions())["elsePrint"].GetTable()->As<ActionPrint>();
		TS_ASSERT(aPrint1 != nullptr);
		TS_ASSERT(aPrint2 != nullptr);

		// this tests for immediate notifications due to no delay
		/*TS_ASSERT_THROWS_NOTHING(w->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, true);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);

		Datum* conditionDatum = nullptr;
		TS_ASSERT_THROWS_NOTHING(conditionDatum = actionListIf->As<ActionListIf>()->Find("condition"));
		TS_ASSERT(conditionDatum != nullptr);
		conditionDatum->Set(0, 0);

		TS_ASSERT_THROWS_NOTHING(w->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, true);

		// this tests for delayed notifications due to delay
		actionEvent->As<ActionEvent>()->SetDelay(0.2f);

		// no change from previous state within actionListIf due to delay
		conditionDatum->Set(1, 0);
		TS_ASSERT_THROWS_NOTHING(w->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, false);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, true);

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		// now a change occurs
		TS_ASSERT_THROWS_NOTHING(w->Update());
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredThen, true);
		TS_ASSERT_EQUALS(actionListIf->As<ActionListIf>()->mEnteredElse, false);*/

		mWorldMaster.RemoveHelper(mTableHelper);
		mWorldMaster.RemoveHelper(mActionHelper);
		mWorldMaster.RemoveHelper(mEntityHelper);
		mWorldMaster.RemoveHelper(mSectorHelper);
		mWorldMaster.RemoveHelper(mWorldHelper);
	}

private:
	XmlParseHelperFoo::SharedData mSharedData;
	XmlParseMaster mMaster;
	XmlParseHelperFoo mHelper;

	Scope* mTestScope;
	XmlParseHelperTable::SharedData mTableSharedData;
	XmlParseMaster mTableMaster;
	XmlParseHelperTable mTableHelper;

	Scope* mWorldScope;
	XmlParseHelperTable::SharedData mWorldSharedData;
	XmlParseMaster mWorldMaster;
	XmlParseHelperWorld mWorldHelper;
	XmlParseHelperSector mSectorHelper;
	XmlParseHelperEntity mEntityHelper;
	XmlParseHelperAction mActionHelper;
};