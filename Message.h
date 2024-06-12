#pragma once
#include "String.h"

class Message {
private:
    String content;

public:
    Message(const String& content) : content(content) {}

    String getContent() const;

    friend std::ostream& operator<<(std::ostream& os, const Message& message);
};