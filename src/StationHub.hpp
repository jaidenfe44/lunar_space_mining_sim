#ifndef STATION_HUB_HPP
#define STATION_HUB_HPP

#include "System.hpp"
#include "MiningTruck.hpp"

#include <array>
#include <queue>

/**
 * Station : This class defines a Station where a MiningTruck unloads Helium-3 or queues to unload.
 *
 * Requirements:
 *   - Unloading the mined Helium-3 at a station takes 5 minutes
 *   - Trucks are assigned to the first available unload station. If all stations are occupied, trucks queue at the station with the shortest wait time and remain in their chosen queue
 *   - Each station can handle one truck at a time
 *   - Trucks are assigned to the first available unload station. If all stations are occupied, trucks queue at the station with the shortest wait time and remain in their chosen queue
 *	 - Calculate and report statistics for the performance and efficiency of each unload station
 */
class Station
{
	public:
		Station() {};

		// Add a truck to this stations queue
		void addTruck(MiningTruck* truck);

		// Remove a truck from this stations queue, meaning the truck has finished unloading
		void removeTruck();

		// Update the availability weight used in deciding which station the next truck should go to
		void updateAvailability();

		// Print out statistics about the station
		void reportStats();

	private:
		// Time it takes to unload a truck, in minutes
		unsigned int unload_time = unloadTime;

		// Number of MiningTrucks unloaded
		unsigned int numMiningTrucks = 0;

		// Max number of queued trucks
		unsigned int maxQueue = 0;

		// TODO: average number of queued trucks: would add this calculation in, but would take more work than I have time for at the moment

		// TODO: Would add additional telemetry points to properly track efficiency and statistics about the stations 

		// The availability score used to calculate which station the next truck should go to
		int availabilityWeight = 0;

		// The queue to unload at the station. Front of the queue is considered "actively unloading"
		std::queue<MiningTruck*> unloadQueue;

		friend class StationHub;

	#ifdef TEST_SUITE
		friend class TestCase_Station;
		friend class TestCase_StationHub;
	#endif
};



/**
 * This class contains all Station and MiningTruck objects and is in charge of progressing through the simulation minutes by minute
 */
class StationHub
{
	public:
		// ensure singleton for StationHub object
		static StationHub& getInstance() {
			static StationHub inst;
			return inst;
		};
		StationHub(const StationHub&) = delete;
    	StationHub& operator=(const StationHub&) = delete;

		// process one system tick for the sim
		void step();

		// add a truck to the next available station or station queue
		void addToStation(MiningTruck* truck);

		// remove a truck from the station once its done unloading and update the queue
		void removeFromStation(MiningTruck* truck);

		// create report(s) for the system
		void generateReport();

	private:
		StationHub()
		{
			// Initialize all trucks as actively mining
			for(int i = 0; i < trucks_a.size(); i++)
			{
				trucks_a[i].computeMineTime();
			}
		};

		// An array containing all Station objects
		std::array<Station, numStations> stations_a;

		// An array containing all MiningTruck objects
		std::array<MiningTruck, numTrucks> trucks_a;

		// A variable holding the index into stations_a of the next available Station a MiningTruck will go to
		unsigned int nextAvailableStation = 0;

		// Figure out what the next available station is
		void updateNextAvailable();

	#ifdef TEST_SUITE
		friend class TestCase_StationHub;
	#endif
};


#endif // STATION_HUB_HPP
