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
		str[i] += getCharFromDigit(number % 10);
	}

	return str;
}

int Bank::getTaskIndex(const Task& toFind)const {
	for (int i = 0; i < tasks.getCount(); i++)
	{
		if (tasks[i].getType() == toFind.getType()&&tasks[i].getClient()==toFind.getClient()&&tasks[i].getBankName()==toFind.getBankName()) {
			return i;
		}
	}
	return -1;
}

 Task* Bank::getTaskByIdx(int idx) {
	return &tasks[idx];
}

const String& Bank::getClientsNumber()const {
	//String str = "";
	return toString(clients.getCount(), str);
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
	Client* _client=new Client(client->getFirstName(), client->getLastName(), client->getUCN(), client->getAge(), client->getPassword(), client->getRole());
	_client->setAccountNumber(account_number);

	clients.push_back(_client);
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
	size_t employeesCount = employees.getCount();

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

 Client* Bank::getClient(const Client* client)const {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i]->getFirstName() == client->getFirstName()&&clients[i]->getLastName()==client->getLastName()&&clients[i]->getPassword()==client->getPassword()) {
			return clients[i];
		}
	}
	
}

void Bank::receiveTask(const Task toDo) {
	tasks.push_back(toDo);
}

BankWorker* Bank::getEmployeeByIndex(int index)const {
	return employees[index];
}

int Bank::getTaskSize() const
{
	return tasks.getCount();
}

void Bank::addWorker(BankWorker* accountOfWorker) {
	employees.push_back(accountOfWorker);
}

void Bank::addClient(Client* accountOfClient) {
	clients.push_back(accountOfClient);
}


void Bank::sendAnswerToClient(const Message& message, Client* client) {
	client->addMessage(message);
}

 Client* Bank::getClientByAccNum(const String& accountNumber)const {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i]->getAccountNumber() == accountNumber) {
			return clients[i];
		}
	}
	return nullptr;
}

const Client* Bank::getClientByIndex(int indx)const {
	return clients[indx];
}

void Bank::printClientByIdx(unsigned index)const {
	std::cout <<"Password is: "<< clients[index]->getPassword()<<std::endl;
	std::cout << "Accout ID is: " << index << std::endl; //index is the account id!
}

