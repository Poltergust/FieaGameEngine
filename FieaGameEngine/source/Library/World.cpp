#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(World)

#pragma region World
	World::World(const std::string& name) : mActionListFactory(), mActionListIfFactory(), mActionPrintFactory(), mReactionAttributedFactory(), mActionEventFactory(), 
											mName(name), mSectors(nullptr), mWorldState(new WorldState()), mEventQueue(new EventQueue()), mGameClock(new GameClock())
	{
		EXTERNAL_ATTRIBUTE(std::string("Name"), Datum::String, 1, &mName);
		INTERNAL_ATTRIBUTE(std::string("Sectors"), Datum::Table, mSectors, 1);
		Populate();
		mSectors = Find(std::string("Sectors"))->GetTable();
	}

	World::~World()
	{
		delete mWorldState;
		delete mEventQueue;
		delete mGameClock;
	}

	const std::string& World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string& name)
	{
		mName = name;
	}

	Scope* World::Sectors() const
	{
		return mSectors;
	}

	Sector* World::CreateSector(const std::string& sectorName)
	{
		std::uint32_t size = mSectors->Size();
		Sector* newSector = new Sector(sectorName);
		newSector->SetWorld(this, size);
		return newSector;
	}

	void World::Update()
	{
		std::uint32_t size = mSectors->Size();
		mWorldState->mWorld = this;
		mGameClock->UpdateGameTime(mWorldState->GetGameTime());
		mEventQueue->Update(mWorldState->GetGameTime());
		for (std::uint32_t i = 0; i < size; ++i)
		{
			Sector* sectorScope = (*mSectors)[i].GetTable()->As<Sector>();
			if (sectorScope == nullptr)
				throw std::exception("sectorScope is not actually a sector.");

			sectorScope->Update(*mWorldState);
		}
	}

	WorldState* World::GetWorldState() const
	{
		return mWorldState;
	}

	EventQueue* World::GetEventQueue() const
	{
		return mEventQueue;
	}
#pragma endregion
}