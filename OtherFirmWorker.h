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

class OtherFirmWorker : public Account {
private:
	Vector<Bank*> banks;
	Vector<Client*>clients;

	Bank* getBankByName(const String& bankName)const {
		for (size_t i = 0; i < banks.getCount(); i++)
		{
			if (banks[i]->getName() == bankName) {
				return banks[i];
			}
		}
		return nullptr;
	}

	Client* getClientByUCN(const String& UCN) {
		for (size_t i = 0; i < clients.getCount(); i++)
		{
			if (clients[i]->getUCN() == UCN) {
				return clients[i];
			}
		}
		return nullptr;
	}

public:
	OtherFirmWorker(const String& name, const String& UCN, unsigned age, const UserRoles& role) :Account("", UCN, age, name, role) {}

	void send_check(double sum, const String& verificationCode, const String& BankName, const String& UCN) {
		Check check(verificationCode, sum);
		Bank* getBank = getBankByName(BankName);
		Client* getClient = getClientByUCN(UCN);
		Message message(getOwner(), "You have a check assigned to you from: ", getBank->getName(), verificationCode);
		getClient->addMessage(message);
		getClient->sendCheck(check);
	}

};