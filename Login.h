#pragma once
#include "Vector.hpp"
#include "String.h"
#include "Bank.h"
#include "OtherFirmWorker.h"
#include "Account.h"
/*The idea is to have main space of all accounts and in case of exit we leave it, so every class inherits Login.*/


class Client;
class BankWorker;
class OtherFirmWorker;
class Bank;

class Login {
private:                                    //The static variables indicate the users we have at the moment!, CurrentUsers is live based pointers and in case of exiting the program we make the pointer of hte user in there nullPTR
	static Vector<Client*> clients;
	static Vector<BankWorker*> bankWorkers;
	static Vector<OtherFirmWorker*> otherFirmWorker;
	static Vector<Bank> banks;

	int index = -1;
	Account* currentUser = nullptr;
	bool isClient = false;
	bool isBankWorker = false;
	bool isOtherFirmWorker = false;

	const String& getRole(const String& firstName, const String& lastName, const String& password);

	void getInfoOfExistingUser(String& balance, String& accountID, String& UCN, unsigned& age);

	Bank* getBankByName(const String& bankName);

	//Client* getLogged;

public:
	void login(const String& firstName, const String& lastName, const String& password);

	void signup(const String& firstName, const String& lastName, const String& UCN, unsigned age, const String& role, const String& password, const String& bankName);

	void create_bank(const String& bankName);

	void exit();
};


