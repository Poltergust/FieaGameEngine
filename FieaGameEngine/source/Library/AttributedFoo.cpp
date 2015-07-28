#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() : mExternalInteger(1), mExternalFloat(2.0f), mExternalVector(3.0f), mExternalMatrix(4.0f), mExternalString(std::string("5"))
	{
		CreateAndPopulate();
	}

	AttributedFoo::AttributedFoo(int externalInteger, float externalFloat, glm::vec4 externalVector, glm::mat4 externalMatrix, std::string externalString)
		: mExternalInteger(externalInteger), mExternalFloat(externalFloat), mExternalVector(externalVector), mExternalMatrix(externalMatrix), mExternalString(externalString)
	{
		CreateAndPopulate();
	}

	void AttributedFoo::CreateAndPopulate()
	{
		int i = 4;
		int iArray[] = { 1, 2, 3 };
		float f = 4.0f;
		float fArray[] = { 1.0f, 2.0f, 3.0f };
		glm::vec4 v(4.0f);
		glm::vec4 vArray[] = { glm::vec4(1.0f), glm::vec4(2.0f), glm::vec4(3.0f) };
		glm::mat4 m(4.0f);
		glm::mat4 mArray[] = { glm::mat4(1.0f), glm::mat4(2.0f), glm::mat4(3.0f) };
		std::string s("4");
		std::string sArray[] = { std::string("1"), std::string("2"), std::string("3") };

		INTERNAL_ATTRIBUTE(std::string("InternalInteger"), Datum::Integer, &i, 1);
		INTERNAL_ATTRIBUTE(std::string("InternalIntegerArray"), Datum::Integer, &iArray, 3);
		INTERNAL_ATTRIBUTE(std::string("InternalFloat"), Datum::Float, &f, 1);
		INTERNAL_ATTRIBUTE(std::string("InternalFloatArray"), Datum::Float, &fArray, 3);
		INTERNAL_ATTRIBUTE(std::string("InternalVector"), Datum::Vector, &v, 1);
		INTERNAL_ATTRIBUTE(std::string("InternalVectorArray"), Datum::Vector, &vArray, 3);
		INTERNAL_ATTRIBUTE(std::string("InternalMatrix"), Datum::Matrix, &m, 1);
		INTERNAL_ATTRIBUTE(std::string("InternalMatrixArray"), Datum::Matrix, &mArray, 3);
		INTERNAL_ATTRIBUTE(std::string("InternalString"), Datum::String, &s, 1);
		INTERNAL_ATTRIBUTE(std::string("InternalStringArray"), Datum::String, &sArray, 3);

		EXTERNAL_ATTRIBUTE(std::string("ExternalInteger"), Datum::Integer, 1, &mExternalInteger);
		EXTERNAL_ATTRIBUTE(std::string("ExternalFloat"), Datum::Float, 1, &mExternalFloat);
		EXTERNAL_ATTRIBUTE(std::string("ExternalVector"), Datum::Vector, 1, &mExternalVector);
		EXTERNAL_ATTRIBUTE(std::string("ExternalMatrix"), Datum::Matrix, 1, &mExternalMatrix);
		EXTERNAL_ATTRIBUTE(std::string("ExternalString"), Datum::String, 1, &mExternalString);

		Populate();
	}
}