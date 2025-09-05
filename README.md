# Lunar Space Mining Simulation

## How to Build/Run:

A `build.sh` script is supplied in the top most directory. To build and execute the simulator, run `./build.sh -t sim`. This builds the simulator and runs the simulator executable. The simulator executable is stored at `build/sim`. To run the test suite, run `./build.sh -t test`. Similarly, this builds and runs the test suite executable. The test suite executable is stored at `build/test`. By default the number of stations is `4` and the number of mining trucks is `10`. To modify these values add the following flags:

```
    -s <stationNum>, where <stationNum> is an integer greater than 0
    -m <miningTruckNum>, where <miningTruckNum> is an integer greater than 0
```

In addition, to access the help menu, simply add the `-h` flag.

---

## Objective:

You are tasked with developing a simulation for a lunar Helium-3 space mining operation. This simulation will manage and track the efficiency of mining trucks and unload stations over a continuous 72-hour operation.

## Key Components:
 - Mining Trucks: These vehicles perform the actual mining tasks.
 - Mining Sites: Locations on the moon where the trucks extract Helium-3. Assume an infinite number of sites, ensuring trucks always have access to mine without waiting.
 - Mining Unload Stations: Designated stations where trucks unload the mined Helium-3. Each station can handle one truck at a time.

## Operation Details:
 - There are (n) mining trucks and (m) mining unload stations.
 - Mining trucks can spend a random duration between 1 to 5 hours mining at the sites.
 - It takes a mining truck 30 minutes to travel between a mining site and an unload station.
   - Assume all trucks are empty at a mining site when the simulation starts.
 - Unloading the mined Helium-3 at a station takes 5 minutes.
 - Trucks are assigned to the first available unload station. If all stations are occupied, trucks queue at the station with the shortest wait time and remain in their chosen queue.

## Simulation Requirements:
 - The simulation must be configurable to accommodate various numbers of mining trucks (n) and unload stations (m).
 - Calculate and report statistics for the performance and efficiency of each mining truck and unload station.
 - The simulation represents 72 hours of non-stop mining and must execute faster than real-time to provide timely analysis.

## Language and programming paradigms:
Please implement this project in C++. Please leverage OOP where it is appropriate.


## Goal of the exercise:
The primary goal of this challenge is to demonstrate your professionalism as a software engineer. This process is designed to mimic a real-world scenario, including design, implementation, and design review. You will be evaluated based on various skills, including:

  1. Communication: Clear and concise explanations of your code and design.
  2. Documentation: Providing well-documented code and explanations.
  3. Code Cleanliness: Writing clean and organized code.
  4. Code Deployment: Demonstrating your ability to deploy and manage code.
  5. Testing: Implementing appropriate testing strategies.

## Things to avoid:
It is not the objective to spend an excessive amount of time on this challenge or create a fully
developed system. Feel free to include pseudocode (in comments) to explain what you would do if
given more time or resources. The focus is on showcasing your problem-solving and coding skills
within a reasonable time frame.

---

<br><br>

# Design Process

This section is used as a scratch pad space for notes and design considerations to describe my though process when approaching the exercise.

## Main Loop Design

The sim main loop will be in charge of system count and stepping through the simulator. The `system count` represents minutes the simulation is running. In this approach the sim runtime is 4320 minutes (72 hours). The `main.cpp` file implements the system runtime loop (in minutes) and calls the `StationHub::step()` function for every simulation minute. Everything within the flow diagram is contained within this step function, with the exception of report generation and system count handling.

The following is a flow diagram representing the design of the `main loop` and `StationHub::step()` functionality.

