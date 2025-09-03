# Lunar Space Mining Simulation

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

<br><br>

# Design Process

This section is used as a scratch pad space for notes and design considerations to describe my though process when approaching the exercise.

## Main Loop Design

The sim main loop will be in charge of system count and stepping through the simulator. The `system count` represents minutes the simulation is running. In this approach the sim runtime is 4320 minutes (72 hours). The `main.cpp` file implements the system runtime loop (in minutes) and calls the `StationHub::step()` function for every simulation minute. Everything within the flow diagram is contained within this step function, with the exception of report generation and system count handling.

The following is a flow diagram representing the design of the main loop and step functionality.

![lunar_mining_sim_main_flow_diagram](https://github.com/user-attachments/assets/5aed72e4-8ebd-458f-b218-3b393e91a1cf)

## StationHub/Station Design

The number of stations is specified in the System.hpp file as `numStations`. All of the Stations are contianed within a single `StationHub` object, which handles the queue logic and simulation step functinality. The queue logic is implemented in two main functions: `StationHub::addToStation()` and `StationHub::removeFromStation()`.

The following diagram shows the flow of the `StationHub::addToStation()` and `Station::addTruck()` functions:

![lunar_mining_sim_StationHub_addToStation_flow_diagram-2](https://github.com/user-attachments/assets/d8f2a1aa-a9f8-4076-ae37-d859196d95c7)

Here we see that the `StationHub` keeps track of the next available station in a variable called `StationHub::nextAvailableStation` which contains the index into the station array.

The following diagram shows the flow of the `StationHub::removeFromStation()` and `Station::removeTruck()` functions:

![lunar_mining_sim_removeTruckFromStation_flow_diagram](https://github.com/user-attachments/assets/38325b97-02ab-4114-aff8-0d649d26572d)

Here we leverage the stored `MiningTruck::unload_station` variable that contains the index of the Station that particular truck is unloading at. This allows the `StationHub` to index directly into the Station array and call `Station::removeTruck()` directly on the correct Station object. Once the `MiningTruck` is removed from the queue, we check if the queue is empty. If it is not empty, then we need to update the state of the `MiningTruck` now at the front of the queue to `eUnloading` instead of `eQueued` so that the `StationHub::step()` function decrements the `MiningTruck::work_time` (down counter representing how many steps to "work" and take up resources until it can switch states again) rather than incrementing the `MiningTruck::wait_time` (up counter representing the amount of time spent in a queue waiting for available resources).


## Mining Truck Design

TODO

