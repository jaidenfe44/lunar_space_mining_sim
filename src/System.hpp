#ifndef SYSTEM_HPP
#define SYSTEM_HPP

// The number of hours to run the sim
constexpr unsigned int simExecution = 72;

// The sim exeuction time in minutes (system ticks for this design)
constexpr unsigned int simRuntime = 60 * simExecution;

// The number of trucks that are available for mining
constexpr unsigned int numTrucks = 10;

// The number of unloading stations there are
constexpr unsigned int numStations = 4;

#endif // SYSTEM_HPP
