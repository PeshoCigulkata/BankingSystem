#pragma once
#include "Account.h"
#include "Bank.h"
#include "Vector.hpp"
#include "Message.h"
#include "Check.h"

class Client : public Account {
private:
	Vector<Bank*> banks;
	Vector<Message> messages;
	Vector<Check> checks;
	int getBankIndex(const String& bankName) const;
	String password = "";
public:
	Client(const String& firstName, const String& lastName, const String& _UCN, unsigned _age, const String& accNum, const UserRoles& role);
	Client(const String& firstName, const String& lastName, const String& _UCN, unsigned _age, const String& password, const UserRoles& role) {

	}

	void check_avl(const String& bank_name, const String& account_number)const;

	void open(const String& bank_name);

	void close(const String& bank_name, const String& account_number);

	void redeem(const String& bank_name,const String& accountNumber, const String& verificationNum);

	void receiveCheck(const Check& check);

	void change(const String& new_bank, const String& other_bank, const String& account_number);

	void list(const String& bank);

	void message()const;

	void addMessage(const Message& message);

	virtual void exit()override; //TODO!!!!!!!!!!!!!!!!!
	virtual void whoami()const override;
	virtual void help()const override;

	Bank* getBankByName(const String& name)const;
};