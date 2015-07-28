#pragma once

#include <chrono>
#include <exception>

namespace Library
{
    class GameTime;

    class GameClock
    {
    public:
		typedef std::chrono::high_resolution_clock::time_point PointInTime;

        GameClock();

        const PointInTime& StartTime() const;
        const PointInTime& CurrentTime() const;
        const PointInTime& LastTime() const;

        void Reset();
        void UpdateGameTime(GameTime& gameTime);

    private:
        GameClock(const GameClock& rhs);
        GameClock& operator=(const GameClock& rhs);

        PointInTime mStartTime;
        PointInTime mCurrentTime;
        PointInTime mLastTime;
    };
}
