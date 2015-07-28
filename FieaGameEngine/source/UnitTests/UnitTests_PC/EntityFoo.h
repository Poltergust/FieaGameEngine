#pragma once

#include "Entity.h"
#include "Factory.h"

namespace Library
{
	class EntityFoo : public Entity
	{
		RTTI_DECLARATIONS(EntityFoo, Entity)

	public:
		explicit EntityFoo(std::uint32_t i = 50);
		EntityFoo(const EntityFoo& rhs) = delete;
		EntityFoo& operator=(const EntityFoo& rhs) = delete;
		virtual ~EntityFoo() = default;

		std::uint32_t GetInt() const;
		void SetInt(std::uint32_t i);

	private:
		std::uint32_t mEntityInt;

	public:
		ConcreteFactory(EntityFoo, RTTI)
	};
}