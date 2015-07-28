#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList() : mContainedActions(nullptr)
	{
		INTERNAL_ATTRIBUTE(std::string("ContainedActions"), Datum::Table, mContainedActions, 1);
		Populate();
		mContainedActions = Find(std::string("ContainedActions"))->GetTable();
	}

	Scope* ActionList::ContainedActions() const
	{
		return mContainedActions;
	}

	Action* ActionList::CreateActionForList(const std::string& className, const std::string& instanceName)
	{
		Action* newAction = Factory<Action>::Create(className)->As<Action>();
		if (newAction == nullptr)
			throw std::exception("Could not create action.");

		std::uint32_t size = mContainedActions->Size();
		newAction->SetName(instanceName);
		newAction->SetActionList(this, size);
		return newAction;
	}

	void ActionList::Update(WorldState& worldState)
	{
		worldState.mAction = this;
		for (std::uint32_t i = 0; i < mContainedActions->Size(); ++i)
		{
			Action* actionScope = (*mContainedActions)[i].GetTable()->As<Action>();
			if (actionScope == nullptr)
				throw std::exception("actionScope is not actually an action.");
			else if (actionScope->Is("Reaction"))
				continue;

			actionScope->Update(worldState);
		}
	}
}