#pragma once

#include <glm/glm.hpp>

namespace Library
{
	class RTTI;
	class Scope;

	/**
	 * A class for datums.
	 */
	class Datum
	{
	public:
		/**
		 * Enumerations for datum types.
		 */
		enum DatumType { Unknown, Integer, Float, Vector, Matrix, Table, String, Pointer };

		/**
		 * A union for all the possible values the datum can hold.
		 */
		union DatumValues
		{
			int*			iPtr;  /**< Integer datum pointer. */
			float*			fPtr;  /**< Float datum pointer. */
			glm::vec4*		vPtr;  /**< Vector datum pointer. */
			glm::mat4*		mPtr;  /**< Matrix datum pointer. */
			Scope**			tPtr;  /**< Table pointer datum pointer. */
			std::string*	sPtr;  /**< String datum pointer. */
			RTTI**			rPtr;  /**< RTTI pointer datum pointer. */

			/**
			 * The default constructor for the union. Sets all pointers to null.
			 */
			DatumValues() : iPtr(nullptr) {}
		};

		/**
		 * The default constructor. Defaults the type to Unknown and the size and capacity to 0.
		 */
		explicit Datum(DatumType type = DatumType::Unknown, std::uint32_t size = 0);

		/**
		 * The copy constructor. Performs a deep copy.
		 * @param rhs	the datum to copy
		 */
		Datum(const Datum& rhs);

		/**
		 * The destructor.
		 */
		~Datum();

		/**
		 * The assignment operator. Performs a deep copy if the right-hand datum is internal, but performs a shallow copy otherwise.
		 * @param rhs	the datum to copy
		 * @return the newly copied datum
		 */
		Datum& operator=(const Datum& rhs);

		/**
		 * Scalar assignment operator for ints. Performs a deep copy.
		 * @param rhs	the integer to copy
		 * @throws an exception if the size of the datum is above 1
		 * @return the newly copied datum
		 */
		Datum& operator=(const int& rhs);

		/**
		* Scalar assignment operator for floats. Performs a deep copy.
		* @param rhs	the float to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(const float& rhs);
		
		/**
		* Scalar assignment operator for vectors. Performs a deep copy.
		* @param rhs	the vector to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(const glm::vec4& rhs);
		
		/**
		* Scalar assignment operator for matrices. Performs a deep copy.
		* @param rhs	the matrix to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(const glm::mat4& rhs);
		
		/**
		* Scalar assignment operator for Scope pointers. Performs a deep copy.
		* @param rhs	the pointer to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(Scope* rhs);

		/**
		* Scalar assignment operator for strings. Performs a deep copy.
		* @param rhs	the string to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(const std::string& rhs);
		
		/**
		* Scalar assignment operator for RTTI pointers. Performs a deep copy.
		* @param rhs	the pointer to copy
		* @throws an exception if the size of the datum is above 1
		* @return the newly copied datum
		*/
		Datum& operator=(RTTI* rhs);

		/**
		* Unused. Only throws an exception when called.
		* @param rhs	the datum to copy
		* @throws an exception immediately
		*/
		void AssignUnknown(const Datum& rhs);

		/**
		 * Assigns ints to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		 * @param rhs	the datum to copy
		 * @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		 */
		void AssignIntegers(const Datum& rhs);

		/**
		* Assigns floats to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignFloats(const Datum& rhs);
		
		/**
		* Assigns vectors to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignVectors(const Datum& rhs);
		
		/**
		* Assigns matrices to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignMatrices(const Datum& rhs);
		
		/**
		* Assigns tables to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignTables(const Datum& rhs);
		
		/**
		* Assigns strings to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignStrings(const Datum& rhs);
		
		/**
		* Assigns RTTI pointers to the datum. Can be a deep copy or shallow copy if rhs is internal or external, respectively.
		* @param rhs	the datum to copy
		* @throws an exception if the sizes of both datums is not equal when the left-hand datum is external and the right-hand datum is internal
		*/
		void AssignPointers(const Datum& rhs);

		/**
		* Unused. Only throws an exception when called.
		* @param size	the amount to allocate
		* @throws an exception immediately
		*/
		void AllocUnknown(std::uint32_t size);

		/**
		 * Allocates memory for the int datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		 * @param size	the amount to allocate
		 */
		void AllocIntegers(std::uint32_t size);

