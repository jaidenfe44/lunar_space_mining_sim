
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
		MiningTruck() { /* TODO */ };

		unsigned int computeMineTime();
		void incrementWaitTime();

		// Time in queue at unload station
		unsigned int queue_time = 0;

	private:
		// Travel time between an unload station and mining site, in minutes
		unsigned int travelTime = 30; 
};


/**
 * Calculate the time it took for a truck object to get to a mine, mine Helium-3, and
 *    return to an unloading station
 *
 * @return The number of minutes it took the truck to mine and get back to the unloading station
 */
unsigned int MiningTruck::computeMineTime(){
	// TODO: calculate the time it took the truck to get to the time, mine, and return
	return 60;
}

