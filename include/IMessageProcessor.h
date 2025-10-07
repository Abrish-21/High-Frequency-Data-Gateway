#ifndef I_MESSAGE_PROCESSOR_H
#define I_MESSAGE_PROCESSOR_H

#include "Message.h"

// Abstract interface for a message processor (Strategy/Interface Pattern).
// This allows you to easily swap out or mock the processing logic,
// crucial for complex systems and unit testing.
class IMessageProcessor {
public:
    virtual ~IMessageProcessor() = default;
    virtual void process(const Message& message) = 0;
};

#endif // I_MESSAGE_PROCESSOR_H
