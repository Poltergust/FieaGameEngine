#include "pch.h"

namespace Library
{
#pragma region WorldState
	WorldState::WorldState() : mEntity(nullptr), mSector(nullptr), mWorld(nullptr), mAction(nullptr), mGameTime(new GameTime()) {}

	WorldState::~WorldState()
	{
		delete mGameTime;
	}

	void WorldState::SetGameTime(GameTime& gameTime)
	{
		mGameTime = &gameTime;
	}

	GameTime& WorldState::GetGameTime() const
	{
		return *mGameTime;
	}
#pragma endregion
}