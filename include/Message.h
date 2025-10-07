#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

// Represents a single market data message.
// In a real-world high-frequency system, this would be highly optimized 
// (e.g., fixed size, no heap allocation, use of structs/unions).
struct Message {
    long long timestamp;
    std::string symbol;
    double price;
    int size;
};

#endif // MESSAGE_H
