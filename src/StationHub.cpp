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
 * Update the index to the next available station
 *
 * @return void
 */
void StationHub::updateNextAvailable()
{
	// Note: Currently just implementing round-robin availability
	//      Future improvements could be made by using a weighted
	//		optimization on queue size or time used or "helium mined"
	//		as the weighting factor(s)

	nextAvailableStation++;
	nextAvailableStation %= numStations;
}


/**
 * Add a MiningTruck to the next available Station
 *
 * @param A pointer to the truck object that is headed to the next
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

	// Pick which Station should receive the next Mining Truck
	updateNextAvailable();
}


/**
 * TODO
 */
void StationHub::removeFromStation(MiningTruck* truck)
{
	stations_a[truck->unload_station].removeTruck();

	truck->computeMineTime();
}


/**
 * TODO
 */
void StationHub::generateReport()
{
	// TODO
	printf("Generate Reports...\n");
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

	// Add the mining truck to the queue
	unloadQueue.push(truck);

	// Update the trucks work time
	truck->work_time = unload_time;
}


/**
 * TODO
 */
void Station::removeTruck()
{
	// Remove the truck from the front of the queue
	unloadQueue.pop();

	// Check if the queue is empty
	if(!unloadQueue.empty())
	{
		// Update the state of the new Mining Truck at the front of the queue
		unloadQueue.front()->state = TruckState::eUnloading;
	}
}


