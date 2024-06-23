#include "Message.h"

const String& Message::getFrom() const {
	return from;
}

const String& Message::getContent() const {
	return content;
}

const String& Message::getBankName() const {
	return bankName;
}

//const String& Message::getContent() const {
//	return content;
//}

void Message::printMessage() const {
	std::cout << getContent() << "! Message from:" << getFrom() << ". From bank: " << getBankName() << std::endl;
}