#pragma once
#include "String.h"
enum class UserRoles {
	Client,
	BankWorker,
	OtherFirmWorker,
	undefined

};

class Account {
private:
	/*String firstName;
	String lastName;*/
	unsigned UCN=0;      //Unique Citizenship Number
	unsigned age=0;
	int account_number=0;
	double balance=0;
	String owner=nullptr;

	UserRoles role=UserRoles::undefined;
public:
	virtual UserRoles getRole()const;

	Account(int acc_num, int _UCN, unsigned _age, String owner);
	Account(UserRoles _role);

	String getOwner()const;
	double getBalance()const;
	void setBalance(double sum);
	int getAccountNumber()const;
	unsigned getUCN()const;
	unsigned getAge()const;

	/*void deposit(double amount) {
		balance += amount;
	}

	bool withdraw(double amount) {
		if (balance >= amount) {
			balance -= amount;
			return true;
		}
		return false;
	}*/
};