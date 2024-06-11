#pragma once
#include "String.h"
#include "Account.h"

class Bank {
private:
   String name;               // name of the bank
   Account** accounts;
   double CheckSums[1024]; //every index indicates an account with the checks value they have received, if its 0 => no check received
   unsigned size;
   unsigned capacity;

  void free();
  void resize();
public:
	Bank();
	Bank(String n);

	Account* get_account(unsigned account_id)const;
	unsigned getSize()const;
	double getCheckAtIdx(unsigned idx)const;
	String getName()const;
	int create_account(String owner, UserRoles role,unsigned UCN,unsigned age);
	void close_account(int account_number);

	Bank(const Bank& other) = delete;
	Bank& operator=(const Bank& other)=delete;
	~Bank();
};
