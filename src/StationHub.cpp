#include "StationHub.hpp"

#include <cstdio>



/**
 * The main simulation progression function
 *
 * This function executes one minute of simulation time and "steps" through the simulation. Sequences through the Miningtruck array to update the system depending on the MiningTruck objects state (eMining, eUnloading, or eQueued).
 * 
 * @return void
 */
void StationHub::step()
{
	// Check if trucks are done with their current task
	for(int i = 0; i < numTrucks; i++)
	{
		MiningTruck* idx = &trucks_a[i];

		// If the truck is waiting in a queue, increment the wait timer, otherwise decrement the work timer
		idx->state == TruckState::eQueued ? idx->wait_time++ : idx->work_time--;


		// Check if the Truck is done with its current task (mining or unloading, queued trucks dont update work_time)
		if(idx->work_time == 0)
		{
			switch(idx->state)
			{
				case TruckState::eMining:
					// Finished Mining, add to the next available Station or Station Queue
					addToStation(idx);
					break;

				case TruckState::eUnloading:
					// Truck finished unloading, remove from the Station
					removeFromStation(idx);
					break;

				default:
					// Should never get here
					break;
			}
		}
	}
}


/**
 * Update the index of the next available station
 *
 * This function uses the queue size of each Station to calculate the availability weight. The lower the
 * weight the "more available" the Station is. The first instance of the lowest availability weight is
 * stored in the StationHub::nextAvailableStation variable.
 *
 * @return void
 */
void StationHub::updateNextAvailable()
{
	// Note: Currently just implementing first instance of lowest queue length. This could be improved
	//		upon by attemting to sequence through the stations so the first few stations dont get favored
	//		over the others. To accomplish this I would start by adding an adjustment to the availability
	//		weight of the next station in the sequence (start with a -1 adjustment to weight) which should
	//		favor the next station in line but only if there are other stations with the same weight (i.e.
	//		queue length). Another improvement could be to look into the queue length and truck "work_time
	//		remaining", which is how long the truck will need to stay at that specific station until it
	//		can go mine again. Both are fairly straight forward and simple.
	for(int i = 0; i < stations_a.size(); i++)
	{
		// Update the availability weight of the current Station index
		stations_a[i].updateAvailability();

		// Check if the availability weight of the current index is less than the availability weight at
		// the previous nextAvailableStation index
		if(stations_a[i].availabilityWeight < stations_a[nextAvailableStation].availabilityWeight)
		{
			// Update the next available Station index
			nextAvailableStation = i;
		}
	}
}


/**
 * Add a MiningTruck to the next available Station
 *
 * @param A pointer to the MiningTruck object that is headed to the next
 *			available station or station queue
 *
 * @return void
 */
void StationHub::addToStation(MiningTruck* truck)
{
	// Add the truck to the next available station or station queue
	stations_a[nextAvailableStation].addTruck(truck);

	// Store Station index
	truck->unload_station = nextAvailableStation;

	// Update which Station should receive the next Mining Truck
	updateNextAvailable();
}


/**
 * Remove the provided MiningTruck from the Station it was unloading at
 *
 * @return void
 */
void StationHub::removeFromStation(MiningTruck* truck)
{
	// Check if the truck is unloading, if not we cant remove it from the queue
	if(truck->state != TruckState::eUnloading) return;

	// Remove the MiningTruck from the Station at the index stored in the MiningTruck::unload_station variable
	stations_a[truck->unload_station].removeTruck();

	// Calculate the amount of time the Truck will be out mining
	truck->computeMineTime();

	// Update which Station should receive the next Mining Truck
	updateNextAvailable();
}


/**
 * Generate a report showing performance and efficiency statistics for each MiningTruck and Station
 *
 * @return void
 */
void StationHub::generateReport()
{
	printf("Generate Reports...\n\n");

	for(int i = 0; i < trucks_a.size(); i++)
	{
		printf("Mining Truck %03i Report:\n", i);
		trucks_a[i].reportStats();
	}

	printf("\n");

	for(int s = 0; s < stations_a.size(); s++)
	{
		printf("Station %03i Report:\n", s);
		stations_a[s].reportStats();
	}
}


/**
 * Add a MiningTruck to the Station
 *
 * @param A pointer to the truck object that has "returned" to the station
 *
 * @return void
 */
void Station::addTruck(MiningTruck* truck)
{
	// Update the trucks state
	truck->state = unloadQueue.empty() ? TruckState::eUnloading : TruckState::eQueued;

	// Add the mining truck to the queue
	unloadQueue.push(truck);

	// Update number of trucks unloaded at station
	numMiningTrucks++;

	// Update the max size of the queue if its increased
	if(unloadQueue.size() > maxQueue) maxQueue = unloadQueue.size();

	// Update the trucks work time
	truck->work_time = unload_time;
}


/**
 * Remove a MiningTruck from the Station
 *
 * @return void
 */
void Station::removeTruck()
{
	// Remove the MiningTruck from the front of the queue as long as the queue is not empty
	if(!unloadQueue.empty()) unloadQueue.pop();

	// Check if the queue is empty
	if(!unloadQueue.empty())
	{
		// Update the state of the new Mining Truck at the front of the queue
		unloadQueue.front()->state = TruckState::eUnloading;
	}
}


/**
 * Update the availability weight for the Station
 *
 * The availability weight is calculated by getting the size of the unloadQueue. The lower
 * the weight, the more available the Station is for receiving MiningTrucks
 *
 * @return void
 */
void Station::updateAvailability()
{
	// Note: Could improve this by taking the remaining time the truck at the front of the queue into account
	availabilityWeight = unloadQueue.size();
}


/**
 * Print out statistics about the Station
 *
 * @return void
 */
void Station::reportStats()
{
	printf("    Unloading Time          : %4i minutes\n", unload_time);
	printf("    Number of Mining Trucks : %4i\n", numMiningTrucks);
	printf("    Maximum Size of Queue   : %4i\n", maxQueue);
}

