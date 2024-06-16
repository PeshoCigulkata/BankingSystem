#pragma once
#include "Account.h"
#include "Bank.h"
#include "Vector.hpp"
#include "Message.h"
#include "Check.h"



//--------------------------------------------------------------------------
//   DA SE DOOPRAVI SUOBSHTENIQTA KOITO POLUCHAVA CLIENTA!!!!!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------



class Client : public Account {
private:
	Vector<Bank*> banks;
	Vector<Message> messages;
	Vector<Check> checks;
	int getBankIndex(const String& bankName) const;
public:
	Client(String acc_num, String _UCN, unsigned _age, String owner, UserRoles role);

	void check_avl(const String& bank_name, const String& account_number)const;

	void open(const String& bank_name);

	void close(const String& bank_name, int account_number);

	void redeem(const String& bank_name, const String& verificationNum);

	void sendCheck(const Check& check) {
		checks.push_back(check);
	}

	void change(const String& new_bank, const String& other_bank, int account_number);

	void list(const String& bank);

	void message()const {

		if (messages.getCount() == 0) {
			std::cout << "No messages to show" << std::endl;
		}

		int count = messages.getCount();
		for (int i = 0; i < count; i++) {
			std::cout << "[" << (i) << "] ";
			messages[i].printMessage();
		}

	}

	void addMessage(const Message& message) {
		messages.push_back(message);
	}

	Bank* getBankByName(const String& name)const {
		for (size_t i = 0; i < banks.getCount(); i++)
		{
			if (banks[i]->getName() == name) {
				return banks[i];
			}
		}
		return nullptr;
	}

	
};