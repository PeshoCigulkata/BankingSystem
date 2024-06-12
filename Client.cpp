#include "Client.h"
#include "String.h"

unsigned getNumberLength(unsigned  n)
{

	if (n == 0)
		return 1;
	unsigned int res = 0;

	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return res;
}

char getCharFromDigit(int digit)
{
	if (digit < 0 || digit > 9)
		return '\0';

	return digit + '0';
}

String toString(unsigned number, String str) {
	unsigned length = getNumberLength(number);
	for (int i = length - 1; i >= 0; i--) {
		str += getCharFromDigit(number % 10);
	}

	return str;
}


Client::Client() :Account(UserRoles::Client) {}

void Client::check_avl()const {
	std::cout << getBalance();
}

void Client::open(Bank& bank) {
	int acc_num = bank.create_account(getOwner(), getRole(), getUCN(), getAge());
	String str;
	Message message("Opened account number: " + getOwner() + toString(getUCN(), str) + toString(getAge(), str));
	bank.addMessage(message);
	messages.push_back(message);
}

void Client::close(Bank& bank, int account_number) {
	if (bank.close_account(account_number)) {  //It means such account exists! The operation to close the account has succeeded.
		String str;
		Message message("Closed account number: " + toString(account_number,str));
		Message forClientMessage("You have closed an account! ");
		messages.push_back(forClientMessage);
		bank.addMessage(message);
	}
	else {
		throw std::runtime_error("This account doesnt exist! ");
	}
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