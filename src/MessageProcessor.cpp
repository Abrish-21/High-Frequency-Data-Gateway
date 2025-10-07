#include "../include/MessageProcessor.h"
#include <iostream>

void MessageProcessor::process(const Message& message) {
    // LOW-LATENCY LOGIC HERE:
    // This function executes in a consumer thread and should be optimized.
    // In a real HFT system, this might involve:
    // 1. Updating a lock-free Order Book structure.
    // 2. Checking a trading signal trigger.
    
    // For this simulation, we'll just print the message details.
    std::cout << "Processor Thread [" << std::this_thread::get_id() << "]: "
              << "Symbol=" << message.symbol
              << ", Price=" << message.price
              << ", Size=" << message.size
              << std::endl;
}
