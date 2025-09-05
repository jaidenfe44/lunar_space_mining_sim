
#include <chrono>

#include "TestCase_MiningTruck.hpp"
#include "TestCase_Station.hpp"
#include "TestCase_StationHub.hpp"

class TestSuite
{
	public:
		static TestSuite& getInstance()
		{
			static TestSuite inst;
			return inst;
		}

		void run();

		void report();


	private:
		unsigned int passed = 0;
		unsigned int failed = 0;
		std::chrono::milliseconds execTime;

		// Test Cases
		TestCase_MiningTruck tcMiningTruck;
		TestCase_Station tcStation;
		TestCase_StationHub tcStationHub;
};
