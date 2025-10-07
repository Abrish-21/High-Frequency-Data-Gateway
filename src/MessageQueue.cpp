#include "../include/MessageQueue.h"

void MessageQueue::push(const Message& message) {
    // Lock guard ensures exclusive access to the queue_ and mutex_
    std::lock_guard<std::mutex> lock(mutex_);
    if (closed_) {
        // If the queue is closed, ignore the message (or handle error)
        return; 
    }
    queue_.push(message);
    // Notify one waiting thread that an item is available
    cond_var_.notify_one();
}

std::optional<Message> MessageQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    
    // Wait until the queue is not empty OR the queue is closed.
    // The lambda predicate prevents spurious wakeups.
    cond_var_.wait(lock, [this] { return !queue_.empty() || closed_; });

    // Check if we woke up because the queue is closed AND empty
    if (queue_.empty() && closed_) {
        return std::nullopt; // Signal termination to the consumer
    }

    // Process the message (the lock is held while popping)
    Message msg = queue_.front();
    queue_.pop();
    return msg;
}

void MessageQueue::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    closed_ = true;
    // Notify all waiting consumer threads so they can check the 'closed_' flag
    cond_var_.notify_all();
}