		/**
		* Allocates memory for the float datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocFloats(std::uint32_t size);

		/**
		* Allocates memory for the vector datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocVectors(std::uint32_t size);

		/**
		* Allocates memory for the matrix datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocMatrices(std::uint32_t size);

		/**
		* Allocates memory for the table datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocTables(std::uint32_t size);

		/**
		* Allocates memory for the string datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocStrings(std::uint32_t size);

		/**
		* Allocates memory for the RTTI pointer datum (if necessary). If the datum is already allocated, it then gets reallocated to the given size.
		* @param size	the amount to allocate
		*/
		void AllocPointers(std::uint32_t size);

		/**
		 * The index operator. Used for dereferencing Scopes.
		 * @param index	the index in the datum to dereference
		 * @return the dereferenced scope at the specified index
		 */
		Scope& operator[](std::uint32_t index);

		/**
		 * The comparison operator. Tests if the values of two datums are equal.
		 * @param rhs	the datum to be compared to
		 * @throws an exception if the two datums are not of the same type
		 * @return true if the datums have the same size and the same values, false otherwise
		 */
		bool operator==(const Datum& rhs) const;

		/**
		 * Scalar comparison operator for ints.
		 * @param rhs	the int to be compared to
		 * @throws an exception if the datum is not of type int
		 * @throws an exception if the datum does not have a size of 1
		 * @return true if the datum matches the given int, false otherwise
		 */
		bool operator==(const int& rhs) const;

		/**
		* Scalar comparison operator for floats.
		* @param rhs	the float to be compared to
		* @throws an exception if the datum is not of type float
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given float, false otherwise
		*/
		bool operator==(const float& rhs) const;

		/**
		* Scalar comparison operator for vectors.
		* @param rhs	the vector to be compared to
		* @throws an exception if the datum is not of type glm::vec4
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given vector, false otherwise
		*/
		bool operator==(const glm::vec4& rhs) const;

		/**
		* Scalar comparison operator for matrices.
		* @param rhs	the matrix to be compared to
		* @throws an exception if the datum is not of type glm::mat4
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given matrix, false otherwise
		*/
		bool operator==(const glm::mat4& rhs) const;

		/**
		* Scalar comparison operator for table pointers.
		* @param rhs	the pointer to be compared to
		* @throws an exception if the datum is not of type table pointer
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given table pointer, false otherwise
		*/
		bool operator==(const Scope* rhs) const;

		/**
		* Scalar comparison operator for strings.
		* @param rhs	the string to be compared to
		* @throws an exception if the datum is not of type std::string
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given string, false otherwise
		*/
		bool operator==(const std::string& rhs) const;

		/**
		* Scalar comparison operator for RTTI pointers.
		* @param rhs	the pointer to be compared to
		* @throws an exception if the datum is not of type RTTI pointer
		* @throws an exception if the datum does not have a size of 1
		* @return true if the datum matches the given RTTI pointer, false otherwise
		*/
		bool operator==(const RTTI* rhs) const;

		/**
		* The comparison operator. Tests if the values of two datums are non-equal.
		* @param rhs	the datum to be compared to
		* @throws an exception if the two datums are not of the same type
		* @return false if the datums have the same size and the same values, true otherwise
		*/
		bool operator!=(const Datum& rhs) const;

		/**
		* Scalar comparison operator for ints. Compares non-equality.
		* @param rhs	the int to be compared to
		* @throws an exception if the datum is not of type int
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given int, true otherwise
		*/
		bool operator!=(const int& rhs) const;

		/**
		* Scalar comparison operator for floats. Compares non-equality.
		* @param rhs	the float to be compared to
		* @throws an exception if the datum is not of type float
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given float, true otherwise
		*/
		bool operator!=(const float& rhs) const;

		/**
		* Scalar comparison operator for vectors. Compares non-equality.
		* @param rhs	the vector to be compared to
		* @throws an exception if the datum is not of type glm::vec4
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given vector, true otherwise
		*/
		bool operator!=(const glm::vec4& rhs) const;

		/**
		* Scalar comparison operator for matricess. Compares non-equality.
		* @param rhs	the matrix to be compared to
		* @throws an exception if the datum is not of type glm::mat4
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given matrix, true otherwise
		*/
		bool operator!=(const glm::mat4& rhs) const;

