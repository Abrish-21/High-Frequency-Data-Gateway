cmake_minimum_required(VERSION 3.10)
project(HighFrequencyDataGateway)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define project include path
include_directories(include)

# Add the main application executable
add_executable(data_gateway 
    src/main.cpp 
    src/MessageQueue.cpp 
    src/MessageProcessor.cpp
)

# --- Configuration for Gtest (Test-Driven Approach) ---

# Enable testing with CTest
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Add the test executable
add_executable(run_tests 
    tests/MessageQueue_test.cpp 
    src/MessageQueue.cpp
)

# Link GTest libraries using modern targets and link to pthreads for concurrency
target_link_libraries(run_tests 
    GTest::GTest 
    GTest::Main 
    pthread
)

# Add test to CTest
add_test(NAME MessageQueueTests COMMAND run_tests)
