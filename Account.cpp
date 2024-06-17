#include "Account.h"

const String& Account::getFirstName() const
{
	return firstName;
}

const String& Account::getLastName() const
{
	return lastName;
}

const String& Account::getBalance()const {
	return balance;
}

void Account::setBalance(const String& sum) {
	balance = sum;
}

void Account::setAccountNumber(const String& accNum)
{
	accountNumber = accNum;
}

const String& Account::getAccountNumber()const {
	return accountNumber;
}

const String& Account::getUCN() const
{
	return UCN;
}

unsigned Account::getAge() const
{
	return age;
}

UserRoles Account::getRole()const {
	return role;
}

Account::Account(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& _accountNumber, const UserRoles& _role)
{
	firstName = _firstName;
	lastName = _lastName;
	UCN = _UCN;
	age = _age;
	accountNumber = _accountNumber;
	role = _role;
}
