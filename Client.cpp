#include "Client.h"
#include "String.h"

const String& RoleToString(UserRoles userRoles) {
	String str = "";
	switch (userRoles) {
	case UserRoles::Client:
		str = "Client";
		break;
	case UserRoles::BankWorker:
		str = "BankWorker";
		break;
	case UserRoles::OtherFirmWorker:
		str = "OtherFirmWorker";
		break;
	default:
		str = "Unknown";
		break;
	}
	return str;
}

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

Bank* Client::getBankByName(const String& name)const {
	for (size_t i = 0; i < banks.getCount(); i++)
	{
		if (banks[i]->getName() == name) {
			return banks[i];
		}
	}
	return nullptr;
}

Client::Client(const String& firstName, const String& lastName, const String& _UCN, unsigned _age, const String& accNum, const UserRoles& role) :Account(firstName, lastName, _UCN, _age, accNum, role) {}

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
	Task currentTask(TaskType::Open, this);
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
	Task currentTask(TaskType::Close, this, account_number);
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
		throw std::exception("Incorrect bank names!");
	}

	Bank* currentBank = banks[indexCurrent];
	int employeeIndexWithLeastTasks = currentBank->getLeastBusyWorker();
	Task currentTask(TaskType::Change, this, account_number);
	currentBank->receiveTask(currentTask);

	int idx = currentBank->getTaskSize() - 1;
	currentBank->getEmployeeByIndex(employeeIndexWithLeastTasks)->addTask(&currentTask);
}

void Client::list(const String& bank_name) {
	int index = getBankIndex(bank_name);
	if (index == -1) {
		throw std::exception("Bank with this name doesnt exist!");
	}

	Bank* currentBank = banks[index];
	bool hasAcc = false;
	for (size_t i = 0; i < currentBank->getSize(); i++)
	{
		if (strcmp(getFirstName().c_str(), currentBank->get_account_by_index(i)->getFirstName().c_str()) && strcmp(getLastName().c_str(), currentBank->get_account_by_index(i)->getLastName().c_str())) {
			currentBank->print_account_by_index(i);
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


void Client::exit() { 
	  
}

void Client::whoami()const {
	std::cout << "Name: " << getFirstName() << " " << getLastName() << std::endl;
	std::cout << "Role: " << RoleToString(getRole()) << std::endl;
	std::cout << "Age: " << getAge() << std::endl;
	std::cout << "UCN: " << getUCN() << std::endl;
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