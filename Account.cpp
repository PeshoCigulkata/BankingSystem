#include "Account.h"


Account::Account(const String& acc_num,const String& _UCN, unsigned _age,const String& _owner, UserRoles role) : account_number(acc_num), UCN(_UCN), age(_age), owner(_owner), role(role) {
	balance = "0";

}

const String& Account::getOwner()const {
	return owner;
}
const String& Account::getBalance()const {
	return balance;
}

void Account::setBalance(String sum) {
	balance = sum;
}

const String& Account::getAccountNumber()const {
	return account_number;
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