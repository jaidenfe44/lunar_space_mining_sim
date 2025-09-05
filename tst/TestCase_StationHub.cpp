
#include "TestCase_StationHub.hpp"


void TestCase_StationHub::cleanup()
{
	for(int idx = 0; idx < stations_a.size(); idx++)
	{
		// Empty station queue
		while(!stations_a[idx].unloadQueue.empty())
		{
			stations_a[idx].unloadQueue.pop();
		}

		stations_a[idx].availabilityWeight = 0;
	}

	truck.state = TruckState::eMining;
	truck.work_time = 0;
	truck.unload_station = 0;

	truckTwo.state = TruckState::eMining;
	truckTwo.work_time = 0;
	truckTwo.unload_station = 0;
}

bool TestCase_StationHub::TC_addToStation()
{
	printf("    %-44s", "Test Case: StationHub::addToStation()");

    try
    {
        // Initialize test case
		unsigned int idx = 1;
		nextAvailableStation = idx;
		truck.state = TruckState::eMining;
		truck.work_time = 0;
		truck.unload_station = 0;

		truckTwo.state = TruckState::eMining;
		truckTwo.work_time = 0;
		truckTwo.unload_station = 0;

        // Execute function
		addToStation(&truck);

        // Verify expected behavior
        tcAssert(truck.state == TruckState::eUnloading, __func__, "MiningTruck::state was not updated to TruckState::eUnloading for added truck");
        tcAssert(truck.work_time == stations_a[idx].unload_time, __func__, "MiningTruck::work_time was not updated to the Station::unload_time");
        tcAssert(truck.unload_station == idx, __func__, "MiningTruck::unload_station was not updated to the Station index");
        tcAssert(nextAvailableStation != idx, __func__, "StationHub::nextAvailableStation was not updated");
		tcAssert(stations_a[idx].unloadQueue.front() == &truck, __func__, "Station::unloadQueue does not contain the MiningTruck object at the front of the queue");

		// Update next station to be the same as first execution
		nextAvailableStation = idx;

        // Execute function a second time
		addToStation(&truckTwo);

        // Verify expected behavior
        tcAssert(truckTwo.state == TruckState::eQueued, __func__, "MiningTruck::state was not updated to TruckState::eQueued for second added truck");
        tcAssert(truckTwo.work_time == stations_a[idx].unload_time, __func__, "Queued MiningTruck::work_time was not updated to the Station::unload_time");
        tcAssert(truckTwo.unload_station == idx, __func__, "Queued MiningTruck::unload_station was not updated to the Station index");
        tcAssert(nextAvailableStation != idx, __func__, "StationHub::nextAvailableStation was not updated");
 
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


bool TestCase_StationHub::TC_removeFromStation()
{
	printf("    %-44s", "Test Case: StationHub::removeFromStation()");

    try
    {
        // TODO: Initialize test case
		nextAvailableStation = 0; // Setting next station to index 0
		stations_a[0].addTruck(&truck);

        // TODO: Execute function
		removeFromStation(&truck);

        // TODO: Verify expected behavior
        tcAssert(false, __func__, "TODO");
 
		// Cleanup


		printf("Passed\n");
 
        return true;
    }
    catch (const std::runtime_error& e)
    {
        return false;
    }
}


bool TestCase_StationHub::TC_step()
{
	printf("    %-44s", "Test Case: StationHub::step");

    try
    {
        // TODO: Initialize test case

        // TODO: Execute function

        // TODO: Verify expected behavior
        tcAssert(false, __func__, "TODO");
 
		// Cleanup


		printf("Passed\n");
 
        return true;
    }
    catch (const std::runtime_error& e)
    {
        return false;
    }
}
