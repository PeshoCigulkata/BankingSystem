#include "Login.h"

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

const String& Login::getRole(const String& firstName, const String& lastName, const String& password) {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i]->getFirstName() == firstName && clients[i]->getLastName() == lastName && clients[i]->getPassword() == password) {
			isClient = true;
			index = i;
			return "Client";
		}
	}

	for (size_t i = 0; i < bankWorkers.getCount(); i++)
	{
		if (bankWorkers[i]->getFirstName() == firstName && bankWorkers[i]->getLastName() == lastName && bankWorkers[i]->getPassword() == password) {
			isBankWorker = true;
			index = i;
			return "BankWorker";
		}
	}

	for (size_t i = 0; i < otherFirmWorker.getCount(); i++)
	{
		if (otherFirmWorker[i]->getFirstName() == firstName && otherFirmWorker[i]->getLastName() == lastName && otherFirmWorker[i]->getPassword() == password) {
			isOtherFirmWorker = true;
			index = i;
			return "OtherFirmWorker";
		}
	}

	throw std::exception("User not found!");
}

void Login::getInfoOfExistingUser(String& balance, String& accountID, String& UCN, unsigned& age) {
	if (isClient == true) {
		balance = clients[index]->getBalance();
		accountID = clients[index]->getAccountNumber();
		UCN = clients[index]->getUCN();
		age = clients[index]->getAge();
	}
	else if (isBankWorker == true) {

		balance = bankWorkers[index]->getBalance();
		//accountID = bankWorkers[index]->getAccountNumber();
		UCN = bankWorkers[index]->getUCN();
		age = bankWorkers[index]->getAge();

	}
	else if (isOtherFirmWorker == true) {
		balance = otherFirmWorker[index]->getBalance();
		//accountID = otherFirmWorker[index]->getAccountNumber();
		UCN = otherFirmWorker[index]->getUCN();
		age = otherFirmWorker[index]->getAge();
	}

}

Bank* Login::getBankByName(const String& bankName) {
	for (size_t i = 0; i < banks.getCount(); i++)
	{
		if (banks[i].getName() == bankName) {
			return &banks[i];
		}
	}

	return nullptr;
}

void Login::login(const String& firstName, const String& lastName, const String& password) {
	if (currentUser != nullptr) {
		throw std::exception("One person can be logged!");
	}

	String roleOfLogger = getRole(firstName, lastName, password);

	String balance = "";
	String accountID = "";
	String UCN = "";
	unsigned age = 0;
	getInfoOfExistingUser(balance, accountID, UCN, age);


	if (roleOfLogger == "Client") {
		currentUser = new Client(firstName, lastName, UCN, age, password, roleOfLogger);

	}
	else if (roleOfLogger == "BankWorker") {
		currentUser = new BankWorker(firstName, lastName, UCN, age, password, roleOfLogger);
	}
	else if (roleOfLogger == "OtherFirmWorker") {
		currentUser = new OtherFirmWorker(firstName, lastName, UCN, age, password, roleOfLogger);
	}

}

void Login::signup(const String& firstName, const String& lastName, const String& UCN, unsigned age, const String& role, const String& password, const String& bankName) {
	if (role == "Client") {
		Bank* bank = getBankByName(bankName);
		Account* User = new Client(firstName, lastName, UCN, age, password, role);
		String str = "";
		Client currentClient(firstName, lastName, UCN, age, toString(bank->getClientsNumber(), str), role);
		Client* ptr = &currentClient;
		clients.push_back(ptr);
		bank->addClient(User);
		dynamic_cast<Client*>(User)->addBank(bank);
		//currentUser = User;
		//currentUsers.push_back(currentUser);
	}
	else if (role == "BankWorker") {
		Bank* bank = getBankByName(bankName);
		Account* user = new BankWorker(firstName, lastName, UCN, age, password, role);
		bank->addWorker(user);
		dynamic_cast<BankWorker*>(user)->setBank(bank);
		//	currentUsers.push_back(currentUser);
	}
	else if (role == "OtherFirmWorker") {
		Bank* bank = getBankByName(bankName);
		Account* _user = new OtherFirmWorker(firstName, lastName, UCN, age, password, role);
		bank->addOtherFirmWorker(_user);
		dynamic_cast<OtherFirmWorker*>(_user)->setBank(bank);
		//	currentUsers.push_back(currentUser);
	}
}
void Login::create_bank(const String& bankName) {
	Bank bank(bankName);
	banks.push_back(bank);
}

void Login::exit() {
	if (currentUser->getRole() == "Client") {
		dynamic_cast<Client*>(currentUser)->exit();
		currentUser = nullptr;
	}
	else if (currentUser->getRole() == "BankWorker") {
		dynamic_cast<BankWorker*>(currentUser)->exit();
		currentUser = nullptr;
	}
	else if (currentUser->getRole() == "OtherFirmWorker") {
		dynamic_cast<OtherFirmWorker*>(currentUser)->exit();
		currentUser = nullptr;
	}
}
