#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Sector)

#pragma region Sector
	Sector::Sector(const std::string& name) : mName(name), mEntities(nullptr)
	{
		EXTERNAL_ATTRIBUTE(std::string("Name"), Datum::String, 1, &mName);
		INTERNAL_ATTRIBUTE(std::string("Entities"), Datum::Table, mEntities, 1);
		Populate();
		mEntities = Find(std::string("Entities"))->GetTable();
	}

	const std::string& Sector::Name() const
	{
		return mName;
	}

	Scope* Sector::Entities() const
	{
		return mEntities;
	}

	Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
	{
		Entity* newEntity = Factory<RTTI>::Create(className)->As<Entity>();
		if (newEntity == nullptr)
			throw std::exception("Could not create entity.");

		std::uint32_t size = mEntities->Size();
		newEntity->mName = instanceName;
		newEntity->SetSector(this, size);
		return newEntity;
	}

	World* Sector::GetWorld() const
	{
		return GetParent()->GetParent()->As<World>();
	}

	void Sector::SetWorld(World* world, std::uint32_t index)
	{
		world->Sectors()->Adopt(*this, mName, index);
	}

	void Sector::Update(WorldState& worldState)
	{
		std::uint32_t size = mEntities->Size();
		worldState.mSector = this;
		for (std::uint32_t i = 0; i < size; ++i)
		{
			Entity* entityScope = (*mEntities)[i].GetTable()->As<Entity>();
			if (entityScope == nullptr)
				throw std::exception("entityScope is not actually an entity.");

			entityScope->Update(worldState);
		}
	}
#pragma endregion
}