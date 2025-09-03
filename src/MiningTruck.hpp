#ifndef MINING_TRUCK_HPP
#define MINING_TRUCK_HPP

#include <cstdlib>
#include <ctime>

/**
 * TODO
 */
enum class TruckState
{
    eMining,
    eQueued,
    eUnloading
};


/**
 * Mining Truck Requirements:
 *   - Mining trucks can spend a random duration between 1 to 5 hours mining at a site
 *   - It takes a mining truck 30 minutes to travel between a mining site and an unload station
 *   - Assume all trucks are empty at a mining site when the simulation starts
 *	 - Calculate and report statistics for the performance and efficiency of each mining truck
 */
class MiningTruck
{
	public:
		MiningTruck()
		{
			// Seed random number generater based on system time for more accurate randomization
			srand(time(0));
		};

		// TODO
		void computeMineTime();

		// Time unload at station or time away mining
		unsigned int work_time = 0;

		// Time in queue at unload station
		unsigned int wait_time = 0;

		// State showing when the truck is mining, unloaded, and queued to unload
		TruckState state = TruckState::eMining;

		// When unloading, this holds the index of the Station within the StationHub where the
		//		MiningTruck is unloading
		unsigned int unload_station = 0;

	private:
		// Travel time between an unload station and mining site, in minutes
		unsigned int travel_time = 30; 
};


#endif // MINING_TRUCK_HPP
