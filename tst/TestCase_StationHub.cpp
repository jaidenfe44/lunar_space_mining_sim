
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
	
	
	printf("    %-44s%s\n", "Test Case: StationHub::addToStation()", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}


bool TestCase_StationHub::TC_removeFromStation()
{
	// Initialize test case
	unsigned int idx = 2;
	nextAvailableStation = idx; // Setting next station index
	
	truck.state = TruckState::eMining;
	truck.work_time = 0;
	truck.unload_station = idx;
	
	truckTwo.state = TruckState::eMining;
	truckTwo.work_time = 0;
	truckTwo.unload_station = idx;
	
	stations_a[idx].addTruck(&truck);
	stations_a[idx].addTruck(&truckTwo);
	
	// Verify initial conditions
	tcAssert(stations_a[idx].unloadQueue.front() == &truck, __func__, "First MiningTruck is not at the front of the Station::unloadQueue");
	tcAssert(stations_a[idx].unloadQueue.size() == 2, __func__, "The Station::unloadQueue does not contain 2 MiningTrucks");
	tcAssert(truck.unload_station == idx, __func__, "First MiningTruck::unload_station was not set to the correct Station index");
	tcAssert(truckTwo.unload_station == idx, __func__, "Second MiningTruck::unload_station was not set to the correct Station index");
	
	// Execute function on Queued truck
	removeFromStation(&truckTwo);
	
	// Verify expected behavior
	tcAssert(stations_a[idx].unloadQueue.front() == &truck, __func__, "First MiningTruck was removed from Station::unloadQueue when attempting to removed a Queued truck");
	tcAssert(stations_a[idx].unloadQueue.size() == 2, __func__, "The number of MiningTrucks in Station::unloadQueue has changed when attempting to remove a Queued truck");
	tcAssert(truckTwo.state == TruckState::eQueued, __func__, "Second trucks MiningTruck::state was changed from TruckState::eQueued when attempted to remove a queued truck");
	tcAssert(nextAvailableStation == idx, __func__, "StationHub::nextAvailableStation was updated when it should not have been");
	
	// Execute function
	removeFromStation(&truck);
	
	// Verify expected behavior
	tcAssert(stations_a[idx].unloadQueue.front() == &truckTwo, __func__, "The queued MiningTruck was not updated to be at the front of the Station::unloadQueue");
	tcAssert(stations_a[idx].unloadQueue.size() == 1, __func__, "The Station::unloadQueue does not show that a MiningTruck was removed from the queue");
	tcAssert(truckTwo.state == TruckState::eUnloading, __func__, "The previously queued trucks MiningTruck::state was not updated to TruckSate::eUnloading");
	tcAssert(truck.work_time > stations_a[idx].unload_time, __func__, "The removed trucks MiningTruck::work_time was not updated to computed mining time (MiningTruck::computeMineTime() was not called)");
	tcAssert(nextAvailableStation != idx, __func__, "StationHub::nextAvailableStation was not updated");
	
	// Cleanup
	cleanup();
	
	
	printf("    %-44s%s\n", "Test Case: StationHub::removeFromStation()", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}


bool TestCase_StationHub::TC_step()
{
	// Initialize test case
	unsigned int workVal0 = 20;
	unsigned int workVal1 = 63;
	unsigned int workVal2 = 19;

	nextAvailableStation = 0;
	addToStation(&trucks_a[0]);
	nextAvailableStation = 0;
	addToStation(&trucks_a[1]);
	trucks_a[0].work_time = workVal0;
	trucks_a[1].work_time = workVal1;
	trucks_a[2].work_time = workVal2;

	// Verify initial conditions
	tcAssert(trucks_a[0].unload_station == 0, __func__, "MiningTruck[0] was not added to Station[0]");
	tcAssert(trucks_a[1].unload_station == 0, __func__, "MiningTruck[1] was not added to Station[0]");
	
	// Execute function
	step();
	
	// Verify expected behavior
	tcAssert(trucks_a[0].work_time == (workVal0 - 1), __func__, "MiningTruck::work_time for MiningTruck[0] (Unloading) was not decremented");
	tcAssert(trucks_a[1].work_time == workVal1, __func__, "MiningTruck::work_time for MiningTruck[1] (Queued) did not remain the same");
	tcAssert(trucks_a[2].work_time == (workVal2 - 1), __func__, "MiningTruck::work_time for MiningTruck[2] (Mining) was not decremented");

	tcAssert(false, __func__, "Need to flesh out this test case a bit more...")
	
	// Cleanup
	cleanup();
	
	
	printf("    %-44s%s\n", "Test Case: StationHub::step()", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}
