#include "Login.h"
unsigned _getNumberLength(unsigned  n)
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

char _getCharFromDigit(int digit)
{
	if (digit < 0 || digit > 9)
		return '\0';

	return digit + ' 0';
}

String _toString(int number, String& str) {
	if (number == 0) {
		str = "0";
	}
	int length = _getNumberLength(number);
	for (int i = length - 1; i >= 0; i--) {
		str[i] = _getCharFromDigit(number % 10);
	}
	str[str.length()] = '\0';
	return str;
}

void Login::getRole(const String& firstName, const String& lastName, const String& password, String& role) {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i].getFirstName() == firstName && clients[i].getLastName() == lastName && clients[i].getPassword() == password) {
			isClient = true;
			index = i;
			role = "Client";
			return;
		}
	}

	for (size_t i = 0; i < bankWorkers.getCount(); i++)
	{
		if (bankWorkers[i].getFirstName() == firstName && bankWorkers[i].getLastName() == lastName && bankWorkers[i].getPassword() == password) {
			isBankWorker = true;
			index = i;
			role = "BankWorker";
			return;
		}
	}

	for (size_t i = 0; i < otherFirmWorker.getCount(); i++)
	{
		if (otherFirmWorker[i].getFirstName() == firstName && otherFirmWorker[i].getLastName() == lastName && otherFirmWorker[i].getPassword() == password) {
			isOtherFirmWorker = true;
			index = i;
			role = "OtherFirmWorker";
			return;
		}
	}

	throw std::exception("User not found!");
}

void Login::getInfoOfExistingUser(String& balance, String& accountID, String& UCN, unsigned& age) {
	if (isClient == true) {
		balance = clients[index].getBalance();
		accountID = clients[index].getAccountNumber();
		UCN = clients[index].getUCN();
		age = clients[index].getAge();
	}
	else if (isBankWorker == true) {

		balance = bankWorkers[index].getBalance();
		//accountID = bankWorkers[index]->getAccountNumber();
		UCN = bankWorkers[index].getUCN();
		age = bankWorkers[index].getAge();

	}
	else if (isOtherFirmWorker == true) {
		balance = otherFirmWorker[index].getBalance();
		//accountID = otherFirmWorker[index]->getAccountNumber();
		UCN = otherFirmWorker[index].getUCN();
		age = otherFirmWorker[index].getAge();
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

	String roleOfLogger = "";
	getRole(firstName, lastName, password, roleOfLogger);

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
		clients.push_back(Client(firstName, lastName, UCN, age, password, role));
		index = clients.getCount() - 1;
		clients[index].setAccountNumber(_toString(index, str));
		getBankByName(bankName)->addClient(&clients[index]);
		clients[clients.getCount() - 1].addBank(getBankByName(bankName));

	}
	else if (role == "BankWorker") {
		bankWorkers.push_back(BankWorker(firstName, lastName, UCN, age, password, role));
		index = bankWorkers.getCount() - 1;
		getBankByName(bankName)->addWorker(&bankWorkers[index]);
	}
	else if (role == "OtherFirmWorker") {
		otherFirmWorker.push_back(OtherFirmWorker(firstName, lastName, UCN, age, password, role));
		index = otherFirmWorker.getCount() - 1;
		otherFirmWorker[otherFirmWorker.getCount() - 1].addBank(getBankByName(bankName));
	}
}
void Login::create_bank(const String& bankName) {
	Bank bank(bankName);
	banks.push_back(bank);
}

void Login::userWhoami() const
{
	currentUser->whoami();
}

void Login::userHelp() const
{
	currentUser->help();
}

void Login::checkUser_avl(const String& bankName, const String& accNum) const
{
	if (isClient == true) {
		clients[index].check_avl(bankName, accNum);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userOpen(const String& bankName)
{
	if (isClient == true) {
		clients[index].open(bankName);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userCLose(const String& bankName, const String& accountNumber)
{
	if (isClient == true) {
		clients[index].close(bankName, accountNumber);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userChange(const String& newBank, const String& currentBank, const String& accountNumber)
{
	if (isClient == true) {
		clients[index].change(newBank, currentBank, accountNumber);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userList(const String& bankName)
{
	if (isClient == true) {
		clients[index].list(bankName);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userRedeem(const String& bankName, const String& accountID, const String& verificationCode)
{
	if (isClient == true) {
		clients[index].redeem(bankName, accountID, verificationCode);
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userMessages() const
{
	if (isClient == true) {
		clients[index].message();
	}
	else {
		throw std::exception("Its not a client.");
	}
}

void Login::userTasks() const
{
	if (isBankWorker == true) {
		bankWorkers[index].showTasks();
	}
	else {
		throw std::exception("Its not a bank worker. ");
	}
}

void Login::userView(unsigned _index) const
{
	if (isBankWorker == true) {
		bankWorkers[index].viewTask(_index);
	}
	else {
		throw std::exception("Its not a bank worker. ");
	}
}

void Login::userApprove(unsigned _index)
{
	if (isBankWorker == true) {
		bankWorkers[index].approveTask(_index);
	}
	else {
		throw std::exception("Its not a ban worker. ");
	}
}

void Login::userDisapprove(unsigned _index, const Message& message)
{
	if (isBankWorker == true) {
		bankWorkers[index].disapproveTask(_index, message);
	}
	else {
		throw std::exception("Its not a ban worker. ");
	}
}

void Login::userValidate(int index)
{
	if (isBankWorker == true) {
		bankWorkers[index].validate(index);
	}
	else {
		throw std::exception("Its not a ban worker. ");
	}
}

void Login::userSendCheck(const String& sum, const String& verificationCode,const String& bankName, const String& UCN)
{
	if (isOtherFirmWorker == true) {
		otherFirmWorker[index].send_check(sum, verificationCode,bankName,UCN);
	}
	else {
		throw std::exception("Its not a ban worker. ");
	}
}

void Login::exit() {
	if (isClient == true) {
		clients[index].exit();
	}
	else if (isBankWorker == true) {
		bankWorkers[index].exit();
	}
	else if (isOtherFirmWorker == true) {
		otherFirmWorker[index].exit();
	}
}
