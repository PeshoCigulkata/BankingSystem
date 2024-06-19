#pragma once
#include "Vector.hpp"
#include "String.h"
#include "Bank.h"
#include "OtherFirmWorker.h"
#include "Account.h"
/*The idea is to have main space of all accounts and in case of exit we leave it, so every class inherits Login.*/



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

	UserRoles getRole(const String& firstName, const String& lastName, const String& password) {
		for (size_t i = 0; i < clients.getCount(); i++)
		{
			if (clients[i]->getFirstName() == firstName && clients[i]->getLastName() == lastName && clients[i]->getPassword() == password) {
				isClient = true;
				index = i;
				return UserRoles::Client;
			}
		}

		for (size_t i = 0; i < bankWorkers.getCount(); i++)
		{
			if (bankWorkers[i]->getFirstName() == firstName && bankWorkers[i]->getLastName() == lastName && bankWorkers[i]->getPassword() == password) {
				isBankWorker = true;
				index = i;
				return UserRoles::BankWorker;
			}
		}

		for (size_t i = 0; i < otherFirmWorker.getCount(); i++)
		{
			if (otherFirmWorker[i]->getFirstName() == firstName && otherFirmWorker[i]->getLastName() == lastName && otherFirmWorker[i]->getPassword() == password) {
				isOtherFirmWorker = true;
				index = i;
				return UserRoles::BankWorker;
			}
		}

		throw std::exception("User not found!");
	}
	void getInfoOfExistingUser(String& balance, String& accountID, String& UCN, unsigned& age) {
		if (isClient == true) {
			balance = clients[index]->getBalance();
			accountID = clients[index]->getAccountNumber();
			UCN = clients[index]->getUCN();
			age = clients[index]->getAge();
		}
		else if (isBankWorker == true) {

			balance = bankWorkers[index]->getBalance();
			accountID = bankWorkers[index]->getAccountNumber();
			UCN = bankWorkers[index]->getUCN();
			age = bankWorkers[index]->getAge();

		}
		else if (isOtherFirmWorker == true) {
			balance = otherFirmWorker[index]->getBalance();
			accountID = otherFirmWorker[index]->getAccountNumber();
			UCN = otherFirmWorker[index]->getUCN();
			age = otherFirmWorker[index]->getAge();
		}

	}
	Bank* getBankByName(const String& bankName) {
		for (size_t i = 0; i < banks.getCount(); i++)
		{
			if (banks[i].getName() == bankName) {
				return &banks[i];
			}
		}

		return nullptr;
	}
public:
	void login(const String& firstName, const String& lastName, const String& password) {
		if (currentUser != nullptr) {
			throw std::exception("One person can be logged!");
		}

		UserRoles roleOfLogger = getRole(firstName, lastName, password);

		String balance = "";
		String accountID = "";
		String UCN = "";
		unsigned age = 0;
		getInfoOfExistingUser(balance, accountID, UCN, age);

		if (roleOfLogger == UserRoles::Client) {
			currentUser = new Client(firstName, lastName, UCN, age, password, roleOfLogger);

		}
		else if (roleOfLogger == UserRoles::BankWorker) {
			currentUser = new BankWorker(firstName, lastName, UCN, age, password, roleOfLogger);
		}
		else if (roleOfLogger == UserRoles::OtherFirmWorker) {
			currentUser = new OtherFirmWorker(firstName, lastName, UCN, age, password, roleOfLogger);
		}

	}

	void signup(const String& firstName, const String& lastName, const String& UCN, unsigned age, const UserRoles& role, const String& password, const String& bankName) {
		if (role == UserRoles::Client) {
			Bank* bank = getBankByName(bankName);
			Account* User = new Client(firstName, lastName, UCN, age, password, role);
			bank->addClient(User);
			dynamic_cast<Client*>(User)->addBank(bank);
			//currentUsers.push_back(currentUser);
		}
		else if (role == UserRoles::BankWorker) {
			Bank* bank = getBankByName(bankName);
			Account* user = new BankWorker(firstName, lastName, UCN, age, password, role);
			bank->addWorker(user);
			dynamic_cast<BankWorker*>(user)->setBank(bank);
			//	currentUsers.push_back(currentUser);
		}
		else if (role == UserRoles::OtherFirmWorker) {
			Bank* bank = getBankByName(bankName);
			Account* _user = new OtherFirmWorker(firstName, lastName, UCN, age, password, role);
			bank->addClient(_user);
			dynamic_cast<OtherFirmWorker*>(_user)->setBank(bank);
			//	currentUsers.push_back(currentUser);
		}
	}

	void create_bank(const String& bankName) {
		Bank bank(bankName);
		banks.push_back(bank);
	}


};


