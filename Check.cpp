#include "Check.h"



Check::Check(const String& code, const String& toSendSum) : code(code), sum(toSendSum) {}

const String& Check::getSum() const
{
	return sum;
}

const String& Check::getCode() const
{
	return code;
}
