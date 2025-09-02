#include "MiningTruck.hpp"
#include "Station.hpp"

#include <cstdio>

/**
 * Requirements:
 *   - There are (n) mining trucks and (m) mining unload stations
 *   - Calculate and report statistics for the performance and efficiency of each mining truck and unload station
 *   - The simulation represents 72 hours of non-stop mining and must execute faster than real-time to provide timely analysis
 */
int main() {
	// TODO: Define the main simulation flow here

	auto truck = MiningTruck();

	unsigned int t = truck.computeMineTime();
	printf("Truck Mine Time: %i\n", t);

	auto station = Station();
	station.addTruck(&truck);
}
