#include "Account.h"


Account::Account(int acc_num, int _UCN,unsigned _age, String _owner) : account_number(acc_num), UCN(_UCN),age(_age), owner(_owner){
	balance = 0;

}

Account::Account(UserRoles _role) {
	role = _role;
}

String Account::getOwner()const {
	return owner;
}
double Account::getBalance()const {
	return balance;
}

void Account::setBalance(double sum) {
	balance = sum;
}

int Account::getAccountNumber()const {
	return account_number;
}

UserRoles Account::getRole()const {
	return role;
}