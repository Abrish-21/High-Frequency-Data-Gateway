🚀 High-Frequency Data Gateway: C++ Backend Service
A high-performance, low-latency C++ service designed to simulate real-time processing of streaming market data.

This project demonstrates core competencies in concurrent C++ programming, resource management, and architecture inspired by industrial-grade message queue systems like Bloomberg's BlazingMQ.

✨ Project Highlights & Features
Feature

Description

Resume Alignment

Multi-Threaded Architecture

Implements a classic Producer-Consumer pattern using std::thread to maximize concurrent data processing and throughput.

High-performance, low-latency

Custom Message Pipeline

Features a custom, thread-safe MessageQueue built with std::mutex and std::condition_variable for reliable, decoupled data transfer.

Designed a custom message processing pipeline

Modern C++ Implementation

Leverages C++17 features including std::optional for clear queue state signaling and efficient use of RAII (Resource Acquisition Is Initialization).

Leveraged modern C++ features (C++17)

Interface-Driven Design

Uses the IMessageProcessor abstract interface, ensuring the core business logic is modular, extensible, and easily mockable for testing.

Engineered a low-latency C++ backend service

Test-Driven Development (TDD)

Critical concurrency logic in MessageQueue is validated using Google Test (Gtest), ensuring robustness under multi-threaded stress.

Test-driven approach using Gtest

🛠️ Build and Setup (Arch Linux)
This project uses CMake for build management and is configured to run on a Linux environment, targeting the C++17 standard.

Prerequisites
Please install the following packages using pacman:

# Install base utilities, CMake, and the Google Test framework
sudo pacman -Syu
sudo pacman -S base-devel cmake gtest

File Structure
The logical separation of concerns is maintained via the following structure:

.
├── CMakeLists.txt              # Primary build file
├── README.md                   # You are here!
├── include/
│   ├── IMessageProcessor.h     # Processing interface
│   ├── Message.h               # Core data structure
│   └── MessageQueue.h          # Thread-safe queue header
├── src/
│   ├── main.cpp                # Gateway entry point and thread management
│   ├── MessageProcessor.cpp    # Business logic implementation
│   └── MessageQueue.cpp        # Thread-safe queue implementation
└── tests/
    └── MessageQueue_test.cpp   # Gtest suite for concurrency verification

▶️ How to Run
The entire build, test, and execution flow is automated via the included shell script.

Make the script executable:

chmod +x run.sh

Execute the script from the project root:

./run.sh

Output Flow: The script will automatically clean the build directory, run CMake, compile the application and tests, execute the Gtest suite, and finally run the multi-threaded data_gateway simulation.

🔬 Core Design Rationale
The MessageQueue
The MessageQueue is the heart of the system, crucial for achieving low latency and high throughput.

Decoupling: It separates the high-volume data ingestion thread (Producer) from the data analysis threads (Consumers).

Backpressure Handling: By using std::condition_variable::wait, consumer threads are put to sleep when the queue is empty, eliminating wasteful polling (busy-waiting) and preserving CPU cycles—a fundamental requirement for low-latency systems.

Clean Shutdown: The close() method and std::optional<Message> return type provide a clean, deadlock-free mechanism for shutting down all consumer threads once the producer is finished.

Extensibility
The use of IMessageProcessor allows new processing strategies (e.g., OrderBookProcessor, RiskCalculator) to be added without modifying the core data flow logic (main.cpp or MessageQueue.cpp).