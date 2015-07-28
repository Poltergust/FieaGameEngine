#include <cxxtest/TestSuite.h>
//#include "vld.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

class MyTestSuite : public CxxTest::TestSuite
{
public:
	void TestAddition(void)
	{
#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

		TS_ASSERT_EQUALS(1 + 1, 2);
	}
};