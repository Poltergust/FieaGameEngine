#pragma once

#include <chrono>

namespace Library
{
	class GameTime
	{
	public:
		GameTime();

		typedef std::chrono::high_resolution_clock::time_point PointInTime;
		typedef std::chrono::milliseconds Milliseconds;

		const PointInTime& CurrentTime() const;
		void SetCurrentTime(const PointInTime& currentTime);

		const Milliseconds& TotalGameTime() const;
		void SetTotalGameTime(const Milliseconds& totalGameTime);

		const Milliseconds& ElapsedGameTime() const;
		void SetElapsedGameTime(const Milliseconds& elapsedGameTime);

	private:
		PointInTime mCurrentTime;
		Milliseconds mTotalGameTime;
		Milliseconds mElapsedGameTime;
	};
}
