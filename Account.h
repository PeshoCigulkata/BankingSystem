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
	unsigned UCN=0;      //Unique Citizenship Number
	unsigned age=0;
	int account_number=0;
	double balance=0;
	String owner=nullptr;

	UserRoles role=UserRoles::undefined;
public:
	virtual UserRoles getRole()const;

	Account(int acc_num, int _UCN, unsigned _age, String owner, UserRoles role);

	String getOwner()const;
	double getBalance()const;
	int getAccountNumber()const;
	unsigned getUCN()const;
	unsigned getAge()const;
	UserRoles getRole()const;

	void setBalance(double sum);
};