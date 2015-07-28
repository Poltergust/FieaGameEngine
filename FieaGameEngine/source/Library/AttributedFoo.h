#pragma once

#include "Attributed.h"

namespace Library
{
	class AttributedFoo : public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	public:

		/**
		 * The constructor.
		 */
		AttributedFoo();

		/**
		 * The constructor. Takes in parameters.
		 * @param externalInteger	the value to set mExternalInteger to
		 * @param externalFloat		the value to set mExternalFloat to
		 * @param externalVector	the value to set mExternalVector to
		 * @param externalMatrix	the value to set mExternalMatrix to
		 * @param externalString	the value to set mExternalString to
		 */
		AttributedFoo(int externalInteger, float externalFloat, glm::vec4 externalVector, glm::mat4 externalMatrix, std::string externalString);

		/**
		 * The copy constructor.
		 * @param rhs	the AttributedFoo object to copy
		 */
		AttributedFoo(const AttributedFoo& rhs) = default;

		/**
		 * The assignment operato.
		 * @param rhs	the AttributedFoo object to copy
		 * @return a reference to the newly copied AttributedFoo
		 */
		AttributedFoo& operator=(const AttributedFoo& rhs) = default;

		/**
		 * The destructor.
		 */
		virtual ~AttributedFoo() = default;

	private:
		/**
		 * Creates internal storage data and populates this object with attributes.
		 */
		void CreateAndPopulate();

		int mExternalInteger; /**< An external int. */
		float mExternalFloat; /**< An external float. */
		glm::vec4 mExternalVector; /**< An external vector. */
		glm::mat4 mExternalMatrix; /**< An external matrix. */
		std::string mExternalString; /**< An external string. */
	};
}