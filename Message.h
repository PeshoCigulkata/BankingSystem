#pragma once
#include "String.h"

class Message {
private:
    String content="Unknown";

public:
    Message() = default;
    Message(const String& content) : content(content) {}

    String getContent() const;

    void printMessage() const;

    friend std::ostream& operator<<(std::ostream& os, const Message& message);
};