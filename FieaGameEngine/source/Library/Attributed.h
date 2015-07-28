#pragma once

#include "Scope.h"

namespace Library
{
	class AttributedFoo;
	/**
	 * A class for attributed objects.
	 */
	class Attributed : public Scope
	{
		/**
		 * AttributedFoo should access Attributed's private members.
		 */
		friend class AttributedFoo;

		RTTI_DECLARATIONS(Attributed, Scope)

	public:

		/**
		 * The constructor.
		 */
		Attributed();

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the attributed object to copy
		 */
		Attributed(const Attributed& rhs);

		/**
		 * The assignment operator. Performs a deep copy.
		 * @param rhs	the attributed object to copy
		 * @return a reference to the newly copied attributed object
		 */
		Attributed& operator=(const Attributed& rhs);

		/**
		 * The destructor. A pure virtual function.
		 */
		virtual ~Attributed() = default;

		/**
		 * Populates this attributed object's scope with prescribed attributes.
		 */
		void Populate();

		/**
		 * Tells whether the attribute of the associated key is a prescribed attribute of this attributed object.
		 * @param key	the key of the attribute to search for
		 * @return true if this key is of a prescribed attribute, false otherwise
		 */
		bool IsPrescribedAttribute(const std::string& key) const;

		/**
		* Tells whether the attribute of the associated key is an auxiliary attribute of this attributed object.
		* @param key	the key of the attribute to search for
		* @return true if this key is of an auxiliary attribute, false otherwise
		*/
		bool IsAuxiliaryAttribute(const std::string& key) const;

		/**
		* Tells whether the attribute of the associated key is an attribute of this attributed object.
		* @param key	the key of the attribute to search for
		* @return true if this key is of an attribute, false otherwise
		*/
		bool IsAttribute(const std::string& key) const;

		/**
		 * Creates an auxiliary attribute and appends it to this attributed object's scope.
		 * @param key	the key of the newly created auxiliary attributed
		 * @throws an exception if the key already refers to a prescribed attribute
		 * @return the datum reference of the newly created attributed
		 */
		Datum& AppendAuxiliaryAttribute(const std::string& key);

		/**
		 * Gets the index of where auxiliary attributes first start within the scope.
		 * @return the index of where auxiliary attributes first start within the scope.
		 */
		std::uint32_t AuxiliaryBegin() const;

	protected:
		/**
		 * A class for signatures (prescribed attributes).
		 */
		class Signature
		{
		public:
			std::string mName;	/**< The name of the signature; used as a key. */
			Datum::DatumType mType; /**< The datum type of the signature. */
			void* mInitialValue; /**< The initial value of the signature (if signature is internal). */
			std::uint32_t mSize; /**< The size of the signature. */
			void* mStorage; /**< Where the signature is contained (if the signature is external). */

			/**
			 * The constructor.
			 */
			Signature();

			/**
			 * The constructor. Takes in parameters.
			 * @param name	the name to give the signature
			 * @param type	the type to give the signature
			 * @param initialValue	the value to give the signature
			 * @param size	the size to give the signature
			 * @param storage	where the signature is contained
			 */
			Signature(const std::string& name, Datum::DatumType type, void* initialValue, std::uint32_t size, void* storage);

			/**
			 * The comparison operator. Compares equality.
			 * @param rhs	the signature to compare to
			 * @return true if the signatures are equal, false otherwise
			 */
			bool operator==(const Signature& rhs) const;

			/**
			 * The comparison operator. Compares non-equality.
			 * @param rhs	the signature to compare to
			 * @return true if the signatures are not equal, false otherwise
			 */
			bool operator!=(const Signature& rhs) const;
		};

	private:
		/**
		 * Unused. Only throws an exception when called.
		 * @param datum	the datum to set a value in
		 * @param valueArray	the passed in array of values
		 * @param index	the index into the value array and the datum
		 * @throws an exception immediately
		 */
		static void SetUnknown(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets an integer value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetInteger(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets a float value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetFloat(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets a vector value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetVector(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets a matrix value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetMatrix(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets a Scope pointer value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetTable(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets a string value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetString(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Sets an RTTI pointer value in the datum at the specified index.
		* @param datum	the datum to set a value in
		* @param valueArray	the passed in array of values
		* @param index	the index into the value array and the datum
		*/
		static void SetPointer(Datum& datum, void* valueArray, std::uint32_t index);

		/**
		* Unused. Only throws an exception when called.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		* @throws an exception immediately
		*/
		static void SetStorageUnknown(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the integer storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageInteger(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the float storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageFloat(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the vector storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageVector(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the matrix storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageMatrix(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the Scope pointer storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageTable(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the string storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStorageString(Datum& datum, void* storageArray, std::uint32_t size);

		/**
		* Sets the datum to store the RTTI pointer storage array.
		* @param datum	the datum to set storage in
		* @param storageArray	the passed in storage array
		* @param size	the size of the storage array
		*/
		static void SetStoragePointer(Datum& datum, void* storageArray, std::uint32_t size);

		typedef void(*SetFunction)(Datum& datum, void* valueArray, std::uint32_t index); /**< A type for holding the set functions. */
		const static SetFunction SetFn[]; /**< The function pointer to hold the set functions. */

		typedef void(*SetStorageFunction)(Datum& datum, void* storageArray, std::uint32_t size); /**< A type for holding the set storage functions. */
		const static SetStorageFunction SetStorageFn[]; /**< The function pointer to hold the set storage functions. */

		std::uint32_t mPopulateCounter; /**< A counter for the populate function, in case we wish to populate more than once. */
		bool mIsPopulated; /**< A boolean telling if the attributed object is populated or not. */
		RTTI* mThisAttributedObject; /**< Pointer to this attributed object. */

	public:
		Vector<Signature> mSignatures; /**< A vector of signatures. */

#define INTERNAL_ATTRIBUTE(name, type, initialValue, size) mSignatures.PushBack(Signature(name, type, initialValue, size, nullptr))

#define EXTERNAL_ATTRIBUTE(name, type, size, storage) mSignatures.PushBack(Signature(name, type, nullptr, size, storage))

	};
}