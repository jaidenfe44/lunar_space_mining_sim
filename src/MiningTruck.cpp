#include "MiningTruck.hpp"
#include "System.hpp"

/**
 * Calculate the time it took for a truck object to get to a mine, mine Helium-3, and
 *    return to an unloading station
 *
 * @return void
 */
void MiningTruck::computeMineTime(){
	// Switch state to mining
	state = TruckState::eMining;

  	// Calculate the time it took the truck to get to the mining site, mine helium-3, and return to the station hub
	work_time = (rand() % mineTimeUpperBound) + mineTimeOffset;
}
