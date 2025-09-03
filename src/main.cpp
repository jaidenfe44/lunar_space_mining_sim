#include "System.hpp"
#include "StationHub.hpp"


/**
 * Requirements:
 *   - There are (n) mining trucks and (m) mining unload stations
 *   - Calculate and report statistics for the performance and efficiency of each mining truck and unload station
 *   - The simulation represents 72 hours of non-stop mining and must execute faster than real-time to provide timely analysis
 */
int main() {
	// Initialize System Ticks (minutes)
	unsigned int sysCount = 0;

	// Initialize the Station Hub object
	StationHub &stationHub = StationHub::getInstance();

	// Main Loop
	while(sysCount < simRuntime)
	{
		// Step through one sim minute
		stationHub.step();

		sysCount++;
	}

	// Generate the simulation report
	stationHub.generateReport();

	return 0;
}
