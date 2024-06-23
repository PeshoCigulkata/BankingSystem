#pragma once
#include "String.h"
#include "Account.h"
#include "Message.h"
#include "Vector.hpp"
#include "BankWorker.h"
#include "Client.h"
//bankata znae za svoite klienti i rabotnici


//TODO: FIX CLIENTS!	
class Account;
class Message;
class Client;
class Task;
class BankWorker;


static String str="";

class Bank {
private:
	String name = "";       // name of the bank

	Vector<Account*> accounts;
	Vector<Message> messages;
	Vector<Task> tasks;
	Vector<BankWorker*> employees;
	Vector<Client*> clients;

	
public:
	Bank() = default;
	Bank(String n);

	const String& getName()const;

	void create_account(const String& balance, Client* client);
	void close_account(const String& account_number);

	bool validateUser(const Client* client)const;

	int getLeastBusyWorker()const;

	void receiveTask(const Task toDo);

	int getTaskIndex(const Task& toFind)const;

	 Task* getTaskByIdx(int idx);

	BankWorker* getEmployeeByIndex(int index)const;

	const Client* getClientByIndex(int indx)const;

	void printClientByIdx(unsigned index)const;   //prints the smetka of the client

	void addWorker(BankWorker* accoutOfWorker);

	void addClient(Client* accountOfClient);

	//void addOtherFirmWorker(Account* accountOfOtherFirmWorker);

	void sendAnswerToClient(const Message& message, Client* client);

	 Client* getClient(const Client* client)const;

	int getTaskSize()const;

	const String& getClientsNumber()const;

	 Client* getClientByAccNum(const String& accountNumber)const;

	~Bank() = default;
};
