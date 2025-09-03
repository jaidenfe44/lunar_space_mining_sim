#include "StationHub.hpp"

#include <cstdio>



/**
 * TODO
 */
void StationHub::step()
{
	// Check if trucks are done with their current task
	for(int i = 0; i < numTrucks; i++)
	{
		MiningTruck* idx = &trucks_a[i];

		// If the truck is waiting in a queue, increment the wait timer, otherwise decrement the work timer
		idx->state == TruckState::eQueued ? idx->wait_time++ : idx->work_time--;

		if(idx->work_time == 0)
		{
			// Check if truck was mining
			switch(idx->state)
			{
				case TruckState::eMining:
					// Finished Mining, add to the next available Station or Station Queue
					addToStation(idx);
					break;

				case TruckState::eUnloading:
					// Truck finished unloading
					removeFromStation(idx);
					break;

				default:
					break;
			}
		}
	}
}


/**
 * TODO
 */
void StationHub::addToStation(MiningTruck* truck)
{
	// Add the truck to the next available station or station queue
	stations_a[nextAvailableStation].addTruck(truck);



	// TODO

	// TODO
	printf("Added truck to station\n");
}


/**
 * TODO
 */
void StationHub::removeFromStation(MiningTruck* truck)
{
	// TODO: Need to be aware of the next truck in the queue and its state
	// TODO
}


/**
 * TODO
 */
void StationHub::generateReport()
{
	// TODO
}


/**
 * Add a truck to the station
 *
 * @param A pointer to the truck object that has "returned" to the station
 *
 * @return void
 */
void Station::addTruck(MiningTruck* truck)
{
	// Update the trucks state
	truck->state = unloadQueue.empty() ? TruckState::eUnloading : TruckState::eQueued;

	// Update the trucks work time
	truck->work_time = unload_time;

	// Add the mining truck to the queue
	unloadQueue.push(truck);

	// TODO
}
