#ifndef TEST_CASE_STATION_HUB_HPP
#define TEST_CASE_STATION_HUB_HPP

#include "StationHub.hpp"
#include "MiningTruck.hpp"
#include "TestCase.hpp"


class TestCase_StationHub: public TestCase, StationHub
{

	public:
		// Test Case execution function
		void run(unsigned int &pass, unsigned int &fail) override
		{
			TC_addToStation()      ? pass++ : fail++;
        	TC_removeFromStation() ? pass++ : fail++;
        	TC_step()              ? pass++ : fail++;
		}

		// Test Cases
		bool TC_addToStation();
        bool TC_removeFromStation();
        bool TC_step();

	private:

		void cleanup() override;

		MiningTruck truck;
		MiningTruck truckTwo;
};

#endif // TEST_CASE_STATION_HUB_HPP
