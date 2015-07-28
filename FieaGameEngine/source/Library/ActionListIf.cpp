#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionListIf)

	ActionListIf::ActionListIf() : mEnteredThen(false), mEnteredElse(false), mConditionValue(0), mThenAction(nullptr), mElseAction(nullptr)
	{
		EXTERNAL_ATTRIBUTE(std::string("condition"), Datum::Integer, 1, &mConditionValue);
		INTERNAL_ATTRIBUTE(std::string("then"), Datum::Table, mThenAction, 1);
		INTERNAL_ATTRIBUTE(std::string("else"), Datum::Table, mElseAction, 1);
		Populate();
		mThenAction = Find(std::string("then"))->GetTable();
		mElseAction = Find(std::string("else"))->GetTable();
	}

	int ActionListIf::Condition() const
	{
		return mConditionValue;
	}

	void ActionListIf::SetCondition(int condition)
	{
		mConditionValue = condition;
	}

	Scope* ActionListIf::ThenAction() const
	{
		return mThenAction;
	}

	Action* ActionListIf::CreateThenAction(const std::string& className, const std::string& instanceName)
	{
		mThenAction = CreateActionForList(className, instanceName);
		return mThenAction->As<Action>();
	}

	Scope* ActionListIf::ElseAction() const
	{
		return mElseAction;
	}

	Action* ActionListIf::CreateElseAction(const std::string& className, const std::string& instanceName)
	{
		mElseAction = CreateActionForList(className, instanceName);
		return mElseAction->As<Action>();
	}

	void ActionListIf::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		if (mThenAction->Size() == 0)
			throw std::exception("Must have a \"then\" clause.");

		if (mConditionValue)
		{
			mEnteredThen = true;
			mEnteredElse = false;
			mThenAction->As<Action>()->Update(worldState);
		}
		else
		{
			mEnteredThen = false;
			if (mElseAction->Size() != 0)
			{
				mEnteredElse = true;
				mElseAction->As<Action>()->Update(worldState);
			}
		}
	}
}