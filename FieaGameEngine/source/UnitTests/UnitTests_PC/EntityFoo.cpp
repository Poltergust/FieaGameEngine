#include "pch.h"
#include "EntityFoo.h"

namespace Library
{
	RTTI_DEFINITIONS(EntityFoo)

	EntityFoo::EntityFoo(std::uint32_t i) : mEntityInt(i) {}

	std::uint32_t EntityFoo::GetInt() const
	{
		return mEntityInt;
	}

	void EntityFoo::SetInt(std::uint32_t i)
	{
		mEntityInt = i;
	}
}