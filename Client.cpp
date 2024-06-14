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

int Client::getBankIndex(const String& bankName) const {
	unsigned banksCount = banks.getCount();

	for (size_t i = 0; i < banksCount; i++)
	{
		if ((banks[i]->getName() == bankName)) {
			return i;
		}
	}
	return -1;
}

Client::Client(int acc_num, int _UCN, unsigned _age, String _owner, UserRoles role) :Account(acc_num, _UCN, _age, _owner, role) {}

void Client::check_avl(const String& bank_name, int account_number)const {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	std::cout << "Balance: " << banks[index]->get_account(account_number)->getBalance() << std::endl;
}

void Client::open(const String& bank_name) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}
	Bank* currentBank = banks[index];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask(TaskType::Open, getOwner());
	currentBank->receiveTask(currentTask);

	size_t idx = static_cast<size_t>(currentBank->getTaskSize()) - 1;        //from potential fixes! without it it can cause problems
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
}

void Client::close(const String& bank_name, int account_number) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask(TaskType::Close, getOwner());
	currentBank->receiveTask(currentTask);

	size_t idx = static_cast<size_t>(currentBank->getTaskSize()) - 1;        //from potential fixes! without it it can cause problems
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
}

void Client::redeem(const String& bank_name, int verificationNum) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];
	for (size_t i = 0; i < currentBank->getSize(); i++)
	{
		if (currentBank->get_account(i)->getAccountNumber() == verificationNum) {
			if (currentBank->getCheckAtIdx(i) != 0) {
				double sum = currentBank->getCheckAtIdx(i);
				setBalance(sum);
			}
			else {
				throw std::exception("No check available");
			}
		}
	}
}

void Client::change(const String& new_bank, const String& this_bank, int account_number) {
	int indexCurrent = getBankIndex(this_bank);
	int indexNew = getBankIndex(new_bank);
	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names!");
	}
	
	Bank* currentBank = banks[indexCurrent];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask(TaskType::Change, getOwner());
	currentBank->receiveTask(currentTask);

	size_t idx = static_cast<size_t>(currentBank->getTaskSize()) - 1;        //from potential fixes! without it it can cause problems
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
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