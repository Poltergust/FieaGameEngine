#include <cxxtest/TestSuite.h>
#include <thread>
#include <future>
#include <mutex>
#include "ConcurrentEventSubscriberFoo.h"
#include "GameClock.h"

using namespace Library;

class ConcurrentEventSuite : public CxxTest::TestSuite
{
public:
	void TestConcurrentEventInstantiation(void)
	{
		Event<std::uint32_t> e(5, false);
		EventQueue eQueue;
		GameTime gameTime;
		ConcurrentEventSubscriberFoo eSubscriber(&eQueue, &gameTime);

		TS_ASSERT_EQUALS(eSubscriber.GetNumber(), 0);
		TS_ASSERT_EQUALS(e.Message(), 5);
	}

	void TestConcurrentEventNotify(void)
	{
		Event<std::uint32_t> e(5, false);
		EventQueue eQueue;
		GameClock gameClock;
		GameTime gameTime;

		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		ConcurrentEventSubscriberFoo eSubscriber(&eQueue, &gameTime);

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::Subscribe(eSubscriber));
		TS_ASSERT_THROWS_NOTHING(eQueue.Enqueue(&e, gameTime, 0.0));
		TS_ASSERT_EQUALS(eSubscriber.GetNumber(), 5);

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		TS_ASSERT_THROWS_NOTHING(gameClock.UpdateGameTime(gameTime));
		TS_ASSERT_THROWS_NOTHING(eQueue.Update(gameTime));
		TS_ASSERT_EQUALS(eSubscriber.GetNumber(), 6);

		TS_ASSERT_THROWS_NOTHING(Event<std::uint32_t>::UnsubscribeAll());
	}
};