		/**
		* Scalar comparison operator for table pointers. Compares non-equality.
		* @param rhs	the pointer to be compared to
		* @throws an exception if the datum is not of type table pointer
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given table pointer, true otherwise
		*/
		bool operator!=(const Scope* rhs) const;

		/**
		* Scalar comparison operator for strings. Compares non-equality.
		* @param rhs	the string to be compared to
		* @throws an exception if the datum is not of type std::string
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given string, true otherwise
		*/
		bool operator!=(const std::string& rhs) const;

		/**
		* Scalar comparison operator for RTTI pointers. Compares non-equality.
		* @param rhs	the pointer to be compared to
		* @throws an exception if the datum is not of type RTTI pointer
		* @throws an exception if the datum does not have a size of 1
		* @return false if the datum matches the given RTTI pointer, true otherwise
		*/
		bool operator!=(const RTTI* rhs) const;

		/** 
		 * Unused. Only throws an exception when called.
		 * @param rhs	the datum to compare to
		 * @throws an exception immediately
		 */
		bool CompareUnknown(const Datum& rhs) const;

		/**
		 * Compares two int datums for equality.
		 * @param rhs	the datum to compare to
		 * @return true if the datums are equal, false otherwise
		 */
		bool CompareIntegers(const Datum& rhs) const;

		/**
		* Compares two float datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool CompareFloats(const Datum& rhs) const;

		/**
		* Compares two vector datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool CompareVectors(const Datum& rhs) const;

		/**
		* Compares two matrix datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool CompareMatrices(const Datum& rhs) const;

		/**
		* Compares two table datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool CompareTables(const Datum& rhs) const;

		/**
		* Compares two string datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool CompareStrings(const Datum& rhs) const;

		/**
		* Compares two RTTI pointer datums for equality.
		* @param rhs	the datum to compare to
		* @return true if the datums are equal, false otherwise
		*/
		bool ComparePointers(const Datum& rhs) const;

		/**
		 * Gets the current type of the datum.
		 * @return the type of the datum
		 */
		DatumType GetType() const;

		/**
		 * Gets whether the datum is internal or external.
		 * @return true if the datum is external, false if its internal
		 */
		bool IsExternal() const;

		/**
		 * Sets the type of the datum.
		 * @param dType	the type to set the datum to
		 * @throws an exception if the type had already been set to something other than Unknown and dType is not the current type
		 */
		void SetType(DatumType dType);

		/**
		 * Gets the current size of the datum.
		 * @return the size of the datum
		 */
		std::uint32_t Size() const;

		/**
		 * Sets the size of the datum. Allocates memory if needed.
		 * @param size	the size to set the datum to
		 * @throws an exception if the datum has external storage
		 */
		void SetSize(std::uint32_t size);

		/**
		 * Deallocates the datum and clears it of its values.
		 */
		void Clear();

		/**
		 * Unused. Only throws an exception if called.
		 * @throws an exception immediately
		 */
	    void ClearUnknown();

		/**
		 * Deallocates the int datum.
		 */
		void ClearIntegers();

		/**
		 * Deallocates the float datum.
		 */
		void ClearFloats();

		/**
		 * Deallocates the vector datum.
		 */
		void ClearVectors();

		/**
		 * Deallocates the matrix datum.
		 */
		void ClearMatrices();

		/**
		 * Deallocates the string datum.
		 */
		void ClearStrings();
		
		/**
		 * Deallocates the pointer datum.
		 */
		void ClearPointers();

		/**
		 * Sets the datum to store data of an int array. Changes type if necessary.
		 * @param intArray	the int array to store
		 * @param size	the size of the int array
		 * @throws an exception if the incoming array is not at least of size 1
		 */
		void SetStorage(int* intArray, std::uint32_t size);

