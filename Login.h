#pragma once
#include "Vector.hpp"
#include "String.h"
#include "Bank.h"
#include "OtherFirmWorker.h"
/*The idea is to have main space of all accounts and in case of exit we leave it, so every class inherits Login.*/



class Login {
private:                                    //The static variables indicate the users we have at the moment!, CurrentUsers is live based pointers and in case of exiting the program we make the pointer of hte user in there nullPTR
	static Vector<Client*> clients;
	static Vector<BankWorker*> bankWorkers;
	static Vector<Bank*> banks;

	//Account* currentUser = nullptr;
	Vector<Account*> currentUsers{nullptr};
public:
	void login(const String& firstName, const String& lastName, const String& password) {
	
	}

	void signup(const String& firstName, const String& lastName, const String& UCN, unsigned age, const UserRoles& role, const String& password, const String& bankName) {
		if (role == UserRoles::Client) {
			Account* currentUser = new Client(firstName, lastName, UCN, age, password, role);
			currentUsers.push_back(currentUser);
		}
		else if (role == UserRoles::BankWorker) {
			Account* currentUser = new BankWorker(firstName, lastName, UCN, age, password, role);
			currentUsers.push_back(currentUser);
		}
		else if (role == UserRoles::OtherFirmWorker) {
			Account* currentUser = new OtherFirmWorker(firstName, lastName, UCN, age, password, role);
			currentUsers.push_back(currentUser);
		}
	}



};

 
