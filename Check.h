#pragma once
#include "String.h"


class Check {
private:
	String code = "***";
	double sum = 0;

public:
	Check() = default;
	Check(const String& code, double toSendSum);

	double getSum()const;
	const String& getCode()const;

};