		/**
		* Sets the datum to store data of a float array. Changes type if necessary.
		* @param floatArray	the float array to store
		* @param size	the size of the float array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(float* floatArray, std::uint32_t size);

		/**
		* Sets the datum to store data of a vector array. Changes type if necessary.
		* @param vectorArray	the vector array to store
		* @param size	the size of the vector array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(glm::vec4* vectorArray, std::uint32_t size);

		/**
		* Sets the datum to store data of a matrix array. Changes type if necessary.
		* @param matrixArray	the matrix array to store
		* @param size	the size of the matrix array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(glm::mat4* matrixArray, std::uint32_t size);

		/**
		* Sets the datum to store data of a table array. Changes type if necessary.
		* @param tableArray	the table array to store
		* @param size	the size of the table array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(Scope** tableArray, std::uint32_t size);

		/**
		* Sets the datum to store data of a string array. Changes type if necessary.
		* @param stringArray	the string array to store
		* @param size	the size of the string array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(std::string* stringArray, std::uint32_t size);

		/**
		* Sets the datum to store data of an RTTI pointer array. Changes type if necessary.
		* @param pointerArray	the pointer array to store
		* @param size	the size of the pointer array
		* @throws an exception if the incoming array is not at least of size 1
		*/
		void SetStorage(RTTI** pointerArray, std::uint32_t size);
		
		/**
		 * Sets a value of the int datum at the given index.
		 * @param value	the value to set
		 * @param index	the index to set the value at
		 * @throws an exception if the datum is not of type int and cannot be changed to be so
		 */
		void Set(const int& value, std::uint32_t index = 0);

		/**
		* Sets a value of the float datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type float and cannot be changed to be so
		*/
		void Set(const float& value, std::uint32_t index = 0);

		/**
		* Sets a value of the vector datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type glm::vec4 and cannot be changed to be so
		*/
		void Set(const glm::vec4& value, std::uint32_t index = 0);

		/**
		* Sets a value of the matrix datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type glm::mat4 and cannot be changed to be so
		*/
		void Set(const glm::mat4& value, std::uint32_t index = 0);

		/**
		* Sets a value of the table pointer datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type table pointer and cannot be changed to be so
		*/
		void Set(Scope* value, std::uint32_t index = 0);

		/**
		* Sets a value of the string datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type std::string and cannot be changed to be so
		*/
		void Set(const std::string& value, std::uint32_t index = 0);

		/**
		* Sets a value of the RTTI pointer datum at the given index.
		* @param value	the value to set
		* @param index	the index to set the value at
		* @throws an exception if the datum is not of type RTTI pointer and cannot be changed to be so
		*/
		void Set(RTTI* value, std::uint32_t index = 0);

		/**
		 * Gets the int value within the datum at the given index.
		 * @param index	the index to get the value at within the datum
		 * @throws an exception if the index is above the size of the datum
		 * @return an int at the specified index within the datum
		 */
		int& GetInteger(std::uint32_t index = 0) const;

		/**
		* Gets the float value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return a float at the specified index within the datum
		*/
		float& GetFloat(std::uint32_t index = 0) const;

		/**
		* Gets the vector value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return a vector at the specified index within the datum
		*/
		glm::vec4& GetVector(std::uint32_t index = 0) const;

		/**
		* Gets the matrix value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return a matrix at the specified index within the datum
		*/
		glm::mat4& GetMatrix(std::uint32_t index = 0) const;

		/**
		* Gets the Scope pointer value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return a Scope pointer at the specified index within the datum
		*/
		Scope*& GetTable(std::uint32_t index = 0) const;

		/**
		* Gets the string value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return a string at the specified index within the datum
		*/
		std::string& GetString(std::uint32_t index = 0) const;

		/**
		* Gets the RTTI pointer value within the datum at the given index.
		* @param index	the index to get the value at within the datum
		* @throws an exception if the index is above the size of the datum
		* @return an RTTI pointer at the specified index within the datum
		*/
		RTTI*& GetPointer(std::uint32_t index = 0) const;

		/**
		 * Sets the datum value at the given index through a string argument.
		 * @param s	the string argument to set data with
		 * @param index	the index within the datum to be set
		 */
		void SetFromString(std::string s, std::uint32_t index = 0);

		/**
		 * Unused. Only throws an exceptions when called.
		 * @throws an exception immediately
		 */
		void SetUnknownFromString(std::string s, std::uint32_t index);

		/**
		* Sets the int datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the int datum to be set
		* @throws an exception if the datum could not be properly set
		*/
		void SetIntegersFromString(std::string s, std::uint32_t index);

		/**
		* Sets the float datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the float datum to be set
		* @throws an exception if the datum could not be properly set
		*/
		void SetFloatsFromString(std::string s, std::uint32_t index);

		/**
		* Sets the vector datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the vector datum to be set
		* @throws an exception if the datum could not be properly set
		*/
		void SetVectorsFromString(std::string s, std::uint32_t index);

		/**
		* Sets the matrix datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the matrix datum to be set
		* @throws an exception if the datum could not be properly set
		*/
		void SetMatricesFromString(std::string s, std::uint32_t index);

		/**
		* Sets the string datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the string datum to be set
		*/
		void SetStringsFromString(std::string s, std::uint32_t index);

		/**
		* Sets the RTTI (or Scope) pointer datum value at the given index through a string argument.
		* @param s	the string argument to set data with
		* @param index	the index within the RTTI (or Scope) pointer datum to be set
		* @throws an exception if the datum could not be properly set
		*/
		void SetPointersFromString(std::string s, std::uint32_t index);

		/**
		 * Converts a datum value at the given index to a string and returns it.
		 * @param index	the index within the datum to convert a string to
		 * @return a string representation of the value within the datum
		 */
		std::string ToString(std::uint32_t index = 0) const;

		/**
		* Unused. Only throws an exceptions when called.
		* @throws an exception immediately
		*/
		std::string UnknownToString(std::uint32_t index) const;

		/**
		 * Converts an int datum value at the given index to a string an returns it.
		 * @param index	the index within the datum to convert a string to
		 * @return a string representation of the int value within the datum
		 */
		std::string IntegersToString(std::uint32_t index) const;

		/**
		* Converts a float datum value at the given index to a string an returns it.
		* @param index	the index within the datum to convert a string to
		* @return a string representation of the float value within the datum
		*/
		std::string FloatsToString(std::uint32_t index) const;

		/**
		* Converts a vector datum value at the given index to a string an returns it.
		* @param index	the index within the datum to convert a string to
		* @return a string representation of the vector value within the datum
		*/
		std::string VectorsToString(std::uint32_t index) const;

		/**
		* Converts a matrix datum value at the given index to a string an returns it.
		* @param index	the index within the datum to convert a string to
		* @return a string representation of the matrix value within the datum
		*/
		std::string MatricesToString(std::uint32_t index) const;

		/**
		* Returns the string at the given index.
		* @param index	the index within the datum to convert a string to
		* @return a string value within the datum
		*/
		std::string StringsToString(std::uint32_t index) const;

		/**
		* Converts an RTTI (or Scope) pointer datum value at the given index to a string an returns it.
		* @param index	the index within the datum to convert a string to
		* @return a string representation of the RTTI (or Scope) pointer value within the datum
		*/
		std::string PointersToString(std::uint32_t index) const;

		typedef void(Datum::*AllocFunction)(std::uint32_t size); /**< A type for holding the alloc functions. */
		const static AllocFunction AllocFn[]; /**< The function pointer to hold the alloc functions. */

		typedef void(Datum::*AssignFunction)(const Datum& rhs); /**< A type for holding the assignment functions. */
		const static AssignFunction AssignFn[]; /**< The function pointer to hold the assignment functions. */

		typedef bool(Datum::*CompareFunction)(const Datum& rhs) const; /**< A type for holding the comparison functions. */
		const static CompareFunction CompareFn[]; /**< The function pointer to hold the comparison functions. */

		typedef void(Datum::*ClearFunction)(void); /**< A type for holding the clear functions. */
		const static ClearFunction ClearFn[]; /**< The function pointer to hold the clear functions. */

		typedef void(Datum::*SetFromStringFunction)(std::string s, std::uint32_t index); /**< A type for holding the SetFromString functions. */
		const static SetFromStringFunction SetStringFn[]; /**< The function pointer to hold the SetFromString functions. */

		typedef std::string(Datum::*ToStringFunction)(std::uint32_t index) const; /**< A type for holding the ToString functions. */
		const static ToStringFunction ToStringFn[]; /**< The function pointer to hold the ToString functions. */

	private:
		DatumType mType; /**< The type the datum is set to. */
		DatumValues mDatum; /**< The union that holds the datum values. */
		std::uint32_t mSize; /**< The size of the datum. */
		std::uint32_t mCapacity; /**< The capacity of the datum. */
		bool mIsExternal; /**< Tells if the datum contains internal storage or external storage. */
	};
}