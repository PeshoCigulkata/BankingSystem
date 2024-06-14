#include "Message.h"


String Message::getContent() const {
    return content;
}

std::ostream& operator<<(std::ostream& os, const Message& message) {
    os << message.content;
    return os;
}

void Message::printMessage() const {
    std::cout << getContent() << std::endl;
}