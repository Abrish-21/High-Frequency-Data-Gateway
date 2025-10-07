#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Clean and create build directory
echo "--- Configuring Build ---"
rm -rf build
mkdir -p build
cd build

# Run CMake to configure the project
cmake ..

# Build the project (main application and test executable)
echo "--- Building Project ---"
make

# Run unit tests (TDD implementation proof)
echo "--- Running Unit Tests (Gtest) ---"
./run_tests

# Run the main application simulation
echo "--- Running Data Gateway Simulation ---"
./data_gateway

echo "--- Script Finished Successfully ---"
