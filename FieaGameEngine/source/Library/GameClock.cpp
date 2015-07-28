#include "pch.h"

namespace Library
{
    GameClock::GameClock()
        : mStartTime(), mCurrentTime(), mLastTime()
    {
        Reset();	
    }

    const GameClock::PointInTime& GameClock::StartTime() const
    {
        return mStartTime;
    }

	const GameClock::PointInTime& GameClock::CurrentTime() const
    {
        return mCurrentTime;
    }

	const GameClock::PointInTime& GameClock::LastTime() const
    {
        return mLastTime;
    }

    void GameClock::Reset()
    {
		mStartTime = std::chrono::high_resolution_clock::now();
        mCurrentTime = mStartTime;
        mLastTime = mCurrentTime;
    }

    void GameClock::UpdateGameTime(GameTime& gameTime)
    {
		mCurrentTime = std::chrono::high_resolution_clock::now();

		gameTime.SetCurrentTime(mCurrentTime);
		gameTime.SetTotalGameTime(std::chrono::duration_cast<GameTime::Milliseconds>(mCurrentTime - mStartTime));
		gameTime.SetElapsedGameTime(std::chrono::duration_cast<GameTime::Milliseconds>(mCurrentTime - mLastTime));

        mLastTime = mCurrentTime;
    }
}