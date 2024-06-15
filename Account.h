#pragma once
#include "String.h"
enum class UserRoles {
	Client,
	BankWorker,
	OtherFirmWorker,
	undefined

};


//-----------------------------------------------------------------
//NAPRAVI VSICHKO DA E OT TIP STRING ZASHTOTO SE PRIEMA NAPISANO CHAROVE OT KONZOLATA!!!!
//--------------------------------------------------------------------

class Account {
private:
	/*String firstName;
	String lastName;*/
	String UCN=0;      //Unique Citizenship Number
	unsigned age=0;
	String account_number=0;
	String balance=0;
	String owner=nullptr;

	UserRoles role=UserRoles::undefined;
public:
	virtual UserRoles getRole()const;

	Account(const String& acc_num, const String& _UCN, unsigned _age, const String& owner, UserRoles role);

	void printAccount()const {
		std::cout << account_number << std::endl;
	}

	const String& getOwner()const;
	const String& getBalance()const;
	const String& getAccountNumber()const;
	const String& getUCN()const;
	unsigned getAge()const;
	UserRoles getRole()const;

	void setBalance(String sum);
};