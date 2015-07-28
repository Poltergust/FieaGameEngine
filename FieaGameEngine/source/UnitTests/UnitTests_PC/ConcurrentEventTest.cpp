/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_ConcurrentEventSuite_init = false;
#include "ConcurrentEventTest.h"

static ConcurrentEventSuite suite_ConcurrentEventSuite;

static CxxTest::List Tests_ConcurrentEventSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConcurrentEventSuite( "C:/dev/Cohort11-Public/Classes/Programming II/FieaGameEngine/source/UnitTests/UnitTests_PC/ConcurrentEventTest.h", 10, "ConcurrentEventSuite", suite_ConcurrentEventSuite, Tests_ConcurrentEventSuite );

static class TestDescription_suite_ConcurrentEventSuite_TestConcurrentEventInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ConcurrentEventSuite_TestConcurrentEventInstantiation() : CxxTest::RealTestDescription( Tests_ConcurrentEventSuite, suiteDescription_ConcurrentEventSuite, 13, "TestConcurrentEventInstantiation" ) {}
 void runTest() { suite_ConcurrentEventSuite.TestConcurrentEventInstantiation(); }
} testDescription_suite_ConcurrentEventSuite_TestConcurrentEventInstantiation;

static class TestDescription_suite_ConcurrentEventSuite_TestConcurrentEventNotify : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ConcurrentEventSuite_TestConcurrentEventNotify() : CxxTest::RealTestDescription( Tests_ConcurrentEventSuite, suiteDescription_ConcurrentEventSuite, 24, "TestConcurrentEventNotify" ) {}
 void runTest() { suite_ConcurrentEventSuite.TestConcurrentEventNotify(); }
} testDescription_suite_ConcurrentEventSuite_TestConcurrentEventNotify;

