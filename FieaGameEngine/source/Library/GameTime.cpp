#include "pch.h"

namespace Library
{
	GameTime::GameTime()
		: mCurrentTime(), mTotalGameTime(), mElapsedGameTime()
	{
	}

	const GameTime::PointInTime& GameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::SetCurrentTime(const GameTime::PointInTime& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const GameTime::Milliseconds& GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const GameTime::Milliseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const GameTime::Milliseconds& GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const GameTime::Milliseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}