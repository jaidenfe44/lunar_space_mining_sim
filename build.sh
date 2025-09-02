#!/bin/bash


build_target='' # Default to empty (no target)

include="-Isrc/ -Ilib/ -Itst/"


build_sim() {

	# TODO
	echo "Building Sim"

	if [ -d "./bin" ]; then
		rm -rf bin/*
	else
		mkdir bin
	fi

	clang++ src/main.cpp -o bin/sim
}

build_test() {

	# TODO
	echo "TODO: Build Test Suite"
}

usage() {
	printf "Usage:\n"
	printf "   ./build.sh -t <target> : Build for one of the following targets:\n"
	printf "                      sim : Build the mining sim\n"
	printf "                     test : Build the mining sim test suite\n"
}


while getopts 't:' flag; do
  case "${flag}" in
	t) build_target="${OPTARG}" ;;
    *) usage
       exit 1 ;;
  esac
done

if [[ "$build_target" = 'test' ]]; then
	build_test
elif [[ "$build_target" = 'sim' ]]; then
	build_sim
else
	usage
fi
