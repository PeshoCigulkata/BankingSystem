#pragma once
#include "Account.h"
#include "Bank.h"
#include "Vector.hpp"
#include "Message.h"




//--------------------------------------------------------------------------
//   DA SE DOOPRAVI SUOBSHTENIQTA KOITO POLUCHAVA CLIENTA!!!!!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------



class Client : public Account {
private:
	Vector<Bank*> banks;
	Vector<Message> messages;

int getBankIndex(const String& bankName) const;
public:
	Client(int acc_num, int _UCN, unsigned _age, String owner, UserRoles role);

	void check_avl(const String& bank_name, int account_number)const;

	void open(const String& bank_name);

	void close(const String& bank_name,int account_number);

	void redeem(const String& bank_name, int verificationNum);

	void change(const String& new_bank, const String& other_bank, int account_number);

	void list(const Bank& bank);

	void message()const;

	
};