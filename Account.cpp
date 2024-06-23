#include "Account.h"

const String& Account::getPassword() const
{
	return password;
}
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

//void Account::setAccountNumber(const String& accNum)
//{
//	accountNumber = accNum;
//}

//const String& Account::getAccountNumber()const {
//	return accountNumber;
//}

const String& Account::getUCN() const
{
	return UCN;
}

unsigned Account::getAge() const
{
	return age;
}

const String& Account::getRole()const {
	return role;
}

Account::Account(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& _password,  const String& _role) {
	firstName = _firstName;
	lastName = _lastName;
	UCN = _UCN;
	age = _age;
	password = _password;
	role = _role;
}
