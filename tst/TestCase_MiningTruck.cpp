
#include "TestCase_MiningTruck.hpp"
#include "System.hpp"

#include <stdexcept>
#include <cstdio>


void TestCase_MiningTruck::cleanup()
{
	state = TruckState::eQueued;
	work_time = 0;
	workLifetime = 0;
	timeTraveling = 0;
	loadsDelivered = 0;
}


bool TestCase_MiningTruck::TC_computeMineTime()
{
	printf("    %-44s", "Test Case: MiningTruck::computeMineTime");

	try
	{
		// Initialize test case
		state = TruckState::eQueued;
		work_time = 0;
		workLifetime = 0;
		timeTraveling = 0;
		loadsDelivered = 0;

		// Execute function
		computeMineTime();

		// Verify expected behavior
		tcAssert(state == TruckState::eMining, __func__, "MiningTruck::state did not update to TruckState::eMining");
		tcAssert(work_time != 0, __func__, "MiningTruck::work_time was not updated");
		tcAssert(workLifetime == work_time, __func__, "MiningTruck::workLifetime was not updated");
		tcAssert(timeTraveling == (miningSiteTravelTime * 2), __func__, "MiningTruck::timeTraveling was not updated");
		tcAssert(loadsDelivered == 1, __func__, "MiningTruck::loadsDelivered was not updated");

		work_time = 0;
		unsigned int lastWorkLifetime = workLifetime;

		// Execute function
		computeMineTime();

		// Verify expected behavior after second execution
		tcAssert(state == TruckState::eMining, __func__, "MiningTruck::state did not update to TruckState::eMining");
		tcAssert(work_time != 0, __func__, "MiningTruck::work_time was not updated on second execution");
		tcAssert(workLifetime == (lastWorkLifetime + work_time), __func__, "MiningTruck::workLifetime was not updated on second execution");
		tcAssert(timeTraveling == (miningSiteTravelTime * 4), __func__, "MiningTruck::timeTraveling was not updated on second execution");
		tcAssert(loadsDelivered == 2, __func__, "MiningTruck::loadsDelivered was not updated on second execution");

		// Cleanup
		cleanup();

	
		printf("Passed\n");

		return true;
	}
	catch (const std::runtime_error& e)
	{
		return false;
	}
}

bool TestCase_MiningTruck::TC_reportStats()
{
	printf("    %-44s", "Test Case: MiningTruck::reportStats");

	try
	{
		// TODO: Initialize test case

		// TODO: Execute function

		// TODO: Verify expected behavior
		tcAssert(false, __func__, "TODO");

		printf("Passed\n");

		return true;
	}
	catch (const std::runtime_error& e)
	{
		return false;
	}
}
