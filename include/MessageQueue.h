#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "Message.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

// A thread-safe queue for Messages, implementing the core message passing
// mechanism inspired by high-performance queues like BlazingMQ.
class MessageQueue {
public:
    // Pushes a message to the back of the queue.
    void push(const Message& message);

    // Waits for and pops a message from the front of the queue.
    // The condition variable ensures consumers sleep until data is available.
    // Returns std::nullopt if the queue is closed and empty.
    std::optional<Message> pop();

    // Closes the queue to signal that no more messages will be pushed,
    // waking up all waiting consumers.
    void close();

private:
    std::queue<Message> queue_;
    std::mutex mutex_;
    std::condition_variable cond_var_;
    bool closed_ = false;
};

#endif // MESSAGE_QUEUE_H
