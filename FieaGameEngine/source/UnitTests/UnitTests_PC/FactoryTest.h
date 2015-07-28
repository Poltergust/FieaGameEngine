#include <cxxtest/TestSuite.h>
#include "AttributedFoo.h"
#include "Factory.h"

using namespace Library;

class FactoryTestSuite : public CxxTest::TestSuite
{
public:
	ConcreteFactory(AttributedFoo, RTTI)

	void TestFactoryInstantiation(void)
	{
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("AttributedFoo"), nullptr);
		TS_ASSERT_EQUALS(Factory<RTTI>::Create("AttributedFoo"), nullptr);
		TS_ASSERT_EQUALS(Factory<RTTI>::begin(), Factory<RTTI>::end());

		AttributedFooFactory aFooFactory;
		TS_ASSERT_EQUALS(Factory<RTTI>::begin()->second, Factory<RTTI>::Find("AttributedFoo"));
		TS_ASSERT(Factory<RTTI>::begin() != Factory<RTTI>::end());

		RTTI* r = Factory<RTTI>::Create(std::string("AttributedFoo"));
		TS_ASSERT(r != nullptr);
		AttributedFoo* f = r->As<AttributedFoo>();
		TS_ASSERT(f != nullptr);
		delete r;
	}

	void TestFactoryFunctionality(void)
	{
		AttributedFooFactory aFooFactory;
		RTTI* r = Factory<RTTI>::Create(std::string("AttributedFoo"));
		TS_ASSERT(r != nullptr);
		AttributedFoo* f = r->As<AttributedFoo>();
		TS_ASSERT(f != nullptr);

		f->AppendAuxiliaryAttribute(std::string("AuxiliaryInteger")) = 10;
		f->AppendAuxiliaryAttribute(std::string("AuxiliaryFloat")) = 10.0f;
		f->AppendAuxiliaryAttribute(std::string("AuxiliaryVector")) = glm::vec4(10.0f);
		f->AppendAuxiliaryAttribute(std::string("AuxiliaryMatrix")) = glm::mat4(10.0f);
		f->AppendAuxiliaryAttribute(std::string("AuxiliaryString")) = std::string("10");

		TS_ASSERT_EQUALS((*f)[std::string("this")].GetPointer(), f);

		TS_ASSERT_EQUALS((*f)[std::string("InternalInteger")].GetInteger(), 4);
		TS_ASSERT_EQUALS((*f)[std::string("InternalIntegerArray")].GetInteger(0), 1);
		TS_ASSERT_EQUALS((*f)[std::string("InternalIntegerArray")].GetInteger(1), 2);
		TS_ASSERT_EQUALS((*f)[std::string("InternalIntegerArray")].GetInteger(2), 3);

		TS_ASSERT_EQUALS((*f)[std::string("InternalFloat")].GetFloat(), 4.0f);
		TS_ASSERT_EQUALS((*f)[std::string("InternalFloatArray")].GetFloat(0), 1.0f);
		TS_ASSERT_EQUALS((*f)[std::string("InternalFloatArray")].GetFloat(1), 2.0f);
		TS_ASSERT_EQUALS((*f)[std::string("InternalFloatArray")].GetFloat(2), 3.0f);

		TS_ASSERT_EQUALS((*f)[std::string("InternalVector")].GetVector(), glm::vec4(4.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalVectorArray")].GetVector(0), glm::vec4(1.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalVectorArray")].GetVector(1), glm::vec4(2.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalVectorArray")].GetVector(2), glm::vec4(3.0f));

		TS_ASSERT_EQUALS((*f)[std::string("InternalMatrix")].GetMatrix(), glm::mat4(4.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalMatrixArray")].GetMatrix(0), glm::mat4(1.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalMatrixArray")].GetMatrix(1), glm::mat4(2.0f));
		TS_ASSERT_EQUALS((*f)[std::string("InternalMatrixArray")].GetMatrix(2), glm::mat4(3.0f));

		TS_ASSERT_EQUALS((*f)[std::string("InternalString")].GetString(), std::string("4"));
		TS_ASSERT_EQUALS((*f)[std::string("InternalStringArray")].GetString(0), std::string("1"));
		TS_ASSERT_EQUALS((*f)[std::string("InternalStringArray")].GetString(1), std::string("2"));
		TS_ASSERT_EQUALS((*f)[std::string("InternalStringArray")].GetString(2), std::string("3"));

		TS_ASSERT_EQUALS((*f)[std::string("ExternalInteger")].GetInteger(), 1);
		TS_ASSERT_EQUALS((*f)[std::string("ExternalFloat")].GetFloat(), 2.0f);
		TS_ASSERT_EQUALS((*f)[std::string("ExternalVector")].GetVector(), glm::vec4(3.0f));
		TS_ASSERT_EQUALS((*f)[std::string("ExternalMatrix")].GetMatrix(), glm::mat4(4.0f));
		TS_ASSERT_EQUALS((*f)[std::string("ExternalString")].GetString(), std::string("5"));

		TS_ASSERT_EQUALS((*f)[std::string("AuxiliaryInteger")].GetInteger(), 10);
		TS_ASSERT_EQUALS((*f)[std::string("AuxiliaryFloat")].GetFloat(), 10.0f);
		TS_ASSERT_EQUALS((*f)[std::string("AuxiliaryVector")].GetVector(), glm::vec4(10.0f));
		TS_ASSERT_EQUALS((*f)[std::string("AuxiliaryMatrix")].GetMatrix(), glm::mat4(10.0f));
		TS_ASSERT_EQUALS((*f)[std::string("AuxiliaryString")].GetString(), std::string("10"));

		delete r;
	}
};