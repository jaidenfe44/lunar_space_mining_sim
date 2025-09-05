
#include "TestCase_Station.hpp"

void TestCase_Station::cleanup()
{
	while(!unloadQueue.empty())
	{
		unloadQueue.pop();
	}
	truck.work_time = 0;
	truck.state = TruckState::eMining;
	truckTwo.work_time = 0;
	truckTwo.state = TruckState::eMining;
}


bool TestCase_Station::TC_addTruck()
{
	// Initialize test case
	while(!unloadQueue.empty())
	{
		unloadQueue.pop();
	}
	
	truck.work_time = 0;
	truck.state = TruckState::eMining;
	truckTwo.work_time = 0;
	truckTwo.state = TruckState::eMining;
	
	// Execute function
	addTruck(&truck);
	
	// Verify expected behavior
	tcAssert(truck.work_time == unload_time, __func__, "MiningTruck::unload_time was not updated");
	tcAssert(truck.state == TruckState::eUnloading, __func__, "MiningTruck::state was not set to TruckState::eUnloading");
	tcAssert(unloadQueue.front() == &truck, __func__, "The front of the Station::unloadQueue did not match the MiningTruck object passed into the function");
	
	
	// Execute function
	addTruck(&truckTwo);
	
	// Verify expected behavior
	tcAssert(truckTwo.work_time == unload_time, __func__, "MiningTruck::unload_time was not updated for second truck");
	tcAssert(truckTwo.state == TruckState::eQueued, __func__, "MiningTruck::state was not set to TruckState::eQueued for second truck");
	tcAssert(unloadQueue.front() != &truckTwo, __func__, "The front of the Station::unloadQueue did matched the MiningTruck object passed into the function on the second call");
	
	// Check that the second truck in the queue is the second truck object
	unloadQueue.pop();
	tcAssert(unloadQueue.front() == &truckTwo, __func__, "The first queued MiningTruck in the Station::unloadQueue did not match the MiningTruck object passed into the function on the second call");
	
	// Cleanup
	cleanup();
	
	
	printf("    %-44s%s\n", "Test Case: Station::addTruck()", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}


bool TestCase_Station::TC_removeTruck()
{
	// Initialize test case
	while(!unloadQueue.empty())
	{
		unloadQueue.pop();
	}
	truck.work_time = 0;
	truck.state = TruckState::eMining;
	truckTwo.work_time = 0;
	truckTwo.state = TruckState::eMining;
	addTruck(&truck);
	addTruck(&truckTwo);
	
	// Verify initial state of both trucks
	tcAssert(truck.state == TruckState::eUnloading, __func__, "First truck in queues MiningTruck::state was not TruckState::eUnloading");
	tcAssert(truckTwo.state == TruckState::eQueued, __func__, "Second truck in queues MiningTruck::state was not TruckState::eQueued");
	tcAssert(unloadQueue.front() == &truck, __func__, "The first MiningTruck object is not at the front of the Station::unloadQueue");
	
	// Execute function
	removeTruck();
	
	// Verify expected behavior
	tcAssert(unloadQueue.front() == &truckTwo, __func__, "The second truck is not now at the front of the Station::unloadQueue");
	tcAssert(unloadQueue.front()->state == TruckState::eUnloading, __func__, "The MiningTruck::state of the truck at the front of the Station::unloadQueue is not TruckState::eUnloading");
	
	// Execute function a second time
	removeTruck();
	
	// Verify expected behavior
	tcAssert(unloadQueue.empty(), __func__, "The Station::unloadQueue is not empty");
	
	   // Execute function a third time when the queue is empty
	removeTruck();
	
	// Cleanup
	cleanup();
	
	
	printf("    %-44s%s\n", "Test Case: Station::removeTruck()", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}


bool TestCase_Station::TC_updateAvailability()
{
	// Initialize test case
	while(!unloadQueue.empty())
	{
		unloadQueue.pop();
	}
	addTruck(&truck);
	
	// Execute function
	updateAvailability();
	
	// Verify expected behavior
	tcAssert(availabilityWeight == unloadQueue.size(), __func__, "Station::availabilityWeight does not equal Station::unloadQueue.size");
	tcAssert(availabilityWeight == 1, __func__, "Station::availabilityWeight is not 1 after adding a single MiningTruck to the Station::unloadQueue");
	
	// Add another truck to the queue
	addTruck(&truckTwo);
	
	// Execute function
	updateAvailability();
	
	// Verify expected behavior
	tcAssert(availabilityWeight == unloadQueue.size(), __func__, "Station::availabilityWeight does not equal Station::unloadQueue.size");
	tcAssert(availabilityWeight == 2, __func__, "Station::availabilityWeight is not 2 after adding a second MiningTruck to the Station::unloadQueue");
	
	// Remove a truck
	removeTruck();
	
	// Execute function
	updateAvailability();
	
	// Verify expected behavior
	tcAssert(availabilityWeight == unloadQueue.size(), __func__, "Station::availabilityWeight does not equal Station::unloadQueue.size");
	tcAssert(availabilityWeight == 1, __func__, "Station::availabilityWeight is not 1 after removing one of the two MiningTruck from the Station::unloadQueue");
	
	// Cleanup
	cleanup();
	
	
	printf("    %-44s%s\n", "Test Case: Station::updateAvailability", tcPass ? "Passed" : "Failed");
	
	return tcPass;
}
