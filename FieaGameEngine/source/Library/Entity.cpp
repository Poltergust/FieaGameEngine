#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Entity)

#pragma region Entity
	Entity::Entity() : mName(std::string()), mActions(nullptr)
	{
		EXTERNAL_ATTRIBUTE(std::string("Name"), Datum::String, 1, &mName);
		INTERNAL_ATTRIBUTE(std::string("Actions"), Datum::Table, mActions, 1);
		Populate();
		mActions = Find(std::string("Actions"))->GetTable();
	}

	const std::string& Entity::Name() const
	{
		return mName;
	}

	Scope* Entity::Actions() const
	{
		return mActions;
	}

	Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* newAction = Factory<Action>::Create(className)->As<Action>();
		if (newAction == nullptr)
			throw std::exception("Could not create action.");

		std::uint32_t size = mActions->Size();
		newAction->mName = instanceName;
		newAction->SetEntity(this, size);
		return newAction;
	}

	Sector* Entity::GetSector() const
	{
		return GetParent()->GetParent()->As<Sector>();
	}

	void Entity::SetSector(Sector* sector, std::uint32_t index)
	{
		sector->Entities()->Adopt(*this, mName, index);
	}

	void Entity::Update(WorldState& worldState)
	{
		std::uint32_t size = mActions->Size();
		worldState.mEntity = this;
		for (std::uint32_t i = 0; i < size; ++i)
		{
			Action* actionScope = (*mActions)[i].GetTable()->As<Action>();
			if (actionScope == nullptr)
				throw std::exception("actionScope is not actually an action.");
			else if (actionScope->Is("Reaction"))
				continue;

			actionScope->Update(worldState);
		}
	}
#pragma endregion
}