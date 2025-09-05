#ifndef SYSTEM_HPP
#define SYSTEM_HPP

// The number of hours to run the sim
constexpr unsigned int simExecutionHours = 72;

// The sim exeuction time in minutes (system ticks for this design)
constexpr unsigned int simRuntime = 60 * simExecutionHours;

// The number of mining trucks
#ifdef MINING_TRUCK_NUM
constexpr unsigned int numTrucks = MINING_TRUCK_NUM;
#else
constexpr unsigned int numTrucks = 10;
#endif

// The number of unloading stations
// Note: For the test suite to work we need at least 3 Stations
#ifdef STATION_NUM
constexpr unsigned int numStations = STATION_NUM;
#else
constexpr unsigned int numStations = 4;
#endif

// MineTruck Travel Time to Mining Site
constexpr unsigned int miningSiteTravelTime = 30;

// The upper boundary of the time it takes to mine Helium-3, in Hours
constexpr unsigned int mineTimeUpperBoundHours = 5; 

// The lower boundary of the time it takes to mine Helium-3, in Hours
constexpr unsigned int mineTimeLowerBoundHours = 1; 

// The upper boundary of the time it takes to mine Helium-3, in minutes
constexpr unsigned int mineTimeUpperBound = (mineTimeUpperBoundHours - mineTimeLowerBoundHours) * 60;

// The mine time calculation offset (also the lower bound in minutes
//			+ travel time to and from the mine site), in minutes
constexpr unsigned int mineTimeOffset = ((mineTimeLowerBoundHours * 60) + (miningSiteTravelTime * 2));

// The amount of time it takes a MiningTruck at a Station to unload
constexpr unsigned int unloadTime = 5;



#endif // SYSTEM_HPP
