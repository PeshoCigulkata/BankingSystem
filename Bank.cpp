#include "Bank.h"


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



Bank::Bank(String _name) :name(_name) {}

const String& Bank::getName()const {
	return name;
}

void Bank::create_account(const String& balance, Client* client) {
	int accNum = accounts.getCount() + 1;
	String buff = "";
	String account_number = toString(accNum, buff);
	//String password = client->getPassword();
	Client client(client->getFirstName(), client->getLastName(), client->getUCN(), client->getAge(), client->getPassword(, client->getRole());
	client->setAccountNumber(account_number);

	clients.push_back(client);
}

void Bank::close_account(const String& account_number) {
	for (size_t i = 0; i < clients.getCount(); ++i) {
		if (clients[i]->getAccountNumber() == account_number) {
			delete clients[i];
			clients[i] = nullptr;
		}
	}
}

int Bank::getLeastBusyWorker()const {
	int index = 0;
	int employeesCount = employees.getCount();

	int leastTasks = employees[0]->getTasksSize();  //Start of the search
	for (size_t i = 0; i < employeesCount; i++)
	{
		if (employees[i]->getTasksSize() < leastTasks) {
			index = i;
			leastTasks = employees[i]->getTasksSize();
		}
	}
	return index;
}

bool Bank::validateUser(const Client* client)const {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i] == client) {
			return true;
		}
	}
	return false;
}

const Client* Bank::getClient(const Client* client)const {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i] == client) {
			return clients[i];
		}
	}
}

void Bank::receiveTask(const Task& toDo) {
	tasks.push_back(toDo);
}

BankWorker* Bank::getEmployeeByIndex(int index)const {
	return employees[index];
}

int Bank::getTaskSize() const
{
	return tasks.getCount();
}

void Bank::addWorker(Account* accoutOfWorker) {
	accounts.push_back(accoutOfWorker);
	BankWorker* worker = dynamic_cast<BankWorker*>(accoutOfWorker);
	if (worker == nullptr) {
		throw std::runtime_error("FAILED CASTING!");
	}
	employees.push_back(worker);
}

int Bank::getClientsNumber()const {
	return clients.getCount();
}


void Bank::sendAnswerToClient(const Message& message, Client* client) {
	client->addMessage(message);
}

Client* Bank::getClientByIndex(int indx)const {
	return clients[indx];
}

void Bank::printClientByIdx(unsigned index)const {
	std::cout<<clients[index]->getPassword();
	std::cout << index; //index is the account id!
}