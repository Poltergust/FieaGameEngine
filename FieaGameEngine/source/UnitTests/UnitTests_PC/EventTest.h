#include <cxxtest/TestSuite.h>
#include <thread>
#include "EventSubscriberFoo.h"
#include "GameClock.h"

using namespace Library;

class EventTestSuite : public CxxTest::TestSuite
{
public:
	void TestEventInstantiation(void)
	{
		EventSubscriberFoo eSubscriberFoo;
		std::uint32_t i = 5;
		Event<std::uint32_t> e(i, false);
		EventQueue eQueue;
		GameTime gameTime;

		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 0);
		TS_ASSERT_EQUALS(e.Message(), 5);
	}

	void TestEventNotifying(void)
	{
		EventSubscriberFoo eSubscriberFoo;
		std::uint32_t i = 5;
		Event<std::uint32_t> e(i, false);
		EventQueue eQueue;
		GameTime gameTime;

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::Subscribe(eSubscriberFoo));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(&e, gameTime, 0.0));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 5);
		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::UnsubscribeAll());
	}

	void TestEventDeletion(void)
	{
		EventSubscriberFoo eSubscriberFoo;
		std::uint32_t i = 5;
		Event<std::uint32_t>* e = new Event<std::uint32_t>(i, true);
		EventQueue eQueue;
		GameTime gameTime;

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::Subscribe(eSubscriberFoo));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(e, gameTime, 0.0));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 5);
		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::UnsubscribeAll());
	}

	void TestEventDelay(void)
	{
		EventSubscriberFoo eSubscriberFoo;
		std::uint32_t i = 5;
		Event<std::uint32_t> e(i, false);
		EventQueue eQueue;
		GameClock gameClock;
		GameTime gameTime;

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::Subscribe(eSubscriberFoo));
		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(&e, gameTime, 0.1f));
		TS_ASSERT_THROWS_NOTHING(eQueue.Update(gameTime));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 0);

		TS_ASSERT_EQUALS(e.TimeEnqueued().CurrentTime(), gameTime.CurrentTime());
		TS_ASSERT_EQUALS(e.Delay(), 0.1f);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Update(gameTime));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 5);
		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::UnsubscribeAll());
	}

	void TestEventQueueing(void)
	{
		EventSubscriberFoo eSubscriberFoo;
		std::uint32_t i1 = 5;
		std::uint32_t i2 = 10;
		Event<std::uint32_t> e1(i1, false);
		Event<std::uint32_t> e2(i2, false);
		EventQueue eQueue;
		GameClock gameClock;
		GameTime gameTime;

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::Subscribe(eSubscriberFoo));
		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(&e1, gameTime, 0.1f));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(&e2, gameTime, 0.2f));
		TS_ASSERT_EQUALS(eQueue.Count(), 2);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Update(gameTime));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 5);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Update(gameTime));
		TS_ASSERT_EQUALS(eSubscriberFoo.GetNumber(), 10);

		TS_ASSERT(eQueue.IsEmpty());
		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::UnsubscribeAll());
	}
};