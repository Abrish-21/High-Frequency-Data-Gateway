#include <gtest/gtest.h>
#include "../include/MessageQueue.h"
#include <thread>
#include <vector>

// Test case 1: Basic single-thread push and pop functionality
TEST(MessageQueueTest, SingleThreadPushPop) {
    MessageQueue queue;
    Message msg{12345, "AAPL", 150.5, 100};
    queue.push(msg);
    auto popped_msg = queue.pop();
    
    ASSERT_TRUE(popped_msg.has_value());
    EXPECT_EQ(popped_msg->symbol, "AAPL");
    EXPECT_EQ(popped_msg->timestamp, 12345);
}

// Test case 2: Verifying correct shutdown behavior
TEST(MessageQueueTest, PopReturnsNullOptWhenClosedAndEmpty) {
    MessageQueue queue;
    queue.close();
    auto msg = queue.pop();
    ASSERT_FALSE(msg.has_value());
}

// Test case 3: Stress test concurrency for thread-safety
TEST(MessageQueueTest, MultiThreadedProducerConsumer) {
    MessageQueue queue;
    const int num_messages = 1000;

    // Producer thread
    std::thread producer([&]() {
        for (int i = 0; i < num_messages; ++i) {
            Message msg{ (long long)i, "TEST", (double)i, i };
            queue.push(msg);
        }
        queue.close();
    });

    int received_count = 0;
    std::thread consumer([&]() {
        while(auto msg = queue.pop()) {
            received_count++;
        }
    });

    producer.join();
    consumer.join();

    // Verify that all messages were successfully delivered exactly once
    EXPECT_EQ(received_count, num_messages);
}

// Gtest main function template
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
