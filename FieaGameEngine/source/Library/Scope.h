#pragma once

#include "RTTI.h"
#include "Datum.h"
#include "HashMap.h"

namespace Library
{
	class Attributed;
	/**
	 * A class for scopes (or tables).
	 */
	class Scope : public RTTI
	{
		friend class Attributed;

		RTTI_DECLARATIONS(Scope, RTTI)

	protected:
		typedef Vector<std::pair<std::string, Datum>*>::Iterator Iterator;

	public:
		/**
		 * The constructor. Takes in a default size of 1.
		 * @param size	the size of the scope, defaults to 10
		 */
		explicit Scope(std::uint32_t size = 10);

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the scope to copy
		 */
		Scope(const Scope& rhs);

		/**
		 * The assignment operator. Performs a deep copy.
		 * @param rhs	the scope to copy
		 * @throws an assert failure if the scope is contained in an external datum
		 * @return a reference to the newly copied scope
		 */
		Scope& operator=(const Scope& rhs);

		/**
		 * The destructor.
		 */
		virtual ~Scope();

		/**
		 * The index operator. Takes in a key argument to find a datum within the scope, or adds an entry if none is found.
		 * @param key	the key argument that will be searched for
		 * @return a reference to the found datum, or a reference to the newly created Datum if none is found
		 */
		Datum& operator[](const std::string& key);

		/**
		 * The index operator. Takes in an index to find a datum within the scope.
		 * @param index	the index into the scope
		 * @throws an exception if the index is too large
		 * @return a reference to the found datum
		 */
		Datum& operator[](std::uint32_t index) const;

		/**
		 * The comparison operator. Tests for equality.
		 * @param rhs	the scope to compare to
		 * @return true if the scopes are equivalent, false otherwise
		 */
		bool operator==(const Scope& rhs) const;

		/**
		* The comparison operator. Tests for non-equality.
		* @param rhs	the scope to compare to
		* @return true if the scopes are not equivalent, false otherwise
		*/
		bool operator!=(const Scope& rhs) const;

		/**
		 * Finds a datum within the scope based on the given key argument.
		 * @param key	the key argument that will be searched for
		 * @return a pointer to the found datum, or nullptr if none is found
		 */
		Datum* Find(const std::string& key) const;

		/**
		* Finds a datum within the scope and all of its ancestors based on the given key argument.
		* @param key	the key argument that will be searched for
		* @param scope	an optional output variable that will store which scope the datum was found in
		* @return a pointer to the found datum, or nullptr if none is found
		*/
		Datum* Search(const std::string& key, Scope** scope = nullptr) const;

		/**
		 * Creates a new entry within the scope, or returns a datum if the provided key was already present within it.
		 * @param key	the key argument that will be searched for
		 * @throws an exception if the key is an empty string
		 * @return a reference to the newly created datum, or a reference to a found datum if the key was already present
		 */
		Datum& Append(const std::string& key);

		/**
		 * Creates a new scope within this scope.
		 * @param key	the name of the newly created scope
		 * @throws an exception if the key is an empty string
		 * @throws an exception if a found key refers to a datum not of DatumType::Table
		 * @throws an exception if a found key refers to an external datum
		 * @return a reference to the newly created scope
		 */
		Scope& AppendScope(const std::string& key);

		/**
		 * Makes this scope a parent of the given scope.
		 * @param child	the reference to the child scope
		 * @param key	the name of the datum to contain the child scope
		 * @param index	optional parameter for determining what index to insert the scope into if a datum is found
		 * @throws an exception if the key is an empty string
		 * @throws an exception if a found key refers to a datum not of DatumType::Table
		 * @throws an exception if a found key refers to an external datum
		 */
		void Adopt(Scope& child, const std::string& key, std::uint32_t index = UINT32_MAX);

		/**
		 * Orphans this scope from its parent (if it has one) and notifies the parent that it lost a child.
		 * @throws an assert failure if the child scope was not found in the parent scope
		 */
		void Orphan();

		/**
		 * Gets the parent of the this scope.
		 * @return a pointer to the parent of this scope
		 */
		Scope* GetParent() const;

		/**
		 * Finds the name of the given scope and puts it into the output variable.
		 * @param scope	the scope to find the name of
		 * @param name	the output variable that will store the found name (if it was found)
		 * @return true if the scope was found, false otherwise
		 */
		bool FindName(const Scope* scope, std::string& name) const;

		/**
		 * Returns an iterator to the beginning of the order vector.
		 * @return an iterator to the beginning of the order vector
		 */
		Iterator begin() const;

		/**
		 * Returns an iterator to one past the end of the order vector.
		 * @return an iterator to one past the end of the order vector
		 */
		Iterator end() const;
		
		/**
		 * Returns the size of the scope.
		 * @return the number of entries within the table
		 */
		std::uint32_t Size() const;

		/**
		 * Deallocates all associated memory to this scope.
		 */
		void Clear();

	private:
		HashMap<std::string, Datum> mTable; /**< The table for the entries within the scope. */
		Vector<std::pair<std::string, Datum>*> mOrder; /**< Another version of the tables that orders the entries based on when they are created. */
		Scope* mParent; /**< The parent to this scope (if applicable). */
	};
}