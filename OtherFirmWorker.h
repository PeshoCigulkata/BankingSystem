#pragma once
#include "Account.h"
#include "String.h"
#include "Vector.hpp"
#include "Check.h"
#include "Bank.h"

enum class UserRoles {
	Client,
	BankWorker,
	OtherFirmWorker,
	undefined

};

class Bank;
class Client;
class Account; 

class OtherFirmWorker : public Account {
private:
	Vector<Bank*> banks;
	Vector<Client*>clients;

	Bank* getBankByName(const String& bankName)const;
	Client* getClientByUCN(const String& UCN)const;

public:
	OtherFirmWorker(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age,const String& password, const String& role);

	void send_check(const String& sum, const String& verificationCode, const String& BankName, const String& UCN);

	void setBank(Bank* bank);

	virtual void exit() const override; //TODO!!!!!!!!!!!!!!!!!
	virtual void whoami() const override;
	virtual void help() const override;
};