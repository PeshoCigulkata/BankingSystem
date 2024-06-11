#include "Client.h"


Client::Client() :Account(UserRoles::Client) {}

void Client::check_avl()const {
	std::cout << getBalance();
}

void Client::open()const {
	//v main moje da se razpishe logikata!
	//samiqt  bank koito sme suzdali prosto uvelichavame size++ i pravim nov akaunt
}

void Client::close()const {
	//v main moje da se razpishe logikata!
	//samiqt  bank koito sme suzdali prosto uvelichavame size-- i triem akaunt
}

void Client::redeem(Bank& other, int verificationNum) {
	for (size_t i = 0; i < other.getSize(); i++)
	{
		if (other.get_account(i)->getAccountNumber() == verificationNum) {
			if (other.getCheckAtIdx(i) != 0) {
				double sum = other.getCheckAtIdx(i);
				setBalance(sum);
			}
			else {
				throw std::exception("No check available");
			}
		}
	}
}

void Client::change(Bank& new_bank, const Bank& other_bank, int account_number) {
	int index = -1;
	for (size_t i = 0; i < other_bank.getSize(); i++)
	{
		if (other_bank.get_account(i)->getAccountNumber() == account_number) {
			index = i;
		}
	}

	if (index == -1) {
		throw std::runtime_error("Non-existant account! ");
	}

	Account* account = other_bank.get_account(index);


	if (account) {
		String owner = account->getOwner();
		UserRoles role = account->getRole();
		double balance = account->getBalance();

		int new_acc_num = new_bank.create_account(owner, role);
		Account* new_account = new_bank.get_account(new_acc_num);

		new_account->setBalance(balance);
		//other_bank.close_account(account_number);

	}

}


void Client::list(const Bank& bank) {
	int index = -1;
	for (size_t i = 0; i < 1024; i++)
	{
		if (strcmp(bank.getName().c_str(), array[i].getName().c_str())) {
			index = i;
		}
	}
	if (index == -1) {
		throw "greshka, nqmame akaunt v takava banka!";
	}
	else {
		//we have an account in such bank
		for (size_t i = 0; i < bank.getSize(); i++)
		{
			if (strcmp(bank.get_account(i)->getOwner().c_str(), getOwner().c_str())) {
				std::cout << getAccountNumber();
			}
		}
	}

}