#pragma once
#include "String.h"
//#include "Login.h"
//enum class UserRoles {
//	Client,
//	BankWorker,
//	OtherFirmWorker,
//	undefined
//
//};

class Account {
protected:
	String firstName="";
	String lastName="";
	String UCN="";      //Unique Citizenship Number
	unsigned age=0;
	//String accountNumber="";
	String balance="0";
	String password = "";     // <---- //TODO:

	String role = "";
public:
	Account() = default;
	
	Account(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& password,  const String& role);

	const String& getPassword()const;
	const String& getFirstName()const;
	const String& getLastName()const;
	 const String& getBalance()const;
	//const String& getAccountNumber()const;
	const String& getUCN()const;
	unsigned getAge()const;
	const String& getRole()const;

	void setBalance(const String& sum);
	//void setAccountNumber(const String& num);

	virtual void exit()const = 0;
	virtual void help()const = 0;
	virtual void whoami()const = 0;
};