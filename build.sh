#!/bin/bash


build_target='' # Default to empty (no target)
stationNum=''
miningTruckNum=''
verbose=''


build_sim() {

	echo "Building Sim"

	if [ -d "./bin" ]; then
		rm -rf bin/sim
	else
		mkdir bin
	fi

	defs=""

	if ! [[ -z "$stationNum" ]]; then
		defs+=" -D STATION_NUM=$stationNum"
	fi

	if ! [[ -z "$miningTruckNum" ]]; then
		defs+=" -D MINING_TRUCK_NUM=$miningTruckNum"
	fi

	clang++ $defs src/MiningTruck.cpp src/StationHub.cpp src/main.cpp -o bin/sim $verbose

	# Run the sim
	./bin/sim
}

build_test() {

	echo "Build Test Suite"

	if [ -d "./bin" ]; then
		rm -rf bin/test
	else
		mkdir bin
	fi

	incList="-Isrc/
			 -Itst/"

	srcList="src/MiningTruck.cpp
		src/StationHub.cpp
		tst/TestSuite.cpp
		tst/TestCase_MiningTruck.cpp
		tst/TestCase_Station.cpp
		tst/TestCase_StationHub.cpp
		tst/main.cpp "

	defs="-D TEST_SUITE"

	#clang++ src/MiningTruck.cpp src/StationHub.cpp tst/TestSuite.cpp tst/main.cpp -o bin/test $verbose
	clang++ $incList $srcList $defs -o bin/test $verbose

	# Run the test suite
	./bin/test
}

usage() {
	echo "Usage: ./build.sh -t <target> [-s <stationNum>] [-m <miningTruckNum>] [-v] [-h]"
	echo "    <target>:"
	echo "          sim - Build and run the mining sim"
	echo "         test - Build and run the mining sim test suite"
	echo "    Options:"
	echo "         -s <stationNum>     - Update the number of Stations used in the sim,"
    echo "                               where <stationNum> is an integer greater than 0"
	echo "         -m <miningTruckNum> - Update the number of MiningTrucks in the sim,"
	echo "                               where <miningTruckNum> is an interger greater than 0"
	echo "         -v                  - Build with verbose error messages"
    echo "         -h                  - Display help message"
}


while getopts 't:vs:m:h' flag; do
  case "${flag}" in
	t) build_target="${OPTARG}" ;;
	s) stationNum="${OPTARG}" ;;
	m) miningTruckNum="${OPTARG}" ;;
	v) verbose='-v' ;;
	h) usage
	   exit 1 ;;
    *) usage
       exit 1 ;;
  esac
done

if ! [[ -z "$stationNum" ]]; then
	if ! [[ "$stationNum" =~ ^[0-9]+$ ]]; then
		echo "Please enter a Station Number integer that is 1 or more"
		usage
		exit 1
	elif [[ "$stationNum" == "0" ]]; then
		echo "Please enter a Station Number integer that is 1 or more"
		usage
		exit 1
	fi
fi

if ! [[ -z "$miningTruckNum" ]]; then
	if ! [[ "$miningTruckNum" =~ ^[0-9]+$ ]]; then
		echo "Please enter a Mining Truck Number integer that is 1 or more"
		usage
		exit 1
	elif [[ "$miningTruckNum" == "0" ]]; then
		echo "Please enter a Mining Truck Number integer that is 1 or more"
		usage
		exit 1
	fi
fi

if [[ "$build_target" = 'test' ]]; then
	build_test
elif [[ "$build_target" = 'sim' ]]; then
	build_sim
else
	usage
fi
