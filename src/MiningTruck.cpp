#include "MiningTruck.hpp"


/**
 * Calculate the time it took for a truck object to get to a mine, mine Helium-3, and
 *    return to an unloading station
 *
 * @return void
 */
void MiningTruck::computeMineTime(){
	// Switch state to mining
	state = TruckState::eMining;

  	// TODO: calculate the time it took the truck to get to the time, mine, and return
  	work_time = travel_time * 2;
}
