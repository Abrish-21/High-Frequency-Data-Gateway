#include "../include/MessageQueue.h"
#include "../include/MessageProcessor.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <memory>

// Producer function to simulate receiving market data (e.g., from a FIX connection)
void data_producer(MessageQueue& queue) {
    std::cout << "--- Producer started, generating 100 messages... ---" << std::endl;
    for (int i = 0; i < 100; ++i) {
        Message msg;
        msg.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        msg.symbol = (i % 2 == 0) ? "AAPL" : "GOOG";
        msg.price = 150.0 + i * 0.1;
        msg.size = 100 + i;

        queue.push(msg);
        // Simulate network latency or burstiness
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    }
    queue.close(); // Signal consumers to shut down after processing remaining messages
    std::cout << "--- Producer finished and closed the queue. ---" << std::endl;
}

// Consumer function to process messages from the queue in parallel
void data_consumer(MessageQueue& queue, IMessageProcessor& processor) {
    while (auto msg_opt = queue.pop()) {
        processor.process(msg_opt.value());
    }
    std::cout << "Consumer Thread [" << std::this_thread::get_id() << "] shut down." << std::endl;
}

int main() {
    MessageQueue data_queue;
    MessageProcessor processor;

    // Start the single producer thread
    std::thread producer_thread(data_producer, std::ref(data_queue));

    // Start multiple consumer/worker threads for high throughput
    const unsigned int num_consumers = 4;
    std::cout << "Starting " << num_consumers << " consumer threads." << std::endl;
    std::vector<std::thread> consumer_threads;
    for (unsigned int i = 0; i < num_consumers; ++i) {
        consumer_threads.emplace_back(data_consumer, std::ref(data_queue), std::ref(processor));
    }

    // Wait for all threads to complete (clean shutdown)
    producer_thread.join();
    for (auto& t : consumer_threads) {
        t.join();
    }

    std::cout << "\nData gateway simulation finished successfully." << std::endl;

    return 0;
}
