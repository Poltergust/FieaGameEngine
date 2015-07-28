#pragma once

#include <cassert>
#include "HashMap.h"

namespace Library
{
	/**
	 * An abstract class for factories.
	 */
	template <typename AbstractProductType>
	class Factory
	{
	public:
		/**
		 * The default constructor.
		 */
		Factory() = default;

		/**
		 * The deleted copy constructor.
		 */
		Factory(const Factory& rhs) = delete;

		/**
		 * The deleted assignment operator.
		 */
		Factory& operator=(const Factory& rhs) = delete;

		/**
		 * The default virtual destructor.
		 */
		virtual ~Factory() = default;

		typedef typename HashMap<std::string, Factory<AbstractProductType>*>::Iterator Iterator; /**< A type definition for the HashMap iterator. */

		/**
		 * Pure virtual function for getting the class name of the concrete factory.
		 * @return the class name of the concrete factory
		 */
		virtual std::string GetClassName() const = 0;

	private:

		/**
		 * A pure virtual function for creating an instance of the type of the concrete factory.
		 * @return a pointer to the created instance of the type
		 */
		virtual AbstractProductType* Create() const = 0;

	public:
		/**
		 * Finds the factory within the factory table.
		 * @param strClassName	the name of the factory class to find
		 * @return a pointer to the found factory; if none is found, returns nullptr
		 */
		static Factory<AbstractProductType>* Find(const std::string& strClassName);

		/**
		 * Creates an instance of the specified type.
		 * @param strClassName	the name of the factory class to create an instance out of
		 * @return a pointer to the created instnace of the type
		 */
		static AbstractProductType* Create(const std::string& strClassName);

		/**
		 * Returns an iterator to the beginning of the factory table.
		 * @return an iterator to the beginning of the factory table.
		 */
		static Iterator begin();

		/**
		 * Returns an iterator to one past the end of the factory table.
		 * @return an iterator to one past the end of the factory table.
		 */
		static Iterator end();

	protected:
		/**
		 * Adds a factory class to the factory table.
		 * @param pFactory the factory class to add
		 */
		static void Add(Factory<AbstractProductType>* pFactory);

		/**
		 * Removes a factory class from the factory table.
		 * @param pFactory the factory class to remove
		 */
		static void Remove(Factory<AbstractProductType>* pFactory);

	private:
		static HashMap<std::string, Factory<AbstractProductType>*> sFactoryTable; /**< The static factory table. */

	public:
	#define ConcreteFactory(ConcreteProductType, AbstractProductType)								\
		class ConcreteProductType ##Factory : public Factory<AbstractProductType>					\
		{																							\
		public:																						\
			ConcreteProductType ##Factory() { Add(this); }											\
			~ConcreteProductType ##Factory() { Remove(this); }										\
			virtual std::string GetClassName() const override										\
			{																						\
				return #ConcreteProductType;														\
			}																						\
			virtual AbstractProductType* Create() const	override									\
			{																						\
				AbstractProductType* product = new ConcreteProductType();							\
				return product;																		\
			}																						\
		};
	};

	/**
	 * Instantiation of the static factory table.
	 */
	template <typename AbstractProductType>
	HashMap<std::string, Factory<AbstractProductType>*> Factory<AbstractProductType>::sFactoryTable;
}

#include "Factory.inl"