#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Action)

	Action::Action()
	{
		EXTERNAL_ATTRIBUTE(std::string("Name"), Datum::String, 1, &mName);
		Populate();
	}

	const std::string& Action::Name() const
	{
		return mName;
	}

	Entity* Action::GetEntity() const
	{
		Scope* grandparent = GetParent()->GetParent();
		while (!grandparent->Is(std::string("Entity")))
		{
			grandparent = grandparent->GetParent();
			if (grandparent == nullptr)
				return nullptr;
		}
		return grandparent->As<Entity>();
	}

	ActionList* Action::GetContainingAction() const
	{
		if (GetParent()->GetParent()->Is("ActionList"))
			return GetParent()->GetParent()->As<ActionList>();
		return nullptr;
	}

	void Action::SetEntity(Entity* entity, std::uint32_t index)
	{
		entity->Actions()->Adopt(*this, mName, index);
	}

	void Action::SetActionList(ActionList* action, std::uint32_t index)
	{
		action->ContainedActions()->Adopt(*this, mName, index);
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
	}
}