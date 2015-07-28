#include <cxxtest/TestSuite.h>
#include "AttributedFoo.h"

using namespace Library;

class AttributedFooTestSuite : public CxxTest::TestSuite
{
public:
	void TestAttributedFooInstantiation(void)
	{
		AttributedFoo f;

		AttributedFoo f2(10, 11.0f, glm::vec4(12.0f), glm::mat4(13.0f), std::string("14"));
	}
	
	void TestAttributedFooCopyConstuctor(void)
	{
		AttributedFoo f;

		f.AppendAuxiliaryAttribute(std::string("AuxiliaryInteger")) = 10;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryFloat")) = 10.0f;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryVector")) = glm::vec4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryMatrix")) = glm::mat4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryString")) = std::string("10");

		AttributedFoo f2(f);

		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryInteger")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryFloat")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryVector")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryMatrix")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryString")));

		TS_ASSERT_EQUALS(f[std::string("AuxiliaryInteger")], f2[std::string("AuxiliaryInteger")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryFloat")], f2[std::string("AuxiliaryFloat")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryVector")], f2[std::string("AuxiliaryVector")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryMatrix")], f2[std::string("AuxiliaryMatrix")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryString")], f2[std::string("AuxiliaryString")]);

		TS_ASSERT(f[std::string("this")] != f2[std::string("this")]);
		TS_ASSERT(&f[std::string("AuxiliaryInteger")] != &f2[std::string("AuxiliaryInteger")]);
		TS_ASSERT(&f[std::string("AuxiliaryFloat")] != &f2[std::string("AuxiliaryFloat")]);
		TS_ASSERT(&f[std::string("AuxiliaryVector")] != &f2[std::string("AuxiliaryVector")]);
		TS_ASSERT(&f[std::string("AuxiliaryMatrix")] != &f2[std::string("AuxiliaryMatrix")]);
		TS_ASSERT(&f[std::string("AuxiliaryString")] != &f2[std::string("AuxiliaryString")]);
	}

	void TestAttributedFooAssignmentOperator(void)
	{
		AttributedFoo f;

		f.AppendAuxiliaryAttribute(std::string("AuxiliaryInteger")) = 10;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryFloat")) = 10.0f;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryVector")) = glm::vec4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryMatrix")) = glm::mat4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryString")) = std::string("10");

		AttributedFoo f2;
		f2 = f;

		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryInteger")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryFloat")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryVector")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryMatrix")));
		TS_ASSERT(f2.IsAttribute(std::string("AuxiliaryString")));

		TS_ASSERT_EQUALS(f[std::string("AuxiliaryInteger")], f2[std::string("AuxiliaryInteger")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryFloat")], f2[std::string("AuxiliaryFloat")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryVector")], f2[std::string("AuxiliaryVector")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryMatrix")], f2[std::string("AuxiliaryMatrix")]);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryString")], f2[std::string("AuxiliaryString")]);

		TS_ASSERT(f[std::string("this")] != f2[std::string("this")]);
		TS_ASSERT(&f[std::string("AuxiliaryInteger")] != &f2[std::string("AuxiliaryInteger")]);
		TS_ASSERT(&f[std::string("AuxiliaryFloat")] != &f2[std::string("AuxiliaryFloat")]);
		TS_ASSERT(&f[std::string("AuxiliaryVector")] != &f2[std::string("AuxiliaryVector")]);
		TS_ASSERT(&f[std::string("AuxiliaryMatrix")] != &f2[std::string("AuxiliaryMatrix")]);
		TS_ASSERT(&f[std::string("AuxiliaryString")] != &f2[std::string("AuxiliaryString")]);
	}

	void TestAttributedFooPopulateProtection(void)
	{
		AttributedFoo f;
		TS_ASSERT_THROWS_NOTHING(f.Populate());
	}

	void TestAttributedFooTypes(void)
	{
		AttributedFoo f;

		f.AppendAuxiliaryAttribute(std::string("AuxiliaryInteger")) = 10;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryFloat")) = 10.0f;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryVector")) = glm::vec4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryMatrix")) = glm::mat4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryString")) = std::string("10");

		TS_ASSERT(f.IsAttribute(std::string("this")));
		TS_ASSERT(f.IsAttribute(std::string("InternalInteger")));
		TS_ASSERT(f.IsAttribute(std::string("InternalIntegerArray")));
		TS_ASSERT(f.IsAttribute(std::string("InternalFloat")));
		TS_ASSERT(f.IsAttribute(std::string("InternalFloatArray")));
		TS_ASSERT(f.IsAttribute(std::string("InternalVector")));
		TS_ASSERT(f.IsAttribute(std::string("InternalVectorArray")));
		TS_ASSERT(f.IsAttribute(std::string("InternalMatrix")));
		TS_ASSERT(f.IsAttribute(std::string("InternalMatrixArray")));
		TS_ASSERT(f.IsAttribute(std::string("InternalString")));
		TS_ASSERT(f.IsAttribute(std::string("InternalStringArray")));
		TS_ASSERT(f.IsAttribute(std::string("ExternalInteger")));
		TS_ASSERT(f.IsAttribute(std::string("ExternalFloat")));
		TS_ASSERT(f.IsAttribute(std::string("ExternalVector")));
		TS_ASSERT(f.IsAttribute(std::string("ExternalMatrix")));
		TS_ASSERT(f.IsAttribute(std::string("ExternalString")));
		TS_ASSERT(f.IsAttribute(std::string("AuxiliaryInteger")));
		TS_ASSERT(f.IsAttribute(std::string("AuxiliaryFloat")));
		TS_ASSERT(f.IsAttribute(std::string("AuxiliaryVector")));
		TS_ASSERT(f.IsAttribute(std::string("AuxiliaryMatrix")));
		TS_ASSERT(f.IsAttribute(std::string("AuxiliaryString")));

		TS_ASSERT(f.IsPrescribedAttribute(std::string("this")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalInteger")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalIntegerArray")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalFloat")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalFloatArray")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalVector")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalVectorArray")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalMatrix")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalMatrixArray")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalString")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("InternalStringArray")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("ExternalInteger")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("ExternalFloat")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("ExternalVector")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("ExternalMatrix")));
		TS_ASSERT(f.IsPrescribedAttribute(std::string("ExternalString")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("AuxiliaryInteger")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("AuxiliaryFloat")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("AuxiliaryVector")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("AuxiliaryMatrix")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("AuxiliaryString")));

		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("this")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalInteger")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalIntegerArray")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalFloat")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalFloatArray")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalVector")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalVectorArray")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalMatrix")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalMatrixArray")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalString")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("InternalStringArray")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("ExternalInteger")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("ExternalFloat")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("ExternalVector")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("ExternalMatrix")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("ExternalString")));
		TS_ASSERT(f.IsAuxiliaryAttribute(std::string("AuxiliaryInteger")));
		TS_ASSERT(f.IsAuxiliaryAttribute(std::string("AuxiliaryFloat")));
		TS_ASSERT(f.IsAuxiliaryAttribute(std::string("AuxiliaryVector")));
		TS_ASSERT(f.IsAuxiliaryAttribute(std::string("AuxiliaryMatrix")));
		TS_ASSERT(f.IsAuxiliaryAttribute(std::string("AuxiliaryString")));

		TS_ASSERT(!f.IsAttribute(std::string("NotAnAttribute")));
		TS_ASSERT(!f.IsPrescribedAttribute(std::string("NotAnAttribute")));
		TS_ASSERT(!f.IsAuxiliaryAttribute(std::string("NotAnAttribute")));
	}

	void TestAttributedFooValues(void)
	{
		AttributedFoo f;

		f.AppendAuxiliaryAttribute(std::string("AuxiliaryInteger")) = 10;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryFloat")) = 10.0f;
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryVector")) = glm::vec4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryMatrix")) = glm::mat4(10.0f);
		f.AppendAuxiliaryAttribute(std::string("AuxiliaryString")) = std::string("10");

		TS_ASSERT_EQUALS(f[std::string("this")].GetPointer(), &f);

		TS_ASSERT_EQUALS(f[std::string("InternalInteger")].GetInteger(), 4);
		TS_ASSERT_EQUALS(f[std::string("InternalIntegerArray")].GetInteger(0), 1);
		TS_ASSERT_EQUALS(f[std::string("InternalIntegerArray")].GetInteger(1), 2);
		TS_ASSERT_EQUALS(f[std::string("InternalIntegerArray")].GetInteger(2), 3);

		TS_ASSERT_EQUALS(f[std::string("InternalFloat")].GetFloat(), 4.0f);
		TS_ASSERT_EQUALS(f[std::string("InternalFloatArray")].GetFloat(0), 1.0f);
		TS_ASSERT_EQUALS(f[std::string("InternalFloatArray")].GetFloat(1), 2.0f);
		TS_ASSERT_EQUALS(f[std::string("InternalFloatArray")].GetFloat(2), 3.0f);

		TS_ASSERT_EQUALS(f[std::string("InternalVector")].GetVector(), glm::vec4(4.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalVectorArray")].GetVector(0), glm::vec4(1.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalVectorArray")].GetVector(1), glm::vec4(2.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalVectorArray")].GetVector(2), glm::vec4(3.0f));

		TS_ASSERT_EQUALS(f[std::string("InternalMatrix")].GetMatrix(), glm::mat4(4.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalMatrixArray")].GetMatrix(0), glm::mat4(1.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalMatrixArray")].GetMatrix(1), glm::mat4(2.0f));
		TS_ASSERT_EQUALS(f[std::string("InternalMatrixArray")].GetMatrix(2), glm::mat4(3.0f));

		TS_ASSERT_EQUALS(f[std::string("InternalString")].GetString(), std::string("4"));
		TS_ASSERT_EQUALS(f[std::string("InternalStringArray")].GetString(0), std::string("1"));
		TS_ASSERT_EQUALS(f[std::string("InternalStringArray")].GetString(1), std::string("2"));
		TS_ASSERT_EQUALS(f[std::string("InternalStringArray")].GetString(2), std::string("3"));

		TS_ASSERT_EQUALS(f[std::string("ExternalInteger")].GetInteger(), 1);
		TS_ASSERT_EQUALS(f[std::string("ExternalFloat")].GetFloat(), 2.0f);
		TS_ASSERT_EQUALS(f[std::string("ExternalVector")].GetVector(), glm::vec4(3.0f));
		TS_ASSERT_EQUALS(f[std::string("ExternalMatrix")].GetMatrix(), glm::mat4(4.0f));
		TS_ASSERT_EQUALS(f[std::string("ExternalString")].GetString(), std::string("5"));

		TS_ASSERT_EQUALS(f[std::string("AuxiliaryInteger")].GetInteger(), 10);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryFloat")].GetFloat(), 10.0f);
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryVector")].GetVector(), glm::vec4(10.0f));
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryMatrix")].GetMatrix(), glm::mat4(10.0f));
		TS_ASSERT_EQUALS(f[std::string("AuxiliaryString")].GetString(), std::string("10"));
	}

	void TestAttributedFooAuxiliaryBegin(void)
	{
		AttributedFoo f;  // f should have a 16 prescibed members: 1 "this" attribute, 10 internal attributes, and 5 external attributes
		TS_ASSERT_EQUALS(f.AuxiliaryBegin(), 16);
	}
};