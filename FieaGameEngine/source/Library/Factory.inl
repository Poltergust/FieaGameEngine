#include "Factory.h"

namespace Library
{
#pragma region Factory
	template <typename AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& strClassName)
	{
		HashMap<std::string, Factory<AbstractProductT>*>::Iterator iterator = sFactoryTable.Find(strClassName);
		if (iterator == sFactoryTable.end())
			return nullptr;
		return iterator->second;
	}

	template <typename AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::Create(const std::string& strClassName)
	{
		Factory<AbstractProductT>* factory = Find(strClassName);
		if (factory == nullptr)
			return nullptr;
		return factory->Create();
	}

	template <typename AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::begin()
	{
		return sFactoryTable.begin();
	}

	template <typename AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::end()
	{
		return sFactoryTable.end();
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory<AbstractProductT>* pFactory)
	{
		if (pFactory != nullptr)
		{
			std::pair<std::string, Factory<AbstractProductT>*> pair(pFactory->GetClassName(), pFactory);
			sFactoryTable.Insert(pair);
		}
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::Remove(Factory<AbstractProductT>* pFactory)
	{
		if (pFactory != nullptr)
			sFactoryTable.Remove(pFactory->GetClassName());
	}
#pragma endregion
}