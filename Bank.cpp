#include "Bank.h"

Bank::Bank(String _name) :name(_name) {
	for (unsigned i = 0; i < 1024; ++i) {
		CheckSums[i] = 0;
	}
}

Account* Bank::get_account(unsigned account_number)const {
	for (unsigned i = 0; i < size; ++i) {
		if (accounts[i]->getAccountNumber() == account_number) {
			return accounts[i];
		}
	}
	return nullptr;

}

unsigned Bank::getSize()const {
	return size;
}

double Bank::getCheckAtIdx(unsigned idx)const {
	return CheckSums[idx];
}


String Bank::getName()const {
	return name;
}


Bank::~Bank() {
	free();
}

void Bank::free() {
	for (unsigned i = 0; i < size; ++i) {
		delete accounts[i];
	}
	delete[] accounts;

	for (size_t i = 0; i < 1024; i++)
	{
		CheckSums[i] = 0;
	}
	unsigned size = 0;
	unsigned capacity = 0;
	name = nullptr;
}

void Bank::resize() {
	capacity *= 2;
	Account** new_accounts = new Account * [capacity];
	for (unsigned i = 0; i < size; ++i) {
		new_accounts[i] = accounts[i];
	}
	delete[] accounts;
	accounts = new_accounts;
}

int Bank::create_account(String owner, UserRoles role, unsigned UCN, unsigned age) {
	if (size >= capacity) {
		resize();
	}
	int account_number = size + 1;
	accounts[size++] = new Account(account_number, UCN, age, owner);
	//opravi v zavisimost ot rolqta!
	return account_number;
}

Bank::Bank() : name("Unnamed"), size(0), capacity(10) {
	accounts = new Account * [capacity] {nullptr};
	for (unsigned i = 0; i < 1024; ++i) {
		CheckSums[i] = 0;
	}
}

bool Bank::close_account(int account_number) {
	for (unsigned i = 0; i < size; ++i) {
		if (accounts[i]->getAccountNumber() == account_number) {
			delete accounts[i];
			accounts[i] = accounts[size--];
			return true;
		}
	}
	return false;
}

int Bank::getLeastBusyWorker()const {
	int index = 0;
	int employeesCount = employees.getCount();

	int leastTasks = employees[0]->getTasksSize();
	for (size_t i = 0; i < employeesCount; i++)
	{
		if (employees[i]->getTasksSize() < leastTasks) {
			index = i;
			leastTasks = employees[i]->getTasksSize();
		}
	}
	return index;
}

