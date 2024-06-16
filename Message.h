#pragma once
#include "String.h"

class Message {
private:
	String from = "Unknown";
	String content = "Empty";
	String bankName = "Unknown";
	String accNumber = "";

public:
	Message() = default;
	Message(const String& from, const String& content, const String& bankName) :from(from), content(content), bankName(bankName) {}
	Message(const String& from, const String& content, const String& bankName, const String& number) : from(from), content(content), bankName(bankName), accNumber(number) {}
	
	const String& getFrom() const;
	const String& getContent() const;
	const String& getBankName() const;

	void printMessage() const;

	friend std::ostream& operator<<(std::ostream& os, const Message& message);
};