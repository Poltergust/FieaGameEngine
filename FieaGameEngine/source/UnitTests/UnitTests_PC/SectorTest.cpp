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

bool suite_SectorTestSuite_init = false;
#include "SectorTest.h"

static SectorTestSuite suite_SectorTestSuite;

static CxxTest::List Tests_SectorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SectorTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/FieaGameEngine/source/UnitTests/UnitTests_PC/SectorTest.h", 8, "SectorTestSuite", suite_SectorTestSuite, Tests_SectorTestSuite );

static class TestDescription_suite_SectorTestSuite_TestSectorInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SectorTestSuite_TestSectorInstantiation() : CxxTest::RealTestDescription( Tests_SectorTestSuite, suiteDescription_SectorTestSuite, 11, "TestSectorInstantiation" ) {}
 void runTest() { suite_SectorTestSuite.TestSectorInstantiation(); }
} testDescription_suite_SectorTestSuite_TestSectorInstantiation;

static class TestDescription_suite_SectorTestSuite_TestSectorName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SectorTestSuite_TestSectorName() : CxxTest::RealTestDescription( Tests_SectorTestSuite, suiteDescription_SectorTestSuite, 17, "TestSectorName" ) {}
 void runTest() { suite_SectorTestSuite.TestSectorName(); }
} testDescription_suite_SectorTestSuite_TestSectorName;

static class TestDescription_suite_SectorTestSuite_TestEntitiesWithinSectors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SectorTestSuite_TestEntitiesWithinSectors() : CxxTest::RealTestDescription( Tests_SectorTestSuite, suiteDescription_SectorTestSuite, 26, "TestEntitiesWithinSectors" ) {}
 void runTest() { suite_SectorTestSuite.TestEntitiesWithinSectors(); }
} testDescription_suite_SectorTestSuite_TestEntitiesWithinSectors;