![lunar_mining_sim_main_flow_diagram-4](https://github.com/user-attachments/assets/42dd2a5d-0845-4a7f-a292-cf8ba6b2d442)

## StationHub/Station Design

The number of stations is specified in the System.hpp file as `numStations`. All of the Stations are contianed within a single `StationHub` object, which handles the queue logic and simulation step functinality. The queue logic is implemented in two main functions: `StationHub::addToStation()` and `StationHub::removeFromStation()`.

The following diagram shows the flow of the `StationHub::addToStation()` and `Station::addTruck()` functions:

![lunar_mining_sim_StationHub_addToStation_flow_diagram-2](https://github.com/user-attachments/assets/d8f2a1aa-a9f8-4076-ae37-d859196d95c7)

Here we see that the `StationHub` keeps track of the next available station in a variable called `StationHub::nextAvailableStation` which contains the index into the station array.

The following diagram shows the flow of the `StationHub::removeFromStation()` and `Station::removeTruck()` functions:

![lunar_mining_sim_removeTruckFromStation_flow_diagram-2](https://github.com/user-attachments/assets/03ce316e-d4b5-433b-9e00-2e3fbefa51c5)


Here we leverage the stored `MiningTruck::unload_station` variable that contains the index of the Station that particular truck is unloading at. This allows the `StationHub` to index directly into the Station array and call `Station::removeTruck()` directly on the correct Station object. Once the `MiningTruck` is removed from the queue, we check if the queue is empty. If it is not empty, then we need to update the state of the `MiningTruck` now at the front of the queue to `eUnloading` instead of `eQueued` so that the `StationHub::step()` function decrements the `MiningTruck::work_time` (down counter representing how many steps to "work" and take up resources until it can switch states again) rather than incrementing the `MiningTruck::wait_time` (up counter representing the amount of time spent in a queue waiting for available resources).


## Mining Truck Design

The mining truck and mining site requirements in the objective were combined into a single object: MiningTruck. The only job of the MiningTruck object is to store telemetry, state, and compute "work time". In this case, state is `mining`, `unloading`, or `queued`. `Work time` is used for both the amount of time the truck is out mining and the aount of time it is unloading at a station. The state is used to destinquish between those two cases. The MiningTruck only has one function to compute the mine time. The `work time` is updated by a Station object when the truck is unloading.

The following shows the simple `MiningTruck::computeMineTime()` function:

![lunar_mining_sim_computeMineTime_flow_diagram-2](https://github.com/user-attachments/assets/c4cdfb0e-77bc-485e-b73c-e819ef374d9c)

In this flow diagram, there are only 3 variables used to calculate the mining time: `mineTimeUpperBound`, `mineTimeOffset`, and a `random number`. The random number is generated by the `rand()` function. The `mineTimeUpperBound` is a system-level constant defined as the difference between the `lowerMineTimeBoundHours` and `upperMineTimeBoundHours` multiplied by `60`. These two variables are defined in the objective as the random mine time between 1 (lower mine time) and 5 (upper mine time) hours. We multiple by 60 to get that shifted upper bound in minutes. The `mineTimeOffset` is defined as the `lowerMineTimeBoundHours` * `60` (to get the lower bound in minutes) plus the travel time to and from a mining site.

---

# Execution Results

```
Building Sim
Generate Reports...

Mining Truck 000 Report:
    Time Spent Waiting   :     0 minutes
    Time Spent Mining    :  3131 minutes
    Time Spent Traveling :  1140 minutes
    # of Loads Delivered :    18
Mining Truck 001 Report:
    Time Spent Waiting   :     2 minutes
    Time Spent Mining    :  3224 minutes
    Time Spent Traveling :  1200 minutes
    # of Loads Delivered :    19
Mining Truck 002 Report:
    Time Spent Waiting   :     0 minutes
    Time Spent Mining    :  3334 minutes
    Time Spent Traveling :  1140 minutes
    # of Loads Delivered :    18
Mining Truck 003 Report:
    Time Spent Waiting   :     0 minutes
    Time Spent Mining    :  3344 minutes
    Time Spent Traveling :  1080 minutes
    # of Loads Delivered :    17
Mining Truck 004 Report:
    Time Spent Waiting   :     3 minutes
    Time Spent Mining    :  3227 minutes
    Time Spent Traveling :  1080 minutes
    # of Loads Delivered :    17
Mining Truck 005 Report:
    Time Spent Waiting   :     2 minutes
    Time Spent Mining    :  3148 minutes
    Time Spent Traveling :  1200 minutes
    # of Loads Delivered :    19
Mining Truck 006 Report:
    Time Spent Waiting   :     3 minutes
    Time Spent Mining    :  3177 minutes
    Time Spent Traveling :  1080 minutes
    # of Loads Delivered :    17
Mining Truck 007 Report:
    Time Spent Waiting   :     6 minutes
    Time Spent Mining    :  3199 minutes
    Time Spent Traveling :  1140 minutes
    # of Loads Delivered :    18
Mining Truck 008 Report:
    Time Spent Waiting   :     0 minutes
    Time Spent Mining    :  3402 minutes
    Time Spent Traveling :  1080 minutes
    # of Loads Delivered :    17
Mining Truck 009 Report:
    Time Spent Waiting   :     3 minutes
    Time Spent Mining    :  3295 minutes
    Time Spent Traveling :  1140 minutes
    # of Loads Delivered :    18

Station 000 Report:
    Unloading Time          :    5 minutes
    Number of Mining Trucks :   43
    Maximum Size of Queue   :    1
Station 001 Report:
    Unloading Time          :    5 minutes
    Number of Mining Trucks :   42
    Maximum Size of Queue   :    1
Station 002 Report:
    Unloading Time          :    5 minutes
    Number of Mining Trucks :   42
    Maximum Size of Queue   :    1
Station 003 Report:
    Unloading Time          :    5 minutes
    Number of Mining Trucks :   51
    Maximum Size of Queue   :    2
```

<br><br>

# Test Suite Results

```
Build Test Suite
Running Test Suite...
    Test Case: MiningTruck::computeMineTime     Passed
    Test Case: Station::addTruck()              Passed
    Test Case: Station::removeTruck()           Passed
    Test Case: Station::updateAvailability      Passed
    Test Case: StationHub::addToStation()       Passed
    Test Case: StationHub::removeFromStation()  Passed
    Test Case: StationHub::step()               Passed

Test Report
    Passed: 7
    Failed: 0

    Runtime: 0 ms
```
