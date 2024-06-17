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
	String firstName="";
	String lastName="";
	String UCN="";      //Unique Citizenship Number
	unsigned age=0;
	String accountNumber="";
	String balance="";
	String password = "";     // <---- //TODO:

	UserRoles role=UserRoles::undefined;
public:
	Account() = default;
	Account(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& accNum, const UserRoles& role);

	void printAccount()const {
		std::cout << accountNumber << std::endl;
	}

	const String& getFirstName()const;
	const String& getLastName()const;
	const String& getBalance()const;
	const String& getAccountNumber()const;
	const String& getUCN()const;
	unsigned getAge()const;
	UserRoles getRole()const;

	void setBalance(const String& sum);
	void setAccountNumber(const String& num);

	virtual void exit() = 0;
	virtual void help()const = 0;
	virtual void whoami()const = 0;
};