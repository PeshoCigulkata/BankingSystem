#include "Client.h"
#include "String.h"



//unsigned _getNumberLength(unsigned  n)
//{
//
//	if (n == 0)
//		return 1;
//	unsigned int res = 0;
//
//	while (n != 0)
//	{
//		res++;
//		n /= 10;
//	}
//	return res;
//}
//
//char _getCharFromDigit(int digit)
//{
//	if (digit < 0 || digit > 9)
//		return '\0';
//
//	return digit + '0';
//}
//
//String _toString(unsigned number, String str) {
//	unsigned length = _getNumberLength(number);
//	for (int i = length - 1; i >= 0; i--) {
//		str += _getCharFromDigit(number % 10);
//	}
//
//	return str;
//}

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

unsigned getDigit(char ch) {
	return ch - '0';
}

size_t CharToDigit(const String& str) {
	size_t length = str.length();
	unsigned Number = 0;
	unsigned multiplier = 1;
	for (size_t i = 0; i < length; i++)
	{
		if (isDigit(str[i])) {
			Number += getDigit(str[i]) * multiplier;
			multiplier *= 10;
		}
	}

	return Number;
}



Client::Client(const String& firstName, const String& lastName, const String& _UCN, unsigned _age, const String& password, const String& role) :Account(firstName, lastName, _UCN, _age, password, role) {

}

void Client::addBank(Bank* bank) {
	banks.push_back(bank);
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

Bank* Client::getBankByName(const String& name)const {
	for (size_t i = 0; i < banks.getCount(); i++)
	{
		if (banks[i]->getName() == name) {
			return banks[i];
		}
	}
	return nullptr;
}

void Client::setAccountNumber(const String& _accountNumber)
{
	accountNumber = _accountNumber;
}

void Client::check_avl(const String& bank_name, const String& account_number)const {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::runtime_error("Bank with this name doesnt exist!");
	}

	std::cout << "Balance: " << banks[index]->getClientByAccNum(account_number)->getBalance() << std::endl;
}

void Client::open(const String& bank_name) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];  // We have the current bank.
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask("Open", this);
	currentBank->receiveTask(currentTask);

	int idx = currentBank->getTaskSize() - 1;
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
}

void Client::close(const String& bank_name, const String& account_number) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask("Close", this, account_number);
	currentBank->receiveTask(currentTask);

	int idx = currentBank->getTaskSize() - 1;        //from potential fixes! without it it can cause problems
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
}

void Client::redeem(const String& bank_name, const String& accountNumber, const String& verificationNum) {
	int indexBank = getBankIndex(bank_name);

	if (indexBank == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	int indexCheck = -1;
	for (size_t i = 0; i < checks.getCount(); i++)
	{
		if (checks[i].getCode() == verificationNum) {
			indexCheck = i;
			break;
		}
	}

	if (indexCheck == -1) {
		throw std::exception("No check.");
	}

	Bank* currentBank = banks[indexBank];

	Client* currentClient = currentBank->getClientByAccNum(accountNumber);
	String currentBalance = currentClient->getBalance();
	currentBalance += checks[indexCheck].getSum();

}

void Client::change(const String& new_bank, const String& this_bank, const String& account_number) {
	int indexCurrent = getBankIndex(this_bank);
	int indexNew = getBankIndex(new_bank);
	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names! ");
	}

	Bank* currentBank = banks[indexCurrent];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask("Change", this, account_number);
	banks[indexCurrent]->receiveTask(currentTask);
	int indexOfCurrentTask=banks[indexCurrent]->getTaskIndex(currentTask);
	//banks[indexCurrent]->getTaskSize();
	//currentBank->receiveTask(currentTask);

	int idx = banks[indexCurrent]->getTaskSize() - 1;
	banks[indexCurrent]->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(banks[indexCurrent]->getTaskByIdx(indexOfCurrentTask));
}

void Client::list(const String& bank_name) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];
	bool hasAcc = false;
	for (size_t i = 0; i <= CharToDigit(currentBank->getClientsNumber()); i++)
	{
		if ((getFirstName()==currentBank->getClientByIndex(i)->getFirstName()) && (getLastName()==currentBank->getClientByIndex(i)->getLastName())) {
			currentBank->printClientByIdx(i);
			hasAcc = true;
		}
	}
	if (hasAcc == false) {
		throw std::exception("The account doesnt exist!");
	}
}

void Client::message()const {
	if (messages.getCount() == 0) {
		std::cout << "No messages to show" << std::endl;
	}

	int count = messages.getCount();
	for (int i = 0; i < count; i++) {
		std::cout << "[" << (i) << "] ";
		messages[i].printMessage();
	}

}

void Client::receiveCheck(const Check& check) {
	checks.push_back(check);
}

void Client::addMessage(const Message& message) {
	messages.push_back(message);
}


void Client::exit()const {
	std::cout << "exited";
}

void Client::whoami()const {
	std::cout << "Name: " << this->getFirstName() << " " << this->getLastName() << std::endl;
	std::cout << "Role: " << this->getRole() << std::endl;
	std::cout << "Age: " << this->getAge() << std::endl;
	std::cout << "UCN: " << this->getUCN() << std::endl;
	/*PASSWORD COUT*/
}

void Client::help()const {
	std::cout << "Commands available: " << std::endl;
	std::cout << "-check_avl [bank_name] [account_number] " << std::endl;
	std::cout << "-open [bank_name] " << std::endl;
	std::cout << "-close [bank_name] [account_number]  " << std::endl;
	std::cout << "-redeem [bank_name] [account_number] [verification_code]  " << std::endl;
	std::cout << "-change [new_bank_name] [current_bank_name] [account_number] " << std::endl;
	std::cout << "-list [bank_name] " << std::endl;
	std::cout << "-messages " << std::endl;
	std::cout << "-whoami " << std::endl;
	std::cout << "-exit " << std::endl;

}

const String& Client::getAccountNumber()const {
	return accountNumber;
}