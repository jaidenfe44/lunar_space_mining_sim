#include "MiningTruck.hpp"
#include "System.hpp"

#include <cstdio>

/**
 * Calculate the time it took for a truck object to get to a mine, mine Helium-3, and
 *    return to an unloading station
 *
 * @return void
 */
void MiningTruck::computeMineTime()
{
	// Switch state to mining
	state = TruckState::eMining;

  	// Calculate the time it took the truck to get to the mining site, mine helium-3, and return to the station hub
	work_time = (rand() % mineTimeUpperBound) + mineTimeOffset;

	// Update lifetime work minutes
	workLifetime += work_time;

	// Update the amount of time the truck has spent traveling
	timeTraveling += miningSiteTravelTime * 2;

	// Update the number of Helium-3 truck loads that have been delivered to a Station
	// Note: This value is 1 more than the actual number of loads delivered, so 1 must be subtracted from it when reporting
	loadsDelivered++;
}


/**
 * Prints out MiningTruck statistics
 *
 * @return void
 */
void MiningTruck::reportStats()
{
	printf("    Time Spent Waiting   : %5i minutes\n", wait_time);
	printf("    Time Spent Mining    : %5i minutes\n", workLifetime - timeTraveling);
	printf("    Time Spent Traveling : %5i minutes\n", timeTraveling);
	printf("    # of Loads Delivered : %5i\n", loadsDelivered - 1); // subtract by 1 to account for the last load that didnt end up being delivered within the sim timeframe
}
