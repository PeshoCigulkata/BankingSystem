#pragma once
#include "String.h"


class Check {
private:
	String code = "***";
	String sum = 0;

public:
	Check() = default;
	Check(const String& code, const String& toSendSum);

	const String& getSum()const;
	const String& getCode()const;

	~Check() = default;
};