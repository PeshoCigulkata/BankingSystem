#include "Check.h"



Check::Check(const String& code, double toSendSum) : code(code), sum(toSendSum) {}

double Check::getSum() const
{
	return sum;
}

const String& Check::getCode() const
{
	return code;
}
