#include "MiningTruck.hpp"


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
		Station() { /* TODO */ };

		void addTruck(MiningTruck* truck);

	private:
		// Time it takes to unload a truck, in minutes
		unsigned int unload_time = 5; 
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
	// TODO
}

