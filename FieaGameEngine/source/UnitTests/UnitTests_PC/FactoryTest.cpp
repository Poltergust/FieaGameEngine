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

bool suite_FactoryTestSuite_init = false;
#include "FactoryTest.h"

static FactoryTestSuite suite_FactoryTestSuite;

static CxxTest::List Tests_FactoryTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FactoryTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/FieaGameEngine/source/UnitTests/UnitTests_PC/FactoryTest.h", 7, "FactoryTestSuite", suite_FactoryTestSuite, Tests_FactoryTestSuite );

static class TestDescription_suite_FactoryTestSuite_TestFactoryInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestFactoryInstantiation() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 12, "TestFactoryInstantiation" ) {}
 void runTest() { suite_FactoryTestSuite.TestFactoryInstantiation(); }
} testDescription_suite_FactoryTestSuite_TestFactoryInstantiation;

static class TestDescription_suite_FactoryTestSuite_TestFactoryFunctionality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestFactoryFunctionality() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 29, "TestFactoryFunctionality" ) {}
 void runTest() { suite_FactoryTestSuite.TestFactoryFunctionality(); }
} testDescription_suite_FactoryTestSuite_TestFactoryFunctionality;

