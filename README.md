High-Frequency Data Gateway
This project is a high-performance, low-latency C++ backend service designed to handle real-time market data streams. It's engineered with modern C++ (C++17) and follows a test-driven development approach for critical components.

Project Structure
.
├── CMakeLists.txt
├── README.md
├── include
│   ├── IMessageProcessor.h
│   ├── Message.h
│   ├── MessageProcessor.h
│   └── MessageQueue.h
├── run.sh
├── src
│   ├── MessageProcessor.cpp
│   ├── MessageQueue.cpp
│   └── main.cpp
└── tests
    └── MessageQueue_test.cpp

Core Components
Message: A simple struct representing a market data message.

MessageQueue: A thread-safe queue for passing messages between threads, inspired by systems like BlazingMQ. This is crucial for decoupling the data ingestion part of the gateway from the data processing part.

IMessageProcessor: An interface for processing messages, allowing for different processing strategies to be implemented.

MessageProcessor: A concrete implementation of IMessageProcessor that will contain the business logic for handling market data.

Building and Running
Prerequisites (Arch Linux)
A C++17 compliant compiler (like g++).

CMake (version 3.10 or later).

Google Test (Gtest) library.

Install required dependencies on Arch Linux:

sudo pacman -S base-devel cmake gtest

Instructions
Use the provided run.sh script to easily build and run the application and tests.

chmod +x run.sh
./run.sh

Design Philosophy
Low Latency: The custom, thread-safe message queue (MessageQueue.h/cpp) is designed for efficient, lock-protected data transfer between threads, minimizing latency.

High Throughput: The multi-threaded producer/consumer model (main.cpp) utilizes multiple worker threads to process data concurrently.

Testability: The core data component (MessageQueue) is verified with Gtest to ensure concurrency and reliability.