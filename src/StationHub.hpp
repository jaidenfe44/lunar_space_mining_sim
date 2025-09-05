#ifndef STATION_HUB_HPP
#define STATION_HUB_HPP

#include "System.hpp"
#include "MiningTruck.hpp"

#include <array>
#include <queue>

/**
 * Station : TODO
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

		// TODO
		void addTruck(MiningTruck* truck);

		// TODO
		void removeTruck();

		// TODO
		void updateAvailability();

	private:
		// Time it takes to unload a truck, in minutes
		unsigned int unload_time = unloadTime;

		// TODO
		int availabilityWeight = 0;

		// TODO
		std::queue<MiningTruck*> unloadQueue;

		friend class StationHub;

	#ifdef TEST_SUITE
		friend class TestCase_Station;
		friend class TestCase_StationHub;
	#endif
};



/**
 * TODO
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

		std::array<Station, numStations> stations_a;
		std::array<MiningTruck, numTrucks> trucks_a;

		unsigned int nextAvailableStation = 0;

		// Figure out what the next available station is
		void updateNextAvailable();

	#ifdef TEST_SUITE
		friend class TestCase_StationHub;
	#endif
};


#endif // STATION_HUB_HPP
