#pragma once
#include "String.h"

class Message {
private:
	String from = "";  //The Worker
	String content = "";
	String bankName = "";
	String accNumber = "";

public:
	Message() = default;
	Message(const String& from, const String& content, const String& bankName) :from(from), content(content), bankName(bankName) {}
	Message(const String& from, const String& content, const String& bankName, const String& number) : from(from), content(content), bankName(bankName), accNumber(number) {}

	const String& getFrom() const;
	const String& getContent() const;
	const String& getBankName() const;

	void printMessage() const;
};