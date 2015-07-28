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

bool suite_EventTestSuite_init = false;
#include "EventTest.h"

static EventTestSuite suite_EventTestSuite;

static CxxTest::List Tests_EventTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EventTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/FieaGameEngine/source/UnitTests/UnitTests_PC/EventTest.h", 8, "EventTestSuite", suite_EventTestSuite, Tests_EventTestSuite );

static class TestDescription_suite_EventTestSuite_TestEventInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventInstantiation() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 11, "TestEventInstantiation" ) {}
 void runTest() { suite_EventTestSuite.TestEventInstantiation(); }
} testDescription_suite_EventTestSuite_TestEventInstantiation;

static class TestDescription_suite_EventTestSuite_TestEventNotifying : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventNotifying() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 23, "TestEventNotifying" ) {}
 void runTest() { suite_EventTestSuite.TestEventNotifying(); }
} testDescription_suite_EventTestSuite_TestEventNotifying;

static class TestDescription_suite_EventTestSuite_TestEventDeletion : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventDeletion() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 37, "TestEventDeletion" ) {}
 void runTest() { suite_EventTestSuite.TestEventDeletion(); }
} testDescription_suite_EventTestSuite_TestEventDeletion;

static class TestDescription_suite_EventTestSuite_TestEventDelay : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventDelay() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 51, "TestEventDelay" ) {}
 void runTest() { suite_EventTestSuite.TestEventDelay(); }
} testDescription_suite_EventTestSuite_TestEventDelay;

static class TestDescription_suite_EventTestSuite_TestEventQueueing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventQueueing() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 77, "TestEventQueueing" ) {}
 void runTest() { suite_EventTestSuite.TestEventQueueing(); }
} testDescription_suite_EventTestSuite_TestEventQueueing;

