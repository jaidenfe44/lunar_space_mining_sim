#ifndef TEST_CASE_STATION_HPP
#define TEST_CASE_STATION_HPP

#include "StationHub.hpp"
#include "MiningTruck.hpp"
#include "TestCase.hpp"


class TestCase_Station: public TestCase, Station
{

	public:
		void cleanup() override;

		// Test Case execution function
		void run(unsigned int &pass, unsigned int &fail) override
		{
			TC_addTruck()           ? pass++ : fail++;
        	TC_removeTruck()        ? pass++ : fail++;
        	TC_updateAvailability() ? pass++ : fail++;
		}

		// Test Cases
		bool TC_addTruck();
        bool TC_removeTruck();
        bool TC_updateAvailability();

	private:
		MiningTruck truck;
		MiningTruck truckTwo;
};

#endif // TEST_CASE_STATION_HPP
