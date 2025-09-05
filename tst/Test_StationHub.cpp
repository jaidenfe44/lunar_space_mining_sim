#include "TestSuite.hpp"
#include "StationHub.hp" 

void TestSuite::StationHub_updateNextAvailable()
{
	stationHub.nextAvailableStation = 0;
	for(int nextVal = 1; nextVal < (numStations-1); nextVal++)
	{
		stationHub.updateNextAvailable();
		assert(stationHub.nextAvailableStation == nextVal);
	}

	stationHub.updateNextAvailable();
	assert(stationHub.nextAvailableStation == 0);

	stationHub.updateNextAvailable();
	assert(stationHub.nextAvailableStation == 1);
}
