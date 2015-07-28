/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_EntityTestSuite_init = false;
#include "EntityTest.h"

static EntityTestSuite suite_EntityTestSuite;

static CxxTest::List Tests_EntityTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EntityTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/FieaGameEngine/source/UnitTests/UnitTests_PC/EntityTest.h", 6, "EntityTestSuite", suite_EntityTestSuite, Tests_EntityTestSuite );

static class TestDescription_suite_EntityTestSuite_TestEntityInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EntityTestSuite_TestEntityInstantiation() : CxxTest::RealTestDescription( Tests_EntityTestSuite, suiteDescription_EntityTestSuite, 9, "TestEntityInstantiation" ) {}
 void runTest() { suite_EntityTestSuite.TestEntityInstantiation(); }
} testDescription_suite_EntityTestSuite_TestEntityInstantiation;

static class TestDescription_suite_EntityTestSuite_TestEntityName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EntityTestSuite_TestEntityName() : CxxTest::RealTestDescription( Tests_EntityTestSuite, suiteDescription_EntityTestSuite, 15, "TestEntityName" ) {}
 void runTest() { suite_EntityTestSuite.TestEntityName(); }
} testDescription_suite_EntityTestSuite_TestEntityName